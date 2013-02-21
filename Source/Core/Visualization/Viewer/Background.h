/****************************************************************************/
/**
 *  @file Background.h
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
#ifndef KVS__BACKGROUND_H_INCLUDE
#define KVS__BACKGROUND_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/RGBAColor>


namespace kvs
{

/*==========================================================================*/
/**
 *  Background class.
 */
/*==========================================================================*/
class Background
{
    kvsClassName( kvs::Background );

public:

    enum Type
    {
        MonoColor = 0,    ///< mono color background
        TwoSideColor,     ///< gradation color background using two colors
        FourCornersColor, ///< gradation color background using four colors
//        Image             ///< image background
    };

protected:

    Type m_type;///< background type
    kvs::RGBAColor m_color[4]; ///< color on the corners
//    MipmapTexture2D m_mipmap;   ///< mipmap texture

public:

    Background();
    Background( const kvs::RGBAColor& color );
    Background( const kvs::RGBAColor& color1, const kvs::RGBAColor& color2 );
    Background( const kvs::RGBAColor& color0, const kvs::RGBAColor& color1,
                const kvs::RGBAColor& color2, const kvs::RGBAColor& color3 );
    virtual ~Background();

public:

    Background& operator = ( const Background& bg );

public:

    void setColor( const kvs::RGBAColor& color );
    void setColor( const kvs::RGBAColor& color0, const kvs::RGBAColor& color1 );
    void setColor( const kvs::RGBAColor& color0, const kvs::RGBAColor& color1,
                   const kvs::RGBAColor& color2, const kvs::RGBAColor& color3 );
//    void setImage( const ImageObject& image );

    const kvs::RGBColor& color( size_t index = 0 ) const;

    void apply();

private:

    void apply_mono_color();
    void apply_gradation_color();
//    void apply_image();
};

} // end of namespace kvs

#endif // KVS__BACKGROUND_H_INCLUDE
