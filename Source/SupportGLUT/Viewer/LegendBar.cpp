/****************************************************************************/
/**
 *  @file LegendBar.cpp
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
#include "LegendBar.h"
#include "../GLUT.h"
#include <kvs/Type>
#include <kvs/Message>
#include <kvs/String>


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
LegendBar::LegendBar( void ):
    m_title(""),
    m_x( 0 ),
    m_y( 0 ),
    m_width( 100 ),
    m_height( 20 ),
    m_orientation( LegendBar::Horizontal ),
    m_ndivisions( 0 ),
    m_division_line_width( 1.0f ),
    m_division_line_color( kvs::RGBColor( 0, 0, 0 ) ),
    m_min_value( 0 ),
    m_max_value( 100 ),
    m_border_width( 1.0f ),
    m_border_color( kvs::RGBColor( 0, 0, 0 ) ),
    m_text_color( kvs::RGBColor( 0, 0, 0 ) ),
    m_enable_anti_aliasing( false )
{
}

LegendBar::~LegendBar( void )
{
}

/*==========================================================================*/
/**
 *  Returns the title.
 */
/*==========================================================================*/
const std::string& LegendBar::title( void ) const
{
    return( m_title );
}

/*==========================================================================*/
/**
 *  Returns the x value of the bar position.
 *  @return x value in the window coordinate system
 */
/*==========================================================================*/
const size_t LegendBar::x( void ) const
{
    return( m_x );
}

/*==========================================================================*/
/**
 *  Returns the y value of the bar position.
 *  @return y value in the window coordinate system
 */
/*==========================================================================*/
const size_t LegendBar::y( void ) const
{
    return( m_y );
}

/*==========================================================================*/
/**
 *  Returns the bar width.
 *  @return width
 */
/*==========================================================================*/
const size_t LegendBar::width( void ) const
{
    return( m_width );
}

/*==========================================================================*/
/**
 *  Returns the bar height.
 *  @return height
 */
/*==========================================================================*/
const size_t LegendBar::height( void ) const
{
    return( m_height );
}

/*==========================================================================*/
/**
 *  Set the title.
 *  @param title [in] bar title
 */
/*==========================================================================*/
void LegendBar::setTitle( const std::string& title )
{
    m_title = title;
}

/*==========================================================================*/
/**
 *  Set the bar position.
 *  @param x [in] x value of the bar position
 *  @param y [in] y value of the bar position
 */
/*==========================================================================*/
void LegendBar::setPosition( const size_t x, const size_t y )
{
    m_x = x;
    m_y = y;
}

/*==========================================================================*/
/**
 *  Set the bar size.
 *  @param width [in] bar width
 *  @param height [in] bar height
 */
/*==========================================================================*/
void LegendBar::setSize( const size_t width, const size_t height )
{
    m_width  = width;
    m_height = height;
}

/*==========================================================================*/
/**
 *  Set the position and the size.
 *  @param x [in] x value of the bar position
 *  @param y [in] y value of the bar position
 *  @param width [in] bar width
 *  @param height [in] bar height
 */
/*==========================================================================*/
void LegendBar::setGeometry( const size_t x, const size_t y, const size_t width, const size_t height )
{
    this->setPosition( x, y );
    this->setSize( width, height );
}

/*==========================================================================*/
/**
 *  Set the bar orientation.
 *  @param orientation [in] bar orientation
 */
/*==========================================================================*/
void LegendBar::setOrientation( const OrientationType orientation )
{
    m_orientation = orientation;
}

/*==========================================================================*/
/**
 *  Set the number of divisions of the range.
 *  @param ndivisions [in] number of divisions
 */
/*==========================================================================*/
void LegendBar::setNDivisions( const size_t ndivisions )
{
    m_ndivisions = ndivisions;
}

/*===========================================================================*/
/**
 *  Sets the division line width.
 *  @param  division_line_width [in] division line width
 */
/*===========================================================================*/
void LegendBar::setDivisionLineWidth( const float division_line_width )
{
    m_division_line_width = division_line_width;
}

/*===========================================================================*/
/**
 *  Sets the division line color.
 *  @param  division_line_color [in] division line color
 */
/*===========================================================================*/
void LegendBar::setDivisionLineColor( const kvs::RGBColor& division_line_color )
{
    m_division_line_color = division_line_color;
}

/*==========================================================================*/
/**
 *  Set the min. value.
 *  @param min_value [in] min value
 */
/*==========================================================================*/
void LegendBar::setMinValue( const double min_value )
{
    m_min_value = min_value;
}

/*==========================================================================*/
/**
 *  Set the max. value.
 *  @param max_value [in] max value
 */
/*==========================================================================*/
void LegendBar::setMaxValue( const double max_value )
{
    m_max_value = max_value;
}

/*==========================================================================*/
/**
 *  Set the border width of the bar.
 *  @param border_width [in] border width
 */
/*==========================================================================*/
void LegendBar::setBorderWidth( const float border_width )
{
    m_border_width = border_width;
}

/*==========================================================================*/
/**
 *  Set the border color of the bar
 *  @param border_color [in] border color
 */
/*==========================================================================*/
void LegendBar::setBorderColor( const kvs::RGBColor& border_color )
{
    m_border_color = border_color;
}

/*==========================================================================*/
/**
 *  Set the text color.
 *  @param text_color [in] text color
 */
/*==========================================================================*/
void LegendBar::setTextColor( const kvs::RGBColor& text_color )
{
    m_text_color = text_color;
}

/*==========================================================================*/
/**
 *  Set the color map to the texture.
 *  @param colormap [in] color map
 */
/*==========================================================================*/
void LegendBar::setColorMap( const kvs::ColorMap& colormap )
{
    m_colormap = colormap;

    // The texture has been already dowloaded.
    if ( m_texture.id() != 0 ) this->release_texture();
}

/*===========================================================================*/
/**
 *  Enables anti-aliasing.
 */
/*===========================================================================*/
void LegendBar::enableAntiAliasing( void )
{
    m_enable_anti_aliasing = true;
}

/*===========================================================================*/
/**
 *  Disables anti-aliasing.
 */
/*===========================================================================*/
void LegendBar::disableAntiAliasing( void )
{
    m_enable_anti_aliasing = false;
}

/*==========================================================================*/
/**
 *  Draw the legend bar.
 */
/*==========================================================================*/
void LegendBar::draw( void )
{
    int vp[4]; glGetIntegerv( GL_VIEWPORT, (GLint*)vp );
    const int left   = vp[0];
    const int bottom = vp[1];
    const int right  = vp[2];
    const int top    = vp[3];

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    if ( !glIsTexture( m_texture.id() ) ) this->create_texture();

    glDisable( GL_LIGHTING );

    m_texture.bind();

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

            this->draw_texture();
            this->draw_border();
            this->draw_string();
        }
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
    }
    glPopMatrix();

    m_texture.unbind();

    glPopAttrib();
}

void LegendBar::create_texture( void )
{
    const size_t nchannels  = 3;
    m_texture.setPixelFormat( nchannels, sizeof( kvs::UInt8 ) );
    m_texture.setMinFilter( GL_NEAREST );
    m_texture.setMagFilter( GL_NEAREST );

    const size_t      width  = m_colormap.resolution();
    const size_t      height = 1;
    const kvs::UInt8* data   = m_colormap.table().pointer();
    m_texture.create( width, height );
    m_texture.download( width, height, data );
}

void LegendBar::release_texture( void )
{
    m_texture.release();
}

/*==========================================================================*/
/**
 *  Draw the texture.
 */
/*==========================================================================*/
void LegendBar::draw_texture( void )
{
    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    glEnable( GL_TEXTURE_2D );

    const GLfloat x = static_cast<GLfloat>(m_x);
    const GLfloat y = static_cast<GLfloat>(m_y);
    const GLfloat width = static_cast<GLfloat>(m_width);
    const GLfloat height = static_cast<GLfloat>(m_height);

    switch ( m_orientation )
    {
    case LegendBar::Horizontal:
    {
        glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 0.0f ); glVertex2f( x,         y );
        glTexCoord2f( 1.0f, 0.0f ); glVertex2f( x + width, y );
        glTexCoord2f( 1.0f, 1.0f ); glVertex2f( x + width, y + height );
        glTexCoord2f( 0.0f, 1.0f ); glVertex2f( x,         y + height );
        glEnd();
        break;
    }
    case LegendBar::Vertical:
    {
        glBegin( GL_QUADS );
        glTexCoord2f( 0.0f, 1.0f ); glVertex2f( x,         y );
        glTexCoord2f( 0.0f, 0.0f ); glVertex2f( x + width, y );
        glTexCoord2f( 1.0f, 0.0f ); glVertex2f( x + width, y + height );
        glTexCoord2f( 1.0f, 1.0f ); glVertex2f( x,         y + height );
        glEnd();
        break;
    }
    default: break;
    }

    glPopAttrib();
}

/*==========================================================================*/
/**
 *  Draw the border.
 */
/*==========================================================================*/
void LegendBar::draw_border( void )
{
    const GLfloat x = static_cast<GLfloat>(m_x);
    const GLfloat y = static_cast<GLfloat>(m_y);
    const GLfloat width = static_cast<GLfloat>(m_width);
    const GLfloat height = static_cast<GLfloat>(m_height);

    if ( m_enable_anti_aliasing && m_border_width != 1.0f )
    {
        glEnable( GL_LINE_SMOOTH );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    glLineWidth( m_border_width );
    glBegin( GL_LINE_LOOP );
    glColor3ub( m_border_color.r(), m_border_color.g(), m_border_color.b() );
    glVertex2f( x,         y );
    glVertex2f( x + width, y );
    glVertex2f( x + width, y + height );
    glVertex2f( x,         y + height );
    glEnd();

    if ( m_enable_anti_aliasing && m_border_width != 1.0f )
    {
        glDisable( GL_LINE_SMOOTH );
        glDisable( GL_BLEND );
    }

    if ( m_ndivisions == 0 ) return;

    if ( m_enable_anti_aliasing && m_division_line_width != 1.0f )
    {
        glEnable( GL_LINE_SMOOTH );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    glLineWidth( m_division_line_width );
    glBegin( GL_LINES );
    glColor3ub( m_division_line_color.r(), m_division_line_color.g(), m_division_line_color.b() );
    switch ( m_orientation )
    {
    case LegendBar::Horizontal:
    {
        const float w = width / m_ndivisions;
        const float h = height;
        for( size_t i = 1; i < m_ndivisions; i++ )
        {
            glVertex2f( x + w * i, y );
            glVertex2f( x + w * i, y + h );
        }
        break;
    }
    case LegendBar::Vertical:
    {
        const float w = width;
        const float h = height / m_ndivisions;
        for( size_t i = 1; i < m_ndivisions; i++ )
        {
            glVertex2f( x,     y + h * i );
            glVertex2f( x + w, y + h * i );
        }
        break;
    }
    default: break;
    }
    glEnd();
}

/*==========================================================================*/
/**
 *  Draw the string.
 */
/*==========================================================================*/
void LegendBar::draw_string( void )
{
    glColor3ub( m_text_color.r(), m_text_color.g(), m_text_color.b() );
    switch ( m_orientation )
    {
    case LegendBar::Horizontal:
    {
        // Title.
        glRasterPos2i( m_x, m_y + m_height + 5 );
        for ( char* p = const_cast<char*>( m_title.c_str() ); *p; p++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
        }
        // Min value.
        kvs::String min_value( m_min_value );
        glRasterPos2i( m_x - 4 * min_value.size(), m_y - 13 );
        for ( size_t i = 0; i < min_value.size(); i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *( min_value.toStdString().c_str() + i ) );
        }
        // Max value.
        kvs::String max_value( m_max_value );
        glRasterPos2i( m_x + m_width - 4 * max_value.size(), m_y - 13 );
        for ( size_t i = 0; i < max_value.size(); i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *( max_value.toStdString().c_str() + i ) );
        }
        break;
    }
    case LegendBar::Vertical:
    {
        // Title.
        glRasterPos2i( m_x, m_y + m_height + 13 );
        for ( char* p = const_cast<char*>( m_title.c_str() ); *p; p++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *p );
        }
        // Min value.
        kvs::String min_value( m_min_value );
        glRasterPos2i( m_x + m_width + 5, m_y - 6 );
        for ( size_t i = 0; i < min_value.size(); i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *( min_value.toStdString().c_str() + i ) );
        }
        // Max value.
        kvs::String max_value( m_max_value );
        glRasterPos2i( m_x + m_width + 5, m_y + m_height - 6 );
        for ( size_t i = 0; i < max_value.size(); i++ )
        {
            glutBitmapCharacter( GLUT_BITMAP_8_BY_13, *( max_value.toStdString().c_str() + i ) );
        }
        break;
    }
    default: break;
    }
}

} // end of namespace glut

} // end of namespace kvs
