/****************************************************************************/
/**
 *  @file Histogram.h
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
#ifndef KVS_SUPPORT_GLUT_HISTOGRAM_H_INCLUDE
#define KVS_SUPPORT_GLUT_HISTOGRAM_H_INCLUDE

#include <kvs/StructuredVolumeObject>
#include <kvs/ImageObject>
#include <kvs/RGBColor>
#include <kvs/RGBAColor>
#include <kvs/FrequencyTable>
#include <kvs/Texture2D>
#include <kvs/ClassName>


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
 *  Histogram class.
 */
/*==========================================================================*/
class Histogram
{
    kvsClassName( Histogram );

protected:

    size_t              m_x; ///< bar position x
    size_t              m_y; ///< bar position y
    size_t              m_width; ///< bar width
    size_t              m_height; ///< bar height
    float               m_axis_width; ///< axis width
    kvs::RGBColor       m_axis_color; ///< axis color
    kvs::RGBColor       m_text_color; ///< text color
    kvs::RGBAColor      m_background_color; ///< background color
    kvs::RGBAColor      m_graph_color; ///< graph color
    float               m_bias_parameter; ///< bias parameter
    kvs::Texture2D      m_histogram_texture; ///< histogram texture
    kvs::FrequencyTable m_table; ///< frequency distribution table

public:

    Histogram( void );

    virtual ~Histogram( void );

public:

    const size_t x( void ) const;

    const size_t y( void ) const;

    const size_t width( void ) const;

    const size_t height( void ) const;

    const kvs::FrequencyTable& table( void ) const;

public:

    void setPosition( const size_t x, const size_t y );

    void setSize( const size_t width, const size_t height );

    void setGeometry( const size_t x, const size_t y, const size_t width, const size_t height );

    void setAxisWidth( const float axis_width );

    void setAxisColor( const kvs::RGBColor& axis_color );

    void setTextColor( const kvs::RGBColor& text_color );

    void setBackgroundColor( const kvs::RGBAColor& background_color );

    void setGraphColor( const kvs::RGBAColor& graph_color );

    void setBiasParameter( const float bias_parameter );

    void setIgnoreValue( const kvs::Real64 value );

    void setObject( const kvs::StructuredVolumeObject* volume );

    void setObject( const kvs::ImageObject* image );

public:

    void draw( void );

private:

    void draw_axis( void );

    void draw_background( void );

    void draw_frequency( void );

    void draw_string( void );

    const kvs::ValueArray<kvs::UInt8> get_histogram_image( void ) const;

    void create_histogram_texture( void );

    void update_histogram_texture( void );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_HISTOGRAM_H_INCLUDE
