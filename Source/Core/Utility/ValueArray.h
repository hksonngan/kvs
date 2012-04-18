/****************************************************************************/
/**
 *  @file ValueArray.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS__VALUE_ARRAY_H_INCLUDE
#define KVS__VALUE_ARRAY_H_INCLUDE

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <limits>
#include <vector>
#include <cstring>
#include <typeinfo>
#include <algorithm>
#include <iterator>
#include <utility>
#include <kvs/DebugNew>
#include <kvs/Assert>
#include <kvs/Endian>
#include <kvs/Message>
#include <kvs/ReferenceCounter>
#include <kvs/Macro>
#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Value array class.
 */
/*==========================================================================*/
template<typename T>
class ValueArray
{
    kvsClassName_without_virtual( kvs::ValueArray );

public:

    typedef ValueArray<T>                         this_type;
    typedef T                                     value_type;
    typedef T*                                    iterator;
    typedef const T*                              const_iterator;
    typedef T&                                    reference;
    typedef const T&                              const_reference;
    typedef std::size_t                           size_type;
    typedef std::ptrdiff_t                        difference_type;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

private:

    kvs::ReferenceCounter* m_counter; ///< Reference counter.
    size_t                 m_size; ///< Number of values.
    value_type*            m_values;  ///< Value array.

public:

    ValueArray()
        : m_counter( 0 )
        , m_size( 0 )
        , m_values( 0 )
    {
        this->create_counter();
    }

    explicit ValueArray( const size_t size )
        : m_counter( 0 )
        , m_size( 0 )
        , m_values( 0 )
    {
        this->allocate( size );
    }

    ValueArray( const value_type* const values, const size_t size )
        : m_counter( 0 )
        , m_size( 0 )
        , m_values( 0 )
    {
        this->allocate( size );
        std::copy( values, values + size, this->begin() );
    }

    explicit ValueArray( const std::vector<T>& values )
        : m_counter( 0 )
        , m_size( 0 )
        , m_values( 0 )
    {
        this->allocate( values.size() );
        std::copy( values.begin(), values.end(), this->begin() );
    }

    template <typename InIter>
    ValueArray( InIter first, InIter last )
        : m_counter( 0 )
        , m_size( 0 )
        , m_values( 0 )
    {
        this->allocate( std::distance( first, last ) );
        std::copy( first, last, this->begin() );
    }

    ValueArray( const this_type& other )
        : m_counter( 0 )
        , m_size( 0 )
        , m_values( 0 )
    {
        m_counter = other.m_counter;
        m_size = other.m_size;
        m_values  = other.m_values;
        this->ref();
    }

    ~ValueArray()
    {
        this->unref();
    }

public:

    iterator begin()
    {
        return this->data();
    }

    const_iterator begin() const
    {
        return this->data();
    }

    iterator end()
    {
        return this->begin() + this->size();
    }

    const_iterator end() const
    {
        return this->begin() + this->size();
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator( this->end() );
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator( this->end() );
    }

    reverse_iterator rend()
    {
        return reverse_iterator( this->begin() );
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator( this->begin() );
    }

public:

    reference operator []( const size_t index )
    {
        KVS_ASSERT( index < this->size() );
        return this->data()[ index ];
    }

    const_reference operator []( const size_t index ) const
    {
        KVS_ASSERT( index < this->size() );
        return this->data()[ index ];
    }

    this_type& operator =( const this_type& rhs )
    {
        this_type temp( rhs );
        temp.swap( *this );
        return *this;
    }

    friend bool operator ==( const this_type& lhs, const this_type& rhs )
    {
        return lhs.size() == rhs.size() &&
               std::equal( lhs.begin(), lhs.end(), rhs.begin() );
    }

    friend bool operator <( const this_type& lhs, const this_type& rhs )
    {
        return std::lexicographical_compare( lhs.begin(), lhs.end(),
                                             rhs.begin(), rhs.end() );
    }

    friend bool operator !=( const this_type& lhs, const this_type& rhs )
    {
        return !( lhs == rhs );
    }

    friend bool operator >( const this_type& lhs, const this_type& rhs )
    {
        return rhs < lhs;
    }

    friend bool operator <=( const this_type& lhs, const this_type& rhs )
    {
        return !( rhs < lhs );
    }

    friend bool operator >=( const this_type& lhs, const this_type& rhs )
    {
        return !( lhs < rhs );
    }

public:

    reference at( const size_t index )
    {
        return (*this)[ index ];
    }

    const_reference at( const size_t index ) const
    {
        return (*this)[ index ];
    }

    reference front()
    {
        return (*this)[0];
    }

    const_reference front() const
    {
        return (*this)[0];
    }

    reference back()
    {
        return (*this)[ this->size() - 1 ];
    }

    const_reference back() const
    {
        return (*this)[ this->size() - 1 ];
    }

    size_type size() const
    {
        return m_size;
    }

    size_type byteSize() const
    {
        return this->size() * sizeof( value_type );
    }

    bool isEmpty() const
    {
        return this->empty();
    }

    value_type* pointer()
    {
        return this->data();
    }

    const value_type* pointer() const
    {
        return this->data();
    }

    kvs::ReferenceCounter* counter() const
    {
        return m_counter;
    }

    void swapByte()
    {
        kvs::Endian::Swap( this->data(), this->size() );
    }

    value_type* data()
    {
        return m_values;
    }

    const value_type* data() const
    {
        return m_values;
    }

    bool empty() const
    {
        return this->size() == 0;
    }

    void swap( ValueArray& other )
    {
        std::swap( m_values, other.m_values );
        std::swap( m_size, other.m_size );
        std::swap( m_counter, other.m_counter );
    }

    this_type clone() const
    {
        return this_type( this->begin(), this->end() );
    }

public:

#if KVS_ENABLE_DEPRECATED

    value_type* allocate( const size_t size )
    {
        this->unref();
        this->create_counter();

        m_size = size;
        m_values = new value_type [ size ];
        KVS_ASSERT( m_values != NULL );

        return m_values;
    }

    void fill( const int bit )
    {
        memset( m_values, bit, sizeof( value_type ) * m_size );
    }

    void shallowCopy( const this_type& other )
    {
        *this = other;
    }

    void deepCopy( const this_type& other )
    {
        *this = other.clone();
    }

    void deepCopy( const value_type* values, const size_t nvalues )
    {
        *this = this_type( values, nvalues );
    }

#else

    void allocate( const size_t size )
    {
        this->unref();
        this->create_counter();

        m_size = size;
        m_values = new value_type [ size ];
    }

    void fill( const T& value )
    {
        std::fill( this->begin(), this->end(), value );
    }

#endif

    void deallocate()
    {
        this->unref();
    }

private:

    void create_counter()
    {
        m_counter = new ReferenceCounter( 1 );
        KVS_ASSERT( m_counter != NULL );
    }

    void ref()
    {
        if ( m_counter ) { m_counter->increment(); }
    }

    void unref()
    {
        if ( m_counter )
        {
            m_counter->decrement();

            if ( m_counter->value() == 0 )
            {
                if ( m_values  ) { delete [] m_values; }
                if ( m_counter ) { delete m_counter; }
            }
        }

        m_counter = 0;
        m_size = 0;
        m_values  = 0;
    }
};

} // end of namespace kvs

namespace std
{

template <typename T>
inline void swap( kvs::ValueArray<T>& lhs, kvs::ValueArray<T>& rhs )
{
    lhs.swap( rhs );
}

} // std

#endif // KVS__VALUE_ARRAY_H_INCLUDE
