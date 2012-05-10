/****************************************************************************/
/**
 *  @file Type.h
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
#ifndef KVS_CORE_TYPE_H_INCLUDE
#define KVS_CORE_TYPE_H_INCLUDE

#include <typeinfo>
#include <kvs/Compiler>
#include <kvs/Platform>


#include <string>

namespace kvs
{

typedef char           Int8;
typedef unsigned char  UInt8;
typedef short          Int16;
typedef unsigned short UInt16;
typedef int            Int32;
typedef unsigned int   UInt32;

#if defined ( KVS_COMPILER_VC )
typedef signed __int64   Int64;
typedef unsigned __int64 UInt64;
#else
#if defined ( KVS_PLATFORM_CPU_64 ) // LP64
typedef long          Int64;
typedef unsigned long UInt64;
#else                               // LLP64
typedef long long          Int64;
typedef unsigned long long UInt64;
#endif
#endif

typedef float       Real32;
typedef double      Real64;
#if KVS_ENABLE_DEPRECATED
typedef long double Real128;
#endif


class Type
{
public:
    enum TypeID
    {
        TypeInt8,
        TypeInt16,
        TypeInt32,
        TypeInt64,
        TypeUInt8,
        TypeUInt16,
        TypeUInt32,
        TypeUInt64,
        TypeReal32,
        TypeReal64,
#if KVS_ENABLE_DEPRECATED
        TypeString,
#endif
        UnknownType
    };

    template <typename T>
    static TypeID GetID()
    {
        return UnknownType;
    }

    static TypeID GetID( const std::type_info& type )
    {
        if (      type == typeid( kvs::Int8   ) ) return TypeInt8;
        else if ( type == typeid( kvs::Int16  ) ) return TypeInt16;
        else if ( type == typeid( kvs::Int32  ) ) return TypeInt32;
        else if ( type == typeid( kvs::Int64  ) ) return TypeInt64;
        else if ( type == typeid( kvs::UInt8  ) ) return TypeUInt8;
        else if ( type == typeid( kvs::UInt16 ) ) return TypeUInt16;
        else if ( type == typeid( kvs::UInt32 ) ) return TypeUInt32;
        else if ( type == typeid( kvs::UInt64 ) ) return TypeUInt64;
        else if ( type == typeid( kvs::Real32 ) ) return TypeReal32;
        else if ( type == typeid( kvs::Real64 ) ) return TypeReal64;
#if KVS_ENABLE_DEPRECATED
        else if ( type == typeid( std::string ) ) return TypeString;
#endif
        return UnknownType;
    }
};

template <> inline Type::TypeID Type::GetID<kvs::Int8  >() { return TypeInt8;   }
template <> inline Type::TypeID Type::GetID<kvs::Int16 >() { return TypeInt16;  }
template <> inline Type::TypeID Type::GetID<kvs::Int32 >() { return TypeInt32;  }
template <> inline Type::TypeID Type::GetID<kvs::Int64 >() { return TypeInt64;  }
template <> inline Type::TypeID Type::GetID<kvs::UInt8 >() { return TypeUInt8;  }
template <> inline Type::TypeID Type::GetID<kvs::UInt16>() { return TypeUInt16; }
template <> inline Type::TypeID Type::GetID<kvs::UInt32>() { return TypeUInt32; }
template <> inline Type::TypeID Type::GetID<kvs::UInt64>() { return TypeUInt64; }
template <> inline Type::TypeID Type::GetID<kvs::Real32>() { return TypeReal32; }
template <> inline Type::TypeID Type::GetID<kvs::Real64>() { return TypeReal64; }
#if KVS_ENABLE_DEPRECATED
template <> inline Type::TypeID Type::GetID<std::string>() { return TypeString; }
#endif

} // end of namespace kvs

#if KVS_ENABLE_DEPRECATED

#if defined ( KVS_PLATFORM_CPU_32 )      // ILP32
#define KVS_TYPE_SIZEOF_CHAR        1
#define KVS_TYPE_SIZEOF_SHORT       2
#define KVS_TYPE_SIZEOF_INT         4
#define KVS_TYPE_SIZEOF_LONG        4
#define KVS_TYPE_SIZEOF_LONG_LONG   8
#define KVS_TYPE_SIZEOF_FLOAT       4
#define KVS_TYPE_SIZEOF_DOUBLE      8
#define KVS_TYPE_SIZEOF_LONG_DOUBLE 16
#define KVS_TYPE_SIZEOF_POINTER     4
#else // KVS_PLATFORM_CPU_64
#if defined ( KVS_COMPILER_VC ) // LLP64
#define KVS_TYPE_SIZEOF_CHAR        1
#define KVS_TYPE_SIZEOF_SHORT       2
#define KVS_TYPE_SIZEOF_INT         4
#define KVS_TYPE_SIZEOF_LONG        4
#define KVS_TYPE_SIZEOF_LONG_LONG   8
#define KVS_TYPE_SIZEOF_FLOAT       4
#define KVS_TYPE_SIZEOF_DOUBLE      8
#define KVS_TYPE_SIZEOF_LONG_DOUBLE 16
#define KVS_TYPE_SIZEOF_POINTER     8
#else // KVS_COMPILER_GCC      // LP64
#define KVS_TYPE_SIZEOF_CHAR        1
#define KVS_TYPE_SIZEOF_SHORT       2
#define KVS_TYPE_SIZEOF_INT         4
#define KVS_TYPE_SIZEOF_LONG        8
#define KVS_TYPE_SIZEOF_LONG_LONG   8
#define KVS_TYPE_SIZEOF_FLOAT       4
#define KVS_TYPE_SIZEOF_DOUBLE      8
#define KVS_TYPE_SIZEOF_LONG_DOUBLE 16
#define KVS_TYPE_SIZEOF_POINTER     8
#endif
#endif

#endif

#endif // KVS_CORE_TYPE_H_INCLUDE
