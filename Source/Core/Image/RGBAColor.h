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
#ifndef KVS__RGBA_COLOR_H_INCLUDE
#define KVS__RGBA_COLOR_H_INCLUDE

#include "RGBColor.h"
#include <kvs/Type>


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

    RGBAColor( float opacity = 1.0f );
    RGBAColor( kvs::UInt8 red, kvs::UInt8 greeb, kvs::UInt8 blue, float opacity = 1.0f );
    RGBAColor( const kvs::UInt8 rgb[3], float opacity = 1.0f );
    RGBAColor( const kvs::RGBColor& rgb, float opacity = 1.0f );

public:

    RGBAColor& operator = ( const RGBAColor& rgba );
    RGBAColor& operator = ( const RGBColor& rgb );

public:

    float a() const;
    float alpha() const;
    float opacity() const;
};

} // end of namespace kvs

#endif // KVS__RGBA_COLOR_H_INCLUDE
