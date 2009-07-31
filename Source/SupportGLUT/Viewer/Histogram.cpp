/****************************************************************************/
/**
 *  @file Histogram.cpp
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
#include <kvs/StructuredVolumeObject>
#include <kvs/String>
#include "../GLUT.h"
#include "Histogram.h"


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Histogram class.
 */
/*===========================================================================*/
Histogram::Histogram( void ):
    m_x( 0 ),
    m_y( 0 ),
    m_width( 100 ),
    m_height( 20 ),
    m_axis_width( 1.0f ),
    m_axis_color( kvs::RGBColor( 0, 0, 0 ) ),
    m_text_color( kvs::RGBColor( 0, 0, 0 ) ),
    m_background_color( kvs::RGBAColor( 0, 0, 0, 0.0f ) ),
    m_graph_color( kvs::RGBAColor( 0, 0, 0, 1.0f ) ),
    m_bias_parameter( 0.5f )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the Histogram class.
 */
/*===========================================================================*/
Histogram::~Histogram( void )
{
}

/*==========================================================================*/
/**
 *  @brief  Returns the x value of the histogram position.
 *  @return x value in the window coordinate system
 */
/*==========================================================================*/
const size_t Histogram::x( void ) const
{
    return( m_x );
}

/*==========================================================================*/
/**
 *  @brief  Returns the y value of the histogram position.
 *  @return y value in the window coordinate system
 */
/*==========================================================================*/
const size_t Histogram::y( void ) const
{
    return( m_y );
}

/*==========================================================================*/
/**
 *  @brief  Returns the graph width.
 *  @return width
 */
/*==========================================================================*/
const size_t Histogram::width( void ) const
{
    return( m_width );
}

/*==========================================================================*/
/**
 *  @breif  Returns the graph height.
 *  @return height
 */
/*==========================================================================*/
const size_t Histogram::height( void ) const
{
    return( m_height );
}

/*==========================================================================*/
/**
 *  @brief  Returns the frequency distribution table.
 *  @return frequency distribution table
 */
/*==========================================================================*/
const kvs::FrequencyTable& Histogram::table( void ) const
{
    return( m_table );
}

/*==========================================================================*/
/**
 *  @breif  Sets the graph position.
 *  @param  x [in] x value of the graph position
 *  @param  y [in] y value of the graph position
 */
/*==========================================================================*/
void Histogram::setPosition( const size_t x, const size_t y )
{
    m_x = x;
    m_y = y;
}

/*==========================================================================*/
/**
 *  @breif  Set the graph size.
 *  @param  width [in] graph width
 *  @param  height [in] graph height
 */
/*==========================================================================*/
void Histogram::setSize( const size_t width, const size_t height )
{
    m_width  = width;
    m_height = height;
}

/*==========================================================================*/
/**
 *  @brief  Sets the position and the size.
 *  @param  x [in] x value of the graph position
 *  @param  y [in] y value of the graph position
 *  @param  width [in] graph width
 *  @param  height [in] graph height
 */
/*==========================================================================*/
void Histogram::setGeometry( const size_t x, const size_t y, const size_t width, const size_t height )
{
    this->setPosition( x, y );
    this->setSize( width, height );
}

/*==========================================================================*/
/**
 *  @brief  Sets the axis width.
 *  @param  axis_width [in] axis width
 */
/*==========================================================================*/
void Histogram::setAxisWidth( const float axis_width )
{
    m_axis_width = axis_width;
}

/*==========================================================================*/
/**
 *  @breif  Sets the axis color.
 *  @param  axis_color [in] axis color
 */
/*==========================================================================*/
void Histogram::setAxisColor( const kvs::RGBColor& axis_color )
{
    m_axis_color = axis_color;
}

/*==========================================================================*/
/**
 *  @brief  Sets the text color.
 *  @param  text_color [in] text color
 */
/*==========================================================================*/
void Histogram::setTextColor( const kvs::RGBColor& text_color )
{
    m_text_color = text_color;
}

/*==========================================================================*/
/**
 *  @breif  Sets the background color.
 *  @param  background_color [in] background color
 */
/*==========================================================================*/
void Histogram::setBackgroundColor( const kvs::RGBAColor& background_color )
{
    m_background_color = background_color;
}

/*==========================================================================*/
/**
 *  @brief  Sets the graph color.
 *  @param  graph_color [in] graph color
 */
/*==========================================================================*/
void Histogram::setGraphColor( const kvs::RGBAColor& graph_color )
{
    m_graph_color = graph_color;
}

/*===========================================================================*/
/**
 *  @brief  Sets a bias parameter.
 *  @param  bias_parameter [in] bias parameter for the bias function
 */
/*===========================================================================*/
void Histogram::setBiasParameter( const float bias_parameter )
{
    /* Bias function: b(f,g) = f^{ln(g)/ln(0.5)}
     *   f: frequecny count that is normalized in [0,1]
     *   g: bias parameter in [0,1]
     */
    m_bias_parameter = kvs::Math::Clamp( bias_parameter, 0.0f, 1.0f );
}

/*==========================================================================*/
/**
 *  @brief  Sets the ignore value.
 *  @param  value [in] ignore value
 */
/*==========================================================================*/
void Histogram::setIgnoreValue( const kvs::Real64 value )
{
    m_table.setIgnoreValue( value );
}

/*==========================================================================*/
/**
 *  @brief  Sets the object and create the frequency distribution table.
 *  @param  volume [in] pointer to the object
 */
/*==========================================================================*/
void Histogram::setObject( const kvs::StructuredVolumeObject* volume )
{
    m_table.create( volume );
    m_histogram_texture.release();
}

/*==========================================================================*/
/**
 *  @brief  Sets the object and create the frequency distribution table.
 *  @param  image [in] pointer to the object
 */
/*==========================================================================*/
void Histogram::setObject( const kvs::ImageObject* image )
{
    m_table.create( image );
    m_histogram_texture.release();
}

/*==========================================================================*/
/**
 *  @brief  Draws the histogram.
 */
/*==========================================================================*/
void Histogram::draw( void )
{
    int vp[4]; glGetIntegerv( GL_VIEWPORT, (GLint*)vp );
    const int left   = vp[0];
    const int bottom = vp[1];
    const int right  = vp[2];
    const int top    = vp[3];

    if ( !glIsTexture( m_histogram_texture.id() ) )
    {
        this->create_histogram_texture();
    }

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    {
        glLoadIdentity();

        glMatrixMode( GL_PROJECTION );
        glPushMatrix();
        {
            glLoadIdentity();

            const float front = 0.0f;
            const float back = 2000.0f;
            glOrtho( left, right, bottom, top, front, back );

            this->draw_background();
            this->draw_frequency();
            this->draw_axis();
            this->draw_string();
        }
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
    }
    glPopMatrix();

    glPopAttrib();
}

/*==========================================================================*/
/**
 *  @breif  Draws the axis.
 */
/*==========================================================================*/
void Histogram::draw_axis( void )
{
    glLineWidth( m_axis_width );
    glBegin( GL_LINE_STRIP );
    glColor3ub( m_axis_color.r(), m_axis_color.g(), m_axis_color.b() );
    glVertex2f( static_cast<GLfloat>(m_x), static_cast<GLfloat>(m_y + m_height) );
    glVertex2f( static_cast<GLfloat>(m_x), static_cast<GLfloat>(m_y) );
    glVertex2f( static_cast<GLfloat>(m_x + m_width), static_cast<GLfloat>(m_y) );
    glEnd();
}

/*==========================================================================*/
/**
 *  @brief  Draws the background.
 */
/*==========================================================================*/
void Histogram::draw_background( void )
{
    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    glEnable( GL_BLEND );
    glDisable( GL_TEXTURE_2D );

    glBegin( GL_POLYGON );
    glColor4ub( m_background_color.r(),
                m_background_color.g(),
                m_background_color.b(),
                kvs::UInt8( m_background_color.a() * 255.0f ) );
    glVertex2f( static_cast<GLfloat>(m_x), static_cast<GLfloat>(m_y + m_height) );
    glVertex2f( static_cast<GLfloat>(m_x), static_cast<GLfloat>(m_y) );
    glVertex2f( static_cast<GLfloat>(m_x + m_width), static_cast<GLfloat>(m_y) );
    glVertex2f( static_cast<GLfloat>(m_x + m_width), static_cast<GLfloat>(m_y + m_height) );
    glEnd();

    glPopAttrib();
}

/*==========================================================================*/
/**
 *  @brief  Draws the frequency distribution graph.
 */
/*==========================================================================*/
void Histogram::draw_frequency( void )
{
    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    const GLfloat x = m_x;
    const GLfloat y = m_y;
    const GLfloat width = static_cast<GLfloat>( m_width );
    const GLfloat height = static_cast<GLfloat>( m_height );

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    m_histogram_texture.bind();
    {
        glBegin( GL_QUADS );
        {
            glTexCoord2f( 0.0f, 0.0f ); glVertex2f( x,         y );
            glTexCoord2f( 1.0f, 0.0f ); glVertex2f( x + width, y );
            glTexCoord2f( 1.0f, 1.0f ); glVertex2f( x + width, y + height );
            glTexCoord2f( 0.0f, 1.0f ); glVertex2f( x,         y + height );
        }
        glEnd();
    }
    m_histogram_texture.unbind();
}

/*==========================================================================*/
/**
 *  @brief  Draws the string.
 */
/*==========================================================================*/
void Histogram::draw_string( void )
{
    glColor3ub( m_text_color.r(), m_text_color.g(), m_text_color.b() );
    {
        // Min value.
        kvs::String min_value( m_table.minRange() );
        glRasterPos2i( m_x - 4 * min_value.size(), m_y - 13 );
        for ( size_t i = 0; i < min_value.size(); i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *( min_value.toStdString().c_str() + i ) );
        }
        // Max value.
        kvs::String max_value( m_table.maxRange() );
        glRasterPos2i( m_x + m_width - 4 * max_value.size(), m_y - 13 );
        for ( size_t i = 0; i < max_value.size(); i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *( max_value.toStdString().c_str() + i ) );
        }
    }
}

/*===========================================================================*/
/**
 *  @brief  Returns the histogram image.
 */
/*===========================================================================*/
const kvs::ValueArray<kvs::UInt8> Histogram::get_histogram_image( void ) const
{
    const size_t nchannels = 4;
    const size_t width = m_table.nbins();
    const size_t height = width;
    const size_t npixels = width * height;

    kvs::ValueArray<kvs::UInt8> data( npixels * nchannels );
    data.fill( 0x00 );

    const float g = m_bias_parameter;
    const kvs::Real32 normalized_factor = 1.0f / ( m_table.maxCount() );
    for ( size_t i = 0; i < width; i++ )
    {
        const size_t n = m_table.bin().at(i); // frequency count
        const float f = n * normalized_factor; // normalized frequency count in [0,1]
        const float b = std::pow( f, static_cast<float>( std::log(g) / std::log(0.5) ) );

        const size_t h = static_cast<size_t>( b * height + 0.5f );
        for ( size_t j = 0; j < h; j++ )
        {
            const size_t index = i + j * width;
            data[ 4 * index + 0 ] = m_graph_color.r();
            data[ 4 * index + 1 ] = m_graph_color.g();
            data[ 4 * index + 2 ] = m_graph_color.b();
            data[ 4 * index + 3 ] = static_cast<kvs::UInt8>( m_graph_color.a() * 255.0f );
        }
    }

    return( data );
}

/*===========================================================================*/
/**
 *  @brief  Creates the histogram texture.
 */
/*===========================================================================*/
void Histogram::create_histogram_texture( void )
{
    const size_t nchannels = 4;
    const size_t width = m_table.nbins();
    const size_t height = width;

    m_histogram_texture.setPixelFormat( nchannels, sizeof( kvs::UInt8 ) );
    m_histogram_texture.setMinFilter( GL_NEAREST );
    m_histogram_texture.setMagFilter( GL_NEAREST );
    m_histogram_texture.create( width, height );
    m_histogram_texture.download( width, height, this->get_histogram_image().pointer() );
}

/*===========================================================================*/
/**
 *  @brief  Updates the histogram texture.
 */
/*===========================================================================*/
void Histogram::update_histogram_texture( void )
{
    m_histogram_texture.release();
    this->create_histogram_texture();
}

} // end of namesapce glut

} // end of namespace kvs
