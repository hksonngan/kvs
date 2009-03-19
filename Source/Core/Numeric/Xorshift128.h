/****************************************************************************/
/**
 *  @file Xorshift128.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_XORSHIFT_128_H_INCLUDE
#define KVS_CORE_XORSHIFT_128_H_INCLUDE

#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Xorshift128 class.
 */
/*==========================================================================*/
class Xorshift128
{
    kvsClassName_without_virtual( Xorshift128 );

private:

    unsigned long m_x;
    unsigned long m_y;
    unsigned long m_z;
    unsigned long m_w;

public:

    Xorshift128( void );

public:

    void setSeed( unsigned long );

public:

    const float rand( void );

public:

    const float operator ()( void );
};

/*==========================================================================*/
/**
 *  .
 *
 *  @return TODO
 */
/*==========================================================================*/
inline const float Xorshift128::rand( void )
{
    const float t24 = 1.0 / 16777216.0; /* 0.5**24 */

    unsigned long t = ( m_x ^ ( m_x << 11 ) );

    m_x = m_y;
    m_y = m_z;
    m_z = m_w;
    m_w = ( m_w ^ ( m_w >> 19 ) ) ^ ( t ^ ( t >> 8 ) );

    return( t24 * static_cast<float>( m_w >> 8 ) );
}

/*==========================================================================*/
/**
 *  .
 *
 *  @return TODO
 */
/*==========================================================================*/
inline const float Xorshift128::operator ()( void )
{
    return( this->rand() );
}

} // end of namespace kvs

#endif // KVS_CORE_XORSHIFT_128_H_INCLUDE
