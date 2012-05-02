/****************************************************************************/
/**
 *  @file BitArray.h
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
#ifndef KVS__BIT_ARRAY_H_INCLUDE
#define KVS__BIT_ARRAY_H_INCLUDE

#include <iostream>
#include <vector>

#include <kvs/Type>
#include <kvs/ClassName>


namespace kvs
{

class ReferenceCounter;

/*==========================================================================*/
/**
 *  Bit array class
 */
/*==========================================================================*/
class BitArray
{
    kvsClassName( kvs::BitArray );

protected:

    kvs::ReferenceCounter* m_counter; ///< reference counter
    size_t                 m_nvalues; ///< number of values
    kvs::UInt8*            m_values;  ///< value array (bit array)

public:

    BitArray();

    BitArray( const size_t nvalues );

    BitArray( const kvs::UInt8* values, const size_t nvalues );

    BitArray( const bool* values, const size_t nvalues );

    BitArray( const BitArray& other );

    virtual ~BitArray();

public:

    bool operator [] ( size_t index ) const;

    BitArray& operator = ( const BitArray& other );

    BitArray& operator &= ( const BitArray& other );

    BitArray& operator |= ( const BitArray& other );

    BitArray& operator ^= ( const BitArray& other );

public:

    void set();

    void set( size_t index );

    void reset();

    void reset( size_t index );

    void flip();

    void flip( size_t index );

    size_t count() const;

    bool test( size_t index ) const;

public:

    size_t size() const;

    size_t byteSize() const;

    size_t bitSize() const;

    size_t paddingBit() const;

    const void* pointer() const;

    void* pointer();

    void shallowCopy( const BitArray& other );

    void deepCopy( const BitArray& other );

    void deepCopy( const kvs::UInt8* values, const size_t nvalues );

    void deepCopy( const bool* values, const size_t nvalues );

public:

    kvs::UInt8* allocate( size_t nvalues );

    void deallocate();

protected:

    void create_counter();

    void ref();

    void unref();
};

} // end of namespace kvs

#endif // KVS__BIT_ARRAY_H_INCLUDE
