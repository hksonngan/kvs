/****************************************************************************/
/**
 *  @file Endian.h
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
#ifndef KVS_CORE_ENDIAN_H_INCLUDE
#define KVS_CORE_ENDIAN_H_INCLUDE

#include "Type.h"


namespace kvs
{

namespace Endian
{

namespace
{

inline void Swap2Bytes( volatile void* value )
{
    volatile unsigned char* v   = static_cast<volatile unsigned char*>( value );
    unsigned char           tmp = v[0]; v[0] = v[1]; v[1] = tmp;
}

inline void Swap4Bytes( volatile void* value )
{
    volatile unsigned char* v    = static_cast<volatile unsigned char*>( value );
    unsigned char           tmp1 = v[0]; v[0] = v[3]; v[3] = tmp1;
    unsigned char           tmp2 = v[1]; v[1] = v[2]; v[2] = tmp2;
}

inline void Swap8Bytes( volatile void* value )
{
    volatile unsigned char* v    = static_cast<volatile unsigned char*>( value );
    unsigned char           tmp1 = v[0]; v[0] = v[7]; v[7] = tmp1;
    unsigned char           tmp2 = v[1]; v[1] = v[6]; v[6] = tmp2;
    unsigned char           tmp3 = v[2]; v[2] = v[5]; v[5] = tmp3;
    unsigned char           tmp4 = v[3]; v[3] = v[4]; v[4] = tmp4;
}

inline void Swap2Bytes( volatile void* value, int n )
{
    volatile unsigned char* v = static_cast<volatile unsigned char*>( value );
    for ( int i = 0; i < n; i++ )
    {
        Swap2Bytes( v ); v += 2;
    }
}

inline void Swap4Bytes( volatile void* value, int n )
{
    volatile unsigned char* v = static_cast<volatile unsigned char*>( value );
    for ( int i = 0; i < n; i++ )
    {
        Swap4Bytes( v ); v += 4;
    }
}

inline void Swap8Bytes( volatile void* value, int n )
{
    volatile unsigned char* v = static_cast<volatile unsigned char*>( value );
    for ( int i = 0; i < n; i++ )
    {
        Swap8Bytes( v ); v += 8;
    }
}

} // end of namespace

enum ByteOrder
{
    Unknown = -1,
    Little  =  0,
    Big     =  1
};

inline ByteOrder Check( void )
{
    ByteOrder ret = Unknown;

    int i = 1;
    if ( *( (char*)&i ) ) { ret = Little; }
    else if ( *( (char*)&i + ( sizeof( int ) - 1 ) ) ) { ret = Big; }

    return( ret );
}

inline bool IsBig( void )
{
    int i = 1;
    return( *( (char*)&i ) == 0 );
}

inline bool IsLittle( void )
{
    int i = 1;
    return( *( (char*)&i ) != 0 );
}

inline void Swap( kvs::Int8& )
{
}

inline void Swap( kvs::UInt8& )
{
}

inline void Swap( kvs::Int16& value )
{
    Swap2Bytes( &value );
}

inline void Swap( kvs::UInt16& value )
{
    Swap2Bytes( &value );
}

inline void Swap( kvs::Int32& value )
{
    Swap4Bytes( &value );
}

inline void Swap( kvs::UInt32& value )
{
    Swap4Bytes( &value );
}

inline void Swap( kvs::Int64& value )
{
    Swap8Bytes( &value );
}

inline void Swap( kvs::UInt64& value )
{
    Swap8Bytes( &value );
}

inline void Swap( kvs::Real32& value )
{
    Swap4Bytes( &value );
}

inline void Swap( kvs::Real64& value )
{
    Swap8Bytes( &value );
}

inline void Swap( kvs::Int8*, int )
{
}

inline void Swap( kvs::UInt8*, int )
{
}

inline void Swap( kvs::Int16* value, int n )
{
    Swap2Bytes( value, n );
}

inline void Swap( kvs::UInt16* value, int n )
{
    Swap2Bytes( value, n );
}

inline void Swap( kvs::Int32* value, int n )
{
    Swap4Bytes( value, n );
}

inline void Swap( kvs::UInt32* value, int n )
{
    Swap4Bytes( value, n );
}

inline void Swap( kvs::Int64* value, int n )
{
    Swap8Bytes( value, n );
}

inline void Swap( kvs::UInt64* value, int n )
{
    Swap8Bytes( value, n );
}

inline void Swap( kvs::Real32* value, int n )
{
    Swap4Bytes( value, n );
}

inline void Swap( kvs::Real64* value, int n )
{
    Swap8Bytes( value, n );
}

};

} // end of namespace kvs

#endif // KVS_CORE_ENDIAN_H_INCLUDE
