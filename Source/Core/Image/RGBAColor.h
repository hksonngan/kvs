/****************************************************************************/
/**
 *  @file RGBAColor.h
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
#ifndef KVS_CORE_RGBA_COLOR_H_INCLUDE
#define KVS_CORE_RGBA_COLOR_H_INCLUDE

#include <kvs/Type>
#include "RGBColor.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  RGB-a color class.
 */
/*==========================================================================*/
class RGBAColor : public kvs::RGBColor
{
protected:

    float m_opacity; ///< opacity [0-1]

public:

    RGBAColor( float opacity = 0.0 );

    RGBAColor( kvs::UInt8 red, kvs::UInt8 greeb, kvs::UInt8 blue, float opacity = 0.0 );

    RGBAColor( const kvs::UInt8 rgb[3], float opacity = 0.0 );

    RGBAColor( const kvs::RGBColor& rgb, float opacity = 0.0 );

public:

    RGBAColor& operator = ( const RGBAColor& rgba );

    RGBAColor& operator = ( const RGBColor& rgb );

public:

    const float a( void ) const;

    const float alpha( void ) const;

    const float opacity( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_RGBA_COLOR_H_INCLUDE
