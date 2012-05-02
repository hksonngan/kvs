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
#include <utility>
#if KVS_ENABLE_DEPRECATED
#include <string>
#endif
#include <kvs/Type>
#include <kvs/SharedPointer>
#include <kvs/ValueArray>
#include <kvs/ClassName>
#if KVS_ENABLE_DEPRECATED
#include <kvs/Endian>
#include <kvs/String>
#endif
#include <kvs/Platform>
#include <kvs/Compiler>


namespace kvs
{

namespace temporal
{

class TypeInfo
{
public:
    TypeInfo()
    {
        m_id = kvs::Type::UnknownType;
    }

public:
    const std::type_info& type() const
    {
        switch ( m_id )
        {
        case kvs::Type::TypeInt8:   return typeid( kvs::Int8   );
        case kvs::Type::TypeInt16:  return typeid( kvs::Int16  );
        case kvs::Type::TypeInt32:  return typeid( kvs::Int32  );
        case kvs::Type::TypeInt64:  return typeid( kvs::Int64  );
        case kvs::Type::TypeUInt8:  return typeid( kvs::UInt8  );
        case kvs::Type::TypeUInt16: return typeid( kvs::UInt16 );
        case kvs::Type::TypeUInt32: return typeid( kvs::UInt32 );
        case kvs::Type::TypeUInt64: return typeid( kvs::UInt64 );
        case kvs::Type::TypeReal32: return typeid( kvs::Real32 );
        case kvs::Type::TypeReal64: return typeid( kvs::Real64 );
#if KVS_ENABLE_DEPRECATED
        case kvs::Type::TypeString: return typeid( std::string );
#endif
        }
        KVS_ASSERT( false );
        return typeid( void );
    }

    const char* typeName() const
    {
        switch ( m_id )
        {
        case kvs::Type::TypeInt8:  return "char";
        case kvs::Type::TypeInt16: return "short";
        case kvs::Type::TypeInt32: return "int";
        case kvs::Type::TypeInt64:
    #if defined ( KVS_COMPILER_VC )
        return "signed __int64";
    #else
    #if defined ( KVS_PLATFORM_CPU_64 ) // LP64
        return "long";
    #else
        return "long long";
    #endif
    #endif
        case kvs::Type::TypeUInt8:  return "unsigned char";
        case kvs::Type::TypeUInt16: return "unsigned short";
        case kvs::Type::TypeUInt32: return "unsigned int";
        case kvs::Type::TypeUInt64:
    #if defined ( KVS_COMPILER_VC )
        return "unsigned __int64";
    #else
    #if defined ( KVS_PLATFORM_CPU_64 ) // LP64
        return "unsigned long";
    #else
        return "unsigned long long";
    #endif
    #endif
        case kvs::Type::TypeReal32: return "float";
        case kvs::Type::TypeReal64: return "double";
#if KVS_ENABLE_DEPRECATED
        case kvs::Type::TypeString: return "string";
#endif
        }
        KVS_ASSERT( false );
        return NULL;
    }

    void setid( kvs::Type::TypeID id )
    {
        m_id = id;
    }

private:
    kvs::Type::TypeID m_id;
}; // TypeInfo


template <typename T, T Value>
struct integral_constant
{
    static const T value = Value;
    typedef T value_type;
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

} // temporal

namespace detail
{

class ValueGetter
{
public:
    template <typename ReturnT>
    static ReturnT Get( const void* ptr, kvs::Type::TypeID id )
    {
        KVS_ASSERT( id != kvs::Type::UnknownType );
        switch ( id )
        {
        case kvs::Type::TypeInt8:   return GetValue<ReturnT, kvs::Int8>  ( ptr );
        case kvs::Type::TypeInt16:  return GetValue<ReturnT, kvs::Int16> ( ptr );
        case kvs::Type::TypeInt32:  return GetValue<ReturnT, kvs::Int32> ( ptr );
        case kvs::Type::TypeInt64:  return GetValue<ReturnT, kvs::Int64> ( ptr );
        case kvs::Type::TypeUInt8:  return GetValue<ReturnT, kvs::UInt8> ( ptr );
        case kvs::Type::TypeUInt16: return GetValue<ReturnT, kvs::UInt16>( ptr );
        case kvs::Type::TypeUInt32: return GetValue<ReturnT, kvs::UInt32>( ptr );
        case kvs::Type::TypeUInt64: return GetValue<ReturnT, kvs::UInt64>( ptr );
        case kvs::Type::TypeReal32: return GetValue<ReturnT, kvs::Real32>( ptr );
        case kvs::Type::TypeReal64: return GetValue<ReturnT, kvs::Real64>( ptr );
#if KVS_DEPRECATED
        case kvs::Type::TypeString: return GetValueFromString<ReturnT>( ptr );
#endif
        }
        return ReturnT();
    }

private:
    template <typename ReturnT, typename DataT>
    static ReturnT GetValue( const void* ptr )
    {
        return static_cast<ReturnT>( *static_cast<const DataT*>( ptr ) );
    }

#if KVS_ENABLE_DEPRECATED
    template <typename DataT>
    static std::string GetString( const void* ptr )
    {
        return kvs::String::ToString( *static_cast<const DataT*>( ptr ) );
    }

    template <typename ReturnT>
    static ReturnT GetValueFromString( const void* ptr )
    {
        const std::string& source = *static_cast<const std::string*>( ptr );
        return kvs::String::To<ReturnT>( source );
    }
#endif
private:
    ValueGetter();
}; // ValueGetter

#if KVS_ENABLE_DEPRECATED
template <>
inline std::string ValueGetter::Get<std::string>( const void* ptr, kvs::Type::TypeID id )
{
    KVS_ASSERT( id != kvs::Type::UnknownType );
    switch ( id )
    {
    case kvs::Type::TypeInt8:   return GetString<kvs::Int8>  ( ptr );
    case kvs::Type::TypeInt16:  return GetString<kvs::Int16> ( ptr );
    case kvs::Type::TypeInt32:  return GetString<kvs::Int32> ( ptr );
    case kvs::Type::TypeInt64:  return GetString<kvs::Int64> ( ptr );
    case kvs::Type::TypeUInt8:  return GetString<kvs::UInt8> ( ptr );
    case kvs::Type::TypeUInt16: return GetString<kvs::UInt16>( ptr );
    case kvs::Type::TypeUInt32: return GetString<kvs::UInt32>( ptr );
    case kvs::Type::TypeUInt64: return GetString<kvs::UInt64>( ptr );
    case kvs::Type::TypeReal32: return GetString<kvs::Real32>( ptr );
    case kvs::Type::TypeReal64: return GetString<kvs::Real64>( ptr );
    case kvs::Type::TypeString: return *static_cast<const std::string*>( ptr );
    }
    return std::string();
}
#endif

class AnyValueArrayElement
{
public:
    AnyValueArrayElement( const void* ptr, kvs::Type::TypeID type_id )
    {
        m_ptr = ptr;
        m_type_id = type_id;
    }

    template <typename T>
    const T to() const
    {
        return ValueGetter::Get<T>( m_ptr, m_type_id );
    }

private:
    const void* m_ptr;
    kvs::Type::TypeID m_type_id;
}; // AnyValueArrayElement

} //detail

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
    typedef kvs::temporal::TypeInfo TypeInfo;
    typedef kvs::detail::AnyValueArrayElement value_type;

private:
    kvs::SharedPointer<void> m_values;       ///< value array
    size_t    m_size_of_value; ///< byte size of a value
    size_t    m_size;       ///< number of values
    kvs::Type::TypeID m_type_id;

    TypeInfo m_type_info;

public:
    AnyValueArray()
    {
        m_size = 0;
        m_size_of_value = 0;
        m_type_id = kvs::Type::UnknownType;
    }

    template<typename T>
    explicit AnyValueArray( const kvs::ValueArray<T>& values )
    {
        KVS_STATIC_ASSERT( is_supported<T>::value, "not supported" );
        m_values        = kvs::static_pointer_cast<T>( values.getSharedPointer() );
        m_size          = values.size();
        m_size_of_value = sizeof( T );
        m_type_id       = kvs::Type::GetID<T>();
    }

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
        return kvs::ValueArray<T>( kvs::static_pointer_cast<T>( m_values ), this->size() );
    }

public:
    size_t size() const
    {
        return m_size;
    }

    size_t byteSize() const
    {
        return this->size() * m_size_of_value;
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
        std::swap( m_type_id, other.m_type_id );
    }

    AnyValueArray clone() const
    {
        switch ( this->typeID() )
        {
        case kvs::Type::TypeInt8:   return this->clone_helper<kvs::Int8  >();
        case kvs::Type::TypeInt16:  return this->clone_helper<kvs::Int16 >();
        case kvs::Type::TypeInt32:  return this->clone_helper<kvs::Int32 >();
        case kvs::Type::TypeInt64:  return this->clone_helper<kvs::Int64 >();
        case kvs::Type::TypeUInt8:  return this->clone_helper<kvs::UInt8 >();
        case kvs::Type::TypeUInt16: return this->clone_helper<kvs::UInt16>();
        case kvs::Type::TypeUInt32: return this->clone_helper<kvs::UInt32>();
        case kvs::Type::TypeUInt64: return this->clone_helper<kvs::UInt64>();
        case kvs::Type::TypeReal32: return this->clone_helper<kvs::Real32>();
        case kvs::Type::TypeReal64: return this->clone_helper<kvs::Real64>();
#if KVS_ENABLE_DEPRECATED
        case kvs::Type::TypeString: return this->clone_helper<std::string>();
#endif
        }
        KVS_ASSERT( false );
        return AnyValueArray();
    }

    bool empty() const
    {
        return this->size() == 0;
    }

    const value_type operator []( size_t index ) const
    {
        return value_type( static_cast<const char*>( this->data() ) + m_size_of_value * index, this->typeID() );
    }

    kvs::Type::TypeID typeID() const
    {
        return m_type_id;
    }

    // for compatibility.

    const TypeInfo* typeInfo() const
    {
        const_cast<AnyValueArray*>( this )->m_type_info.setid( this->typeID() );
        return &m_type_info;
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
        return ( *this )[ index ].to<T>();
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
        m_size = 0;
        m_size_of_value = 0;
        m_type_id = kvs::Type::UnknownType;
    }

    bool unique() const
    {
        return m_values.unique();
    }

private:
    template <typename T>
    AnyValueArray clone_helper() const
    {
        ValueArray<T> ret( static_cast<const T*>( this->data() ), this->size() );
        return AnyValueArray( ret );
    }

    template <typename T>
    bool check_type() const
    {
        return m_type_id == kvs::Type::GetID<T>();
    }

    template <typename T>
    struct is_supported : kvs::temporal::false_type {};
};

template <> struct AnyValueArray::is_supported<kvs::Int8  > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Int16 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Int32 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Int64 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt8 > : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt16> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt32> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::UInt64> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Real32> : kvs::temporal::true_type {};
template <> struct AnyValueArray::is_supported<kvs::Real64> : kvs::temporal::true_type {};
#if KVS_ENABLE_DEPRECATED
template <> struct AnyValueArray::is_supported<std::string> : kvs::temporal::true_type {};
#endif
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
