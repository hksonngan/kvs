/*****************************************************************************/
/**
 *  @file   SharedCount.h
 *  @author Naoya Maeda
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS_SHARED_COUNT_H_INCLUDE
#define KVS_SHARED_COUNT_H_INCLUDE

#if defined KVS_ENABLE_THREAD_SAFE
  #if defined KVS_COMPILER_GCC
    #define KVS_ATOMIC_INCREMENT( a ) __sync_add_and_fetch( &a, 1 )
    #define KVS_ATOMIC_DECREMENT( a ) __sync_sub_and_fetch( &a, 1 )
    #define KVS_ATOMIC_COMPARE_SWAP( a, b, c ) __sync_val_compare_and_swap( &a, b, c )
  #elif defined KVS_COMPILER_VC
    #include <intrin.h>
    #define KVS_ATOMIC_INCREMENT( a ) _InterlockedIncrement( &a )
    #define KVS_ATOMIC_DECREMENT( a ) _InterlockedDecrement( &a )
    #define KVS_ATOMIC_COMPARE_SWAP( a, b, c ) _InterlockedCompareExchange( &a, c, b )
  #else
    #error "Not Supported Compiler"
  #endif
#else
  #define KVS_ATOMIC_INCREMENT( a ) ( ++a )
  #define KVS_ATOMIC_DECREMENT( a ) ( --a )
  #define KVS_ATOMIC_COMPARE_SWAP( a, b, c ) _kvs_non_atomic_compare_swap( &a, b, c )
#endif

namespace kvs
{

namespace detail
{

namespace shared_pointer_impl
{

inline long _kvs_non_atomic_compare_swap( long* ptr, long oldval, long newval )
{
    long old = *ptr;
    if ( old == oldval ) { *ptr = newval; }
    return old;
}

// Implementation of shared count.
// A instance of this class contain a pointer to an instance and 
// manage the shared count and weak count of it.
class Counter
{
protected:
// Constructs a instance which contain 'ptr' and manages the life-time of the instance to which 'ptr' is indicating.
// The instance to which 'ptr' is indicating is automatically deleted when the shared count becomes 0.
// And the instance of this class is automatcally deleted when the weak count becomes 0.
// In the beginning, the weak count is 1, which is decremented when the shared count becomes 0.
    explicit Counter( void* ptr ) throw()
        : m_pointer( ptr )
        , m_count( 1 )
        , m_weak_count( 1 )
    {}

    virtual ~Counter() throw()
    {}

public:
// Returns the count of shared.
    long use_count() const throw()
    {
        return m_count;
    }

public:
// Inclements the shared count.
    void increment() throw()
    {
        KVS_ATOMIC_INCREMENT( m_count );
    }

// Decrements the shared count.
// When the count become 0, the weak count is also decremented.
    void decrement() throw()
    {
        KVS_ATOMIC_DECREMENT( m_count );
        if ( m_count == 0 )
        {
            this->dispose();
            this->decrement_weak();
        }
    }

// Increments the weak count.
    void increment_weak() throw()
    {
        KVS_ATOMIC_INCREMENT( m_weak_count );
    }

// Decrements the weak count.
// When the weak count becomes 0, this instance is deleted.
    void decrement_weak() throw()
    {
        KVS_ATOMIC_DECREMENT( m_weak_count );
        if ( m_weak_count == 0 )
        {
            delete this;
        }
    }

// Increments the shared count if the instance is not expired.
// Returns true if the count is incremented.
    bool increment_if_not_expired() throw()
    {
        for ( ;; )
        {
            long count = ( volatile long& )m_count;
            if ( count == 0 )
                return false;
            if ( KVS_ATOMIC_COMPARE_SWAP( m_count, count, count + 1 ) == count )
                return true;
        }
    }

private:
    virtual void dispose() throw() = 0;

protected: // for dispose()
    void* m_pointer;   // pointer to a instance

private:
    long m_count;      // number of shared count
    long m_weak_count; // number of weak count + ( m_count != 0 ? 1 : 0 )

private:
    Counter( const Counter& );
    Counter& operator =( const Counter& );
}; // Counter

#undef KVS_ATOMIC_INCREMENT
#undef KVS_ATOMIC_DECREMENT
#undef KVS_ATOMIC_COMPARE_SWAP


template <typename T>
class DefaultCounter : public Counter
{
public:
    DefaultCounter( T* ptr ) throw()
        : Counter( static_cast<void*>( ptr ) )
    {}

private:
// Delete the managing instance using delete.
    void dispose() throw()
    {
        delete static_cast<T*>( m_pointer );
    }
}; // DefaultCounter



template <typename T, typename D>
class CounterWithDeleter : public Counter
{
public:
// 'deleter' must be copy-constructable.
    CounterWithDeleter( T* ptr, D deleter ) throw()
        : Counter( static_cast<void*>( ptr ) )
        , m_deleter( deleter )
    {}

private:
// Delete the managing instance using deleter specified at constructor.
    void dispose() throw()
    {
        m_deleter( static_cast<T*>( m_pointer ) );
    }

private:
    D m_deleter;
}; // CounterWithDeleter



class WeakCount;

// Shared Count class
// This class hold a pointer to shared count and manage 
// the operation against the count.
// 
class SharedCount
{
public:
    SharedCount() throw()
        : m_counter( NULL )
    {}

    // delete ptr; must be well-formed.
    template <typename T>
    explicit SharedCount( T* ptr )
    {
        m_counter = this->make_counter( ptr );
    }

    // deleter( ptr ); must be well-formed.
    // 'deleter' must be copy-constructable. Copy of it is used.
    template <typename T, typename D>
    SharedCount( T* ptr, D deleter )
    {
        m_counter = this->make_counter( ptr, deleter );
    }

    SharedCount( const SharedCount& other ) throw()
        : m_counter( other.m_counter )
    {
        if ( m_counter ) { m_counter->increment(); }
    }

    explicit SharedCount( const WeakCount& other ) throw();

    ~SharedCount() throw()
    {
        if ( m_counter ) { m_counter->decrement(); }
    }

public:
    void swap( SharedCount& other ) throw()
    {
        std::swap( m_counter, other.m_counter );
    }

    long use_count() const throw()
    {
        return m_counter ? m_counter->use_count() : 0;
    }

    bool is_valid() const throw()
    {
        return m_counter != NULL;
    }

private:
    template <typename T>
    static Counter* make_counter( T* ptr )
    {
        try
        {
            return new DefaultCounter<T>( ptr );
        }
        catch ( ... )
        {
            delete ptr;
            throw;
        }
    }

    template <typename T, typename D>
    static Counter* make_counter( T* ptr, D deleter )
    {
        try
        {
            return new CounterWithDeleter<T, D>( ptr, deleter );
        }
        catch ( ... )
        {
            deleter( ptr );
            throw;
        }
    }

private:
    Counter* m_counter;

    friend class WeakCount;

    SharedCount& operator =( const SharedCount& );
}; // SharedCount



class WeakCount
{
public:
    WeakCount() throw()
        : m_counter( NULL )
    {}

    explicit WeakCount( const SharedCount& other ) throw()
        : m_counter( other.m_counter )
    {
        if ( m_counter ) { m_counter->increment_weak(); }
    }

    WeakCount( const WeakCount& other ) throw()
        : m_counter( other.m_counter )
    {
        if ( m_counter ) { m_counter->increment_weak(); }
    }

    ~WeakCount() throw()
    {
        if ( m_counter ) { m_counter->decrement_weak(); }
    }

public:
    void swap( WeakCount& other ) throw()
    {
        std::swap( m_counter, other.m_counter );
    }

    long use_count() const throw()
    {
        return m_counter ? m_counter->use_count() : 0;
    }

    bool expired() const throw()
    {
        return !m_counter || m_counter->use_count() == 0;
    }

private:
    Counter* m_counter;

    friend class SharedCount;

    WeakCount& operator =( const WeakCount& );
}; // WeakCount



inline SharedCount::SharedCount( const WeakCount& other ) throw()
    : m_counter( NULL )
{
    if ( other.m_counter && other.m_counter->increment_if_not_expired() )
    {
        // Copy if the instance is not expired.
        m_counter = other.m_counter;
    }
}

} // shared_pointer_impl

} // detail

} // kvs

#endif
