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

#include <typeinfo>
#include <string>
#include <sstream>
#include <utility>
#include <kvs/Type>
#include <kvs/AnyValue>
#include <kvs/SharedPointer>
#include <kvs/ValueArray>
#include <kvs/ClassName>
#if KVS_ENABLE_DEPRECATED
#include <kvs/Endian>
#endif


namespace kvs
{

namespace temporal
{

template <typename T, T Value>
struct integral_constant
{
    static const T value = Value;
    typedef T value_type;
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

} // temporal

#define KVS_STATIC_ASSERT( expr, mes ) { char dummy[ ( expr ) ? 1 : -1 ]; (void)dummy; }

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
    kvs::SharedPointer<void>     m_values;       ///< value array
    kvs::SharedPointer<TypeInfo> m_type_info;     ///< type information
    size_t    m_size_of_value; ///< byte size of a value
    size_t    m_size;       ///< number of values

public:
    AnyValueArray();

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

    template <typename T>
    kvs::ValueArray<T> asValueArray() const
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
        KVS_ASSERT( this->check_type<T>() );
        return kvs::ValueArray<T>( kvs::static_pointer_cast<T>( m_values ), m_size );
    }

public:
    template<typename T>
    T& at( const size_t index )
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
        KVS_ASSERT( index < this->size() );
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<T*>( this->data() )[ index ];
    }

    template<typename T>
    const T& at( const size_t index ) const
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
        KVS_ASSERT( index < this->size() );
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<const T*>( this->data() )[ index ];
    }

    template<typename T>
    T to( const size_t index ) const
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );

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
            T v; std::istringstream s( this->at<std::string>( index ) ); s >> v;
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

    template<typename T>
    const T* pointer() const
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<const T*>( this->data() );
    }

    template<typename T>
    T* pointer()
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
        KVS_ASSERT( this->check_type<T>() );
        return static_cast<T*>( this->data() );
    }

    const TypeInfo* typeInfo() const
    {
        return m_type_info.get();
    }

    const kvs::SharedPointer<void>& getSharedPointer() const
    {
        return m_values;
    }

    const void* data() const
    {
        return m_values.get();
    }

    void* data()
    {
        return m_values.get();
    }

    void swap( AnyValueArray& other )
    {
        std::swap( m_values, other.m_values );
        std::swap( m_size, other.m_size );
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

    const void* pointer() const
    {
        return this->data();
    }

    void* pointer()
    {
        return this->data();
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
    AnyValueArray( const T* values, const size_t size )
    {
        *this = AnyValueArray( kvs::ValueArray<T>( values, size ) );
    }

    template<typename T>
    AnyValueArray( const std::vector<T>& values )
    {
        *this = AnyValueArray( kvs::ValueArray<T>( values ) );
    }

    template<typename T>
    void* allocate( const size_t size )
    {
        this->deallocate();
        *this = AnyValueArray( kvs::ValueArray<T>( size ) );
        return this->data();
    }

    bool isEmpty() const
    {
        return this->empty();
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

#else

    template<typename T>
    void allocate( const size_t size )
    {
        *this = AnyValueArray( kvs::ValueArray<T>( size ) );
    }

#endif

    void deallocate()
    {
        m_values.reset();
        m_type_info.reset();
        m_size = 0;
        m_size_of_value = 0;
    }

private:

    template <typename T>
    bool check_type() const
    {
        return this->typeInfo()->type() == typeid( T );
    }

    template <typename T>
    struct is_supported : kvs::temporal::false_type {};
};

template<typename T>
inline AnyValueArray::AnyValueArray( const kvs::ValueArray<T>& values )
{
    KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
    m_values        = kvs::static_pointer_cast<T>( values.getSharedPointer() );
    m_size          = values.size();
    m_size_of_value = sizeof( T );
    m_type_info.reset( new kvs::AnyValue::SetTypeInfo<T>() );
}

template<>
inline std::string AnyValueArray::to<std::string>( const size_t index ) const
{
    const std::type_info& type = this->typeInfo()->type();

    // String to String.
    if ( type == typeid( std::string ) ) return this->at<std::string>( index );

    std::ostringstream v;
    // Value to String.
    if      ( type == typeid( kvs::Int8   ) ) { v << (int)this->at<kvs::Int8  >( index ); }
    else if ( type == typeid( kvs::Int16  ) ) { v << this->at<kvs::Int16 >( index ); }
    else if ( type == typeid( kvs::Int32  ) ) { v << this->at<kvs::Int32 >( index ); }
    else if ( type == typeid( kvs::Int64  ) ) { v << this->at<kvs::Int64 >( index ); }
    else if ( type == typeid( kvs::UInt8  ) ) { v << (int)this->at<kvs::UInt8 >( index ); }
    else if ( type == typeid( kvs::UInt16 ) ) { v << this->at<kvs::UInt16>( index ); }
    else if ( type == typeid( kvs::UInt32 ) ) { v << this->at<kvs::UInt32>( index ); }
    else if ( type == typeid( kvs::UInt64 ) ) { v << this->at<kvs::UInt64>( index ); }
    else if ( type == typeid( kvs::Real32 ) ) { v << this->at<kvs::Real32>( index ); }
    else if ( type == typeid( kvs::Real64 ) ) { v << this->at<kvs::Real64>( index ); }
    else { kvsMessageError("Unsupported data type."); }

    return v.str();
}

template <> struct AnyValueArray::is_supported<kvs::Int8  > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt8 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Int16 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt16> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Int32 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt32> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Int64 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt64> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Real32> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Real64> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<std::string> : kvs::temporal::true_type {};

} // end of namespace kvs

#undef KVS_STATIC_ASSERT

namespace std
{

inline void swap( kvs::AnyValueArray& lhs, kvs::AnyValueArray& rhs )
{
    lhs.swap( rhs );
}

} // std

#endif // KVS__ANY_VALUE_ARRAY_H_INCLUDE
