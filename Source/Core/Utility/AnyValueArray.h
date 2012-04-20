/****************************************************************************/
/**
 *  @file AnyValueArray.h
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
#ifndef KVS__ANY_VALUE_ARRAY_H_INCLUDE
#define KVS__ANY_VALUE_ARRAY_H_INCLUDE

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <typeinfo>
#include <string>
#include <sstream>
#include <kvs/DebugNew>
#include <kvs/Endian>
#include <kvs/AnyValue>
#include <kvs/ReferenceCounter>
#include <kvs/ValueArray>
#include <kvs/Macro>
#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Any type array class.
 */
/*==========================================================================*/
class AnyValueArray
{
    kvsClassName_without_virtual( kvs::AnyValueArray );

public:

    typedef kvs::AnyValue::TypeInfo TypeInfo;

private:

    kvs::ReferenceCounter* m_counter;       ///< reference counter

    TypeInfo* m_type_info;     ///< type information
    size_t    m_size_of_value; ///< byte size of a value

    size_t    m_size;       ///< number of values
    void*     m_values;        ///< value array

public:

    AnyValueArray();

    template<typename T>
    AnyValueArray( const T* values, const size_t size );

    template<typename T>
    explicit AnyValueArray( const std::vector<T>& values );

    template<typename T>
    explicit AnyValueArray( const kvs::ValueArray<T>& values );

    AnyValueArray( const AnyValueArray& other );

    ~AnyValueArray();

public:

    AnyValueArray& operator =( const AnyValueArray& rhs )
    {
        AnyValueArray temp( rhs );
        temp.swap( *this );
        return *this;
    }

public:

    template<typename T>
    T& at( const size_t index )
    {
        KVS_ASSERT( index < this->size() );
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<T*>( this->data() )[ index ];
    }

    template<typename T>
    const T& at( const size_t index ) const
    {
        KVS_ASSERT( index < this->size() );
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<const T*>( this->data() )[ index ];
    }

    template<typename T>
    T to( const size_t index ) const
    {
        // Value to Value.
        const std::type_info& type = this->typeInfo()->type();
        if ( type == typeid( kvs::Int8   ) ) return static_cast<T>( this->at<kvs::Int8  >( index ) );
        if ( type == typeid( kvs::Int16  ) ) return static_cast<T>( this->at<kvs::Int16 >( index ) );
        if ( type == typeid( kvs::Int32  ) ) return static_cast<T>( this->at<kvs::Int32 >( index ) );
        if ( type == typeid( kvs::Int64  ) ) return static_cast<T>( this->at<kvs::Int64 >( index ) );
        if ( type == typeid( kvs::UInt8  ) ) return static_cast<T>( this->at<kvs::UInt8 >( index ) );
        if ( type == typeid( kvs::UInt16 ) ) return static_cast<T>( this->at<kvs::UInt16>( index ) );
        if ( type == typeid( kvs::UInt32 ) ) return static_cast<T>( this->at<kvs::UInt32>( index ) );
        if ( type == typeid( kvs::UInt64 ) ) return static_cast<T>( this->at<kvs::UInt64>( index ) );
        if ( type == typeid( kvs::Real32 ) ) return static_cast<T>( this->at<kvs::Real32>( index ) );
        if ( type == typeid( kvs::Real64 ) ) return static_cast<T>( this->at<kvs::Real64>( index ) );

        // String to Value.
        if ( type == typeid( std::string ) )
        {
            T v; std::stringstream s( this->at<std::string>( index ) ); s >> v;
            return v;
        }

        kvsMessageError("Unsupported data type.");
        return T( 0 );
    }

    size_t size() const
    {
        return m_size;
    }

    size_t byteSize() const
    {
        return this->size() * m_size_of_value;
    }

    bool isEmpty() const
    {
        return this->empty();
    }

    const void* pointer() const
    {
        return this->data();
    }

    void* pointer()
    {
        return this->data();
    }

    template<typename T>
    const T* pointer() const
    {
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<const T*>( this->data() );
    }

    template<typename T>
    T* pointer()
    {
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<T*>( this->data() );
    }

    const TypeInfo* typeInfo() const
    {
        return m_type_info;
    }

    ReferenceCounter* counter() const
    {
        return m_counter;
    }

    void swapByte()
    {
        const std::type_info& type = this->typeInfo()->type();
        if (      type == typeid( kvs::Int8   ) ) { kvs::Endian::Swap( static_cast<kvs::Int8*  >( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::UInt8  ) ) { kvs::Endian::Swap( static_cast<kvs::UInt8* >( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::Int16  ) ) { kvs::Endian::Swap( static_cast<kvs::Int16* >( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::UInt16 ) ) { kvs::Endian::Swap( static_cast<kvs::UInt16*>( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::Int32  ) ) { kvs::Endian::Swap( static_cast<kvs::Int32* >( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::UInt32 ) ) { kvs::Endian::Swap( static_cast<kvs::UInt32*>( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::Int64  ) ) { kvs::Endian::Swap( static_cast<kvs::Int64* >( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::UInt64 ) ) { kvs::Endian::Swap( static_cast<kvs::UInt64*>( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::Real32 ) ) { kvs::Endian::Swap( static_cast<kvs::Real32*>( this->data() ), this->size() ); }
        else if ( type == typeid( kvs::Real64 ) ) { kvs::Endian::Swap( static_cast<kvs::Real64*>( this->data() ), this->size() ); }
    }

    template<typename T>
    void shallowCopy( const kvs::ValueArray<T>& values )
    {
        *this = AnyValueArray( values );
    }

    void shallowCopy( const AnyValueArray& other )
    {
        *this = other;
    }

    template<typename T>
    void deepCopy( const T* values, const size_t size )
    {
        *this = AnyValueArray( kvs::ValueArray<T>( values, size ) );
    }

    const void* data() const
    {
        return m_values;
    }

    void* data()
    {
        return m_values;
    }

    void swap( AnyValueArray& other )
    {
        std::swap( m_values, other.m_values );
        std::swap( m_size, other.m_size );
        std::swap( m_counter, other.m_counter );
        std::swap( m_size_of_value, other.m_size_of_value );
        std::swap( m_type_info, other.m_type_info );
    }

    AnyValueArray clone() const
    {
        const std::type_info& type = this->typeInfo()->type();
        if (      type == typeid( kvs::Int8   ) ) { return this->clone_helper<kvs::Int8  >(); }
        else if ( type == typeid( kvs::UInt8  ) ) { return this->clone_helper<kvs::UInt8 >(); }
        else if ( type == typeid( kvs::Int16  ) ) { return this->clone_helper<kvs::Int16 >(); }
        else if ( type == typeid( kvs::UInt16 ) ) { return this->clone_helper<kvs::UInt16>(); }
        else if ( type == typeid( kvs::Int32  ) ) { return this->clone_helper<kvs::Int32 >(); }
        else if ( type == typeid( kvs::UInt32 ) ) { return this->clone_helper<kvs::UInt32>(); }
        else if ( type == typeid( kvs::Int64  ) ) { return this->clone_helper<kvs::Int64 >(); }
        else if ( type == typeid( kvs::UInt64 ) ) { return this->clone_helper<kvs::UInt64>(); }
        else if ( type == typeid( kvs::Real32 ) ) { return this->clone_helper<kvs::Real32>(); }
        else if ( type == typeid( kvs::Real64 ) ) { return this->clone_helper<kvs::Real64>(); }
        KVS_ASSERT( false );
        return AnyValueArray();
    }

    bool empty() const
    {
        return this->size() == 0;
    }

private:

    template <typename T>
    AnyValueArray clone_helper() const
    {
        ValueArray<T> ret( static_cast<const T*>( this->data() ), this->size() );
        return AnyValueArray( ret );
    }

public:

#if KVS_ENABLE_DEPRECATED

    template<typename T>
    void* allocate( const size_t size )
    {
        this->deallocate();
        *this = AnyValueArray( kvs::ValueArray<T>( size ) );
        return this->data();
    }

#else

    template<typename T>
    void allocate( const size_t size )
    {
        *this = AnyValueArray( kvs::ValueArray<T>( size ) );
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
                if ( m_values )
                {
                    const std::type_info& type = this->typeInfo()->type();
                    if (      type == typeid( kvs::Int8   ) ) { this->delete_array<kvs::Int8  >(); }
                    else if ( type == typeid( kvs::UInt8  ) ) { this->delete_array<kvs::UInt8 >(); }
                    else if ( type == typeid( kvs::Int16  ) ) { this->delete_array<kvs::Int16 >(); }
                    else if ( type == typeid( kvs::UInt16 ) ) { this->delete_array<kvs::UInt16>(); }
                    else if ( type == typeid( kvs::Int32  ) ) { this->delete_array<kvs::Int32 >(); }
                    else if ( type == typeid( kvs::UInt32 ) ) { this->delete_array<kvs::UInt32>(); }
                    else if ( type == typeid( kvs::Int64  ) ) { this->delete_array<kvs::Int64 >(); }
                    else if ( type == typeid( kvs::UInt64 ) ) { this->delete_array<kvs::UInt64>(); }
                    else if ( type == typeid( kvs::Real32 ) ) { this->delete_array<kvs::Real32>(); }
                    else if ( type == typeid( kvs::Real64 ) ) { this->delete_array<kvs::Real64>(); }
                    else if ( type == typeid( std::string ) ) { this->delete_array<std::string>(); }
                }
                delete m_counter;
            }
        }
        delete m_type_info;

        m_type_info = 0;
        m_counter       = 0;
        m_size_of_value = 0;
        m_size       = 0;
        m_values        = 0;
    }

    template <typename T>
    void delete_array()
    {
        delete [] static_cast<T*>( m_values );
    }

    template <typename T>
    bool check_type() const
    {
        return this->typeInfo()->type() == typeid( T );
    }
};

template<typename T>
inline AnyValueArray::AnyValueArray( const T* values, const size_t size )
    : m_counter( 0 )
    , m_type_info( 0 )
    , m_size_of_value( 0 )
    , m_size( 0 )
    , m_values( 0 )
{
    *this = AnyValueArray( kvs::ValueArray<T>( values, size ) );
}

template<typename T>
inline AnyValueArray::AnyValueArray( const std::vector<T>& values )
    : m_counter( 0 )
    , m_type_info( 0 )
    , m_size_of_value( 0 )
    , m_size( 0 )
    , m_values( 0 )
{
    *this = AnyValueArray( kvs::ValueArray<T>( values ) );
}

template<typename T>
inline AnyValueArray::AnyValueArray( const kvs::ValueArray<T>& values )
{
    m_counter       = values.counter();
    m_size          = values.size();
    m_values        = const_cast<T*>( values.data() );

    m_type_info     = new kvs::AnyValue::SetTypeInfo<T>();
    m_size_of_value = sizeof( T );

    this->ref();
}

template<>
inline std::string AnyValueArray::to<std::string>( const size_t index ) const
{
    const std::type_info& type = this->typeInfo()->type();

    // String to String.
    if ( type == typeid( std::string ) ) return this->at<std::string>( index );

    std::ostringstream v;
    // Value to String.
    if      ( type == typeid( kvs::Int8   ) ) { v << this->at<kvs::Int8  >( index ); }
    else if ( type == typeid( kvs::Int16  ) ) { v << this->at<kvs::Int16 >( index ); }
    else if ( type == typeid( kvs::Int32  ) ) { v << this->at<kvs::Int32 >( index ); }
    else if ( type == typeid( kvs::Int64  ) ) { v << this->at<kvs::Int64 >( index ); }
    else if ( type == typeid( kvs::UInt8  ) ) { v << this->at<kvs::UInt8 >( index ); }
    else if ( type == typeid( kvs::UInt16 ) ) { v << this->at<kvs::UInt16>( index ); }
    else if ( type == typeid( kvs::UInt32 ) ) { v << this->at<kvs::UInt32>( index ); }
    else if ( type == typeid( kvs::UInt64 ) ) { v << this->at<kvs::UInt64>( index ); }
    else if ( type == typeid( kvs::Real32 ) ) { v << this->at<kvs::Real32>( index ); }
    else if ( type == typeid( kvs::Real64 ) ) { v << this->at<kvs::Real64>( index ); }
    else { kvsMessageError("Unsupported data type."); }

    return v.str();
}

} // end of namespace kvs

namespace std
{

inline void swap( kvs::AnyValueArray& lhs, kvs::AnyValueArray& rhs )
{
    lhs.swap( rhs );
}

} // std

#endif // KVS__ANY_VALUE_ARRAY_H_INCLUDE
