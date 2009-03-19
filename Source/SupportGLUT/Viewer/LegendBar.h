/****************************************************************************/
/**
 *  @file LegendBar.h
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
#ifndef KVS_SUPPORT_GLUT_LEGEND_BAR_H_INCLUDE
#define KVS_SUPPORT_GLUT_LEGEND_BAR_H_INCLUDE

#include <string>
#include <kvs/ColorMap>
#include <kvs/RGBColor>
#include <kvs/Texture2D>
#include <kvs/ClassName>


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
 *  Legend bar class.
 */
/*==========================================================================*/
class LegendBar
{
    kvsClassName( LegendBar );

public:

    enum OrientationType
    {
        Horizontal = 0, ///< horizontal bar
        Vertical        ///< vertical bar
    };

protected:

    std::string     m_title;        ///< title
    size_t          m_x;            ///< bar position x
    size_t          m_y;            ///< bar position y
    size_t          m_width;        ///< bar width
    size_t          m_height;       ///< bar height
    OrientationType m_orientation;  ///< bar layout
    size_t          m_ndivisions;   ///< number of divisions of the bar
    float           m_division_line_width; ///< division line width
    kvs::RGBColor   m_division_line_color; ///< division line color
    double          m_min_value;    ///< min. value
    double          m_max_value;    ///< max. value
    float           m_border_width; ///< border line width
    kvs::RGBColor   m_border_color; ///< border line color
    kvs::RGBColor   m_text_color;   ///< text color
    kvs::ColorMap   m_colormap;     ///< color map
    kvs::Texture2D  m_texture;      ///< texture data
    bool m_enable_anti_aliasing; ///< check flag for anti-aliasing

public:

    LegendBar( void );

    virtual ~LegendBar( void );

public:

    const std::string& title( void ) const;

    const size_t x( void ) const;

    const size_t y( void ) const;

    const size_t width( void ) const;

    const size_t height( void ) const;

public:

    void setTitle( const std::string& title );

    void setPosition( const size_t x, const size_t y );

    void setSize( const size_t width, const size_t height );

    void setGeometry( const size_t x, const size_t y, const size_t width, const size_t height );

    void setOrientation( const OrientationType orientation );

    void setNDivisions( const size_t ndivisions );

    void setDivisionLineWidth( const float division_line_width );

    void setDivisionLineColor( const kvs::RGBColor& division_line_color );

    void setMinValue( const double min_value );

    void setMaxValue( const double max_value );

    void setBorderWidth( const float border_width );

    void setBorderColor( const kvs::RGBColor& border_color );

    void setTextColor( const kvs::RGBColor& text_color );

    void setColorMap( const kvs::ColorMap& colormap );

    void enableAntiAliasing( void );

    void disableAntiAliasing( void );

public:

    void draw( void );

private:

    void create_texture( void );

    void release_texture( void );

    void draw_texture( void );

    void draw_border( void );

    void draw_string( void );
};

} // end of namesapce glut

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_LEGEND_BAR_H_INCLUDE
