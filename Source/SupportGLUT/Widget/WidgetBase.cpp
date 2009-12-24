/*****************************************************************************/
/**
 *  @file   WidgetBase.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "WidgetBase.h"
#include <kvs/OpenGL>
#include <kvs/glut/GLUT>
#include <kvs/HSVColor>
#include <kvs/RGBColor>

// Default parameters.
namespace { namespace Default
{
void*                CharacterFont = GLUT_BITMAP_8_BY_13;
const int            CharacterWidth = 8;
const int            CharacterHeight = 12;
const kvs::RGBColor  TextColor = kvs::RGBColor( 0, 0, 0 );
const kvs::RGBAColor BackgroundColor = kvs::RGBAColor( 200, 200, 200, 0.0f );
const kvs::RGBAColor BackgroundBorderColor = kvs::RGBAColor( 0, 0, 0, 1.0f );
const float          BackgroundBorderWidth = 0.0f;
} }


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new WidgetBase class.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
WidgetBase::WidgetBase( kvs::glut::Screen* screen ):
    m_screen( screen ),
    m_x( 0 ),
    m_y( 0 ),
    m_width( 0 ),
    m_height( 0 ),
    m_margin( 0 ),
    m_is_active( false ),
    m_is_shown( false )
{
    if ( screen ) screen->eventHandler()->attach( this );

    // Set default parameters.
    this->setTextColor( ::Default::TextColor );
    this->setBackgroundColor( ::Default::BackgroundColor );
    this->setBackgroundBorderColor( ::Default::BackgroundBorderColor );
    this->setBackgroundBorderWidth( ::Default::BackgroundBorderWidth );
    m_character_width = ::Default::CharacterWidth;
    m_character_height = ::Default::CharacterHeight;
}

/*===========================================================================*/
/**
 *  @brief  Destructs the WidgetBase class.
 */
/*===========================================================================*/
WidgetBase::~WidgetBase( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the screen.
 *  @return pointer to the screen
 */
/*===========================================================================*/
kvs::glut::Screen* WidgetBase::screen( void )
{
    return( m_screen );
}

/*===========================================================================*/
/**
 *  @brief  Returns the x value of the widget position.
 *  @return x value of the widget position
 */
/*===========================================================================*/
const int WidgetBase::x( void ) const
{
    return( m_x );
}

/*===========================================================================*/
/**
 *  @brief  Returns the y value of the widget position.
 *  @return y value of the widget position
 */
/*===========================================================================*/
const int WidgetBase::y( void ) const
{
    return( m_y );
}

/*===========================================================================*/
/**
 *  @brief  Returns the widget width.
 *  @return widget width
 */
/*===========================================================================*/
const int WidgetBase::width( void ) const
{
    return( m_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the widget height.
 *  @return widget height
 */
/*===========================================================================*/
const int WidgetBase::height( void ) const
{
    return( m_height );
}

/*===========================================================================*/
/**
 *  @brief  Returns the margin.
 *  @return margin
 */
/*===========================================================================*/
const int WidgetBase::margin( void ) const
{
    return( m_margin );
}

/*===========================================================================*/
/**
 *  @brief  Returns the x value of the bottom-left of the widget.
 *  @return x value of the upper-left
 */
/*===========================================================================*/
const int WidgetBase::x0( void ) const
{
    return( m_x );
}

/*===========================================================================*/
/**
 *  @brief  Returns the y value of the bottom-left of the widget.
 *  @return y value of the upper-left
 */
/*===========================================================================*/
const int WidgetBase::y0( void ) const
{
    return( m_y );
}

/*===========================================================================*/
/**
 *  @brief  Returns the x value of the top-right of the widget.
 *  @return x value of the lower-right
 */
/*===========================================================================*/
const int WidgetBase::x1( void ) const
{
    return( m_x + m_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the y value of the top-right of the widget.
 *  @return y value of the lower-right
 */
/*===========================================================================*/
const int WidgetBase::y1( void ) const
{
    return( m_y + m_height );
}

/*===========================================================================*/
/**
 *  @brief  Returns the text color.
 *  @return text color
 */
/*===========================================================================*/
const kvs::RGBColor& WidgetBase::textColor( void ) const
{
    return( m_text_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the background color.
 *  @return background color
 */
/*===========================================================================*/
const kvs::RGBAColor& WidgetBase::backgroundColor( void ) const
{
    return( m_background_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the background border color.
 *  @return background border color
 */
/*===========================================================================*/
const kvs::RGBAColor& WidgetBase::backgroundBorderColor( void ) const
{
    return( m_background_border_color );
}

/*===========================================================================*/
/**
 *  @brief  Returns the background width.
 *  @return background width
 */
/*===========================================================================*/
const float WidgetBase::backgroundBorderWidth( void ) const
{
    return( m_background_border_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the character width.
 *  @return character width
 */
/*===========================================================================*/
const int WidgetBase::characterWidth( void ) const
{
    return( m_character_width );
}

/*===========================================================================*/
/**
 *  @brief  Returns the character height.
 *  @return character height
 */
/*===========================================================================*/
const int WidgetBase::characterHeight( void ) const
{
    return( m_character_height );
}

/*===========================================================================*/
/**
 *  @brief  Checks whether the widget is active or not.
 *  @return true, if the widget is active
 */
/*===========================================================================*/
const bool WidgetBase::isActive( void ) const
{
    return( m_is_active );
}

/*===========================================================================*/
/**
 *  @brief  Checks whether the widget is shown or not.
 *  @return true, if the widget is shown
 */
/*===========================================================================*/
const bool WidgetBase::isShown( void ) const
{
    return( m_is_shown );
}

/*===========================================================================*/
/**
 *  @brief  Sets x value of the widget position on the window coordinate.
 *  @param  x [in] x value of the widget position
 */
/*===========================================================================*/
void WidgetBase::setX( const int x )
{
    m_x = x;
}

/*===========================================================================*/
/**
 *  @brief  Sets y value of the widget position on the window coordinate.
 *  @param  y [in] y value of the widget position
 */
/*===========================================================================*/
void WidgetBase::setY( const int y )
{
    m_y = y;
}

/*===========================================================================*/
/**
 *  @brief  Sets a widget width.
 *  @param  width [in] widget width
 */
/*===========================================================================*/
void WidgetBase::setWidth( const int width )
{
    m_width = width;
}

/*===========================================================================*/
/**
 *  @brief  Sets a widget height.
 *  @param  height [in] widget height
 */
/*===========================================================================*/
void WidgetBase::setHeight( const int height )
{
    m_height = height;
}

/*===========================================================================*/
/**
 *  @brief  Sets a margin.
 *  @param  margin [in] margin
 */
/*===========================================================================*/
void WidgetBase::setMargin( const int margin )
{
    m_margin = margin;
}

/*===========================================================================*/
/**
 *  @brief  Sets a widget position.
 *  @param  x [in] x coordinate of the widget position
 *  @param  y [in] y coordinate of the widget position
 */
/*===========================================================================*/
void WidgetBase::setPosition( const int x, const int y )
{
    this->setX( x );
    this->setY( y );
}

/*===========================================================================*/
/**
 *  @brief  Sets a widget size.
 *  @param  width [in] widget width
 *  @param  height [in] widget height
 */
/*===========================================================================*/
void WidgetBase::setSize( const int width, const int height )
{
    this->setWidth( width );
    this->setHeight( height );
}

/*===========================================================================*/
/**
 *  @brief  Sets a widget geometry.
 *  @param  x [in] x coordinate of the widget position
 *  @param  y [in] y coordinate of the widget position
 *  @param  width [in] widget width
 *  @param  height [in] widget height
 */
/*===========================================================================*/
void WidgetBase::setGeometry( const int x, const int y, const int width, const int height )
{
    this->setPosition( x, y );
    this->setSize( width, height );
}

/*===========================================================================*/
/**
 *  @brief  Sets a text color.
 *  @param  color [in] text color
 */
/*===========================================================================*/
void WidgetBase::setTextColor( const kvs::RGBColor& color )
{
    m_text_color = color;
}

/*===========================================================================*/
/**
 *  @brief  Sets a background color.
 *  @param  background_color [in] background color
 */
/*===========================================================================*/
void WidgetBase::setBackgroundColor( const kvs::RGBAColor& background_color )
{
    m_background_color = background_color;
}

/*===========================================================================*/
/**
 *  @brief  Sets a background opacity value.
 *  @param  opacity [in] opacity value
 */
/*===========================================================================*/
void WidgetBase::setBackgroundOpacity( const float opacity )
{
    const kvs::UInt8 r = m_background_color.r();
    const kvs::UInt8 g = m_background_color.g();
    const kvs::UInt8 b = m_background_color.b();
    m_background_color = kvs::RGBAColor( r, g, b, opacity );
}

/*===========================================================================*/
/**
 *  @brief  Sets a background color.
 *  @param  background_border_color [in] background color
 */
/*===========================================================================*/
void WidgetBase::setBackgroundBorderColor( const kvs::RGBAColor& background_border_color )
{
    m_background_border_color = background_border_color;
}

/*===========================================================================*/
/**
 *  @brief  Sets a background border opacity value.
 *  @param  opacity [in] background opacity value
 */
/*===========================================================================*/
void WidgetBase::setBackgroundBorderOpacity( const float opacity )
{
    const kvs::UInt8 r = m_background_border_color.r();
    const kvs::UInt8 g = m_background_border_color.g();
    const kvs::UInt8 b = m_background_border_color.b();
    m_background_border_color = kvs::RGBAColor( r, g, b, opacity );
}

/*===========================================================================*/
/**
 *  @brief  Sets a background border width.
 *  @param  background_border_width [in] background border width
 */
/*===========================================================================*/
void WidgetBase::setBackgroundBorderWidth( const float background_border_width )
{
    m_background_border_width = background_border_width;
}

/*===========================================================================*/
/**
 *  @brief  Shows the screen.
 */
/*===========================================================================*/
void WidgetBase::show( void )
{
    if ( m_width == 0 ) m_width = this->get_fitted_width();
    if ( m_height == 0 ) m_height = this->get_fitted_height();

    m_is_shown = true;
}

/*===========================================================================*/
/**
 *  @brief  Hides the screen.
 */
/*===========================================================================*/
void WidgetBase::hide( void )
{
    m_is_shown = false;
}

/*===========================================================================*/
/**
 *  @brief  Activates the widget.
 */
/*===========================================================================*/
void WidgetBase::activate( void )
{
    m_is_active = true;
}

/*===========================================================================*/
/**
 *  @brief  Deactivates the widget.
 */
/*===========================================================================*/
void WidgetBase::deactivate( void )
{
    m_is_active = false;
}

/*===========================================================================*/
/**
 *  @brief  Check whether the given point is inside the widget or not.
 *  @param  x [in] x position in the window coordinate
 *  @param  y [in] y position in the window coordinate
 *  @param  proper [in] whether the edges are checked or not
 *  @return true if the given point is inside the width
 */
/*===========================================================================*/
const bool WidgetBase::contains(
    const int x,
    const int y,
    const bool proper )
{
    /*
     *   p0 ------------ *
     *    |              |  p  : ( x,  y  )
     *    |   p          |
     *    |              |  p0 : ( x0, y0 )
     *    |              |  p1 : ( x1, y1 )
     *    |              |
     *    * ------------ p1
     *
     */
    const int x0 = m_x;
    const int x1 = m_x + m_width;
    const int y0 = m_y;
    const int y1 = m_y + m_height;

    if ( proper )
    {
        return( ( x0 < x ) && ( x < x1 ) && ( y0 < y ) && ( y < y1 ) );
    }
    else
    {
        return( ( x0 <= x ) && ( x <= x1 ) && ( y0 <= y ) && ( y <= y1 ) );
    }
}

/*===========================================================================*/
/**
 *  @brief  Delimits the drawing.
 */
/*===========================================================================*/
void WidgetBase::begin_draw( void )
{
    GLint vp[4]; glGetIntegerv( GL_VIEWPORT, vp );
    const GLint left   = vp[0];
    const GLint bottom = vp[1];
    const GLint right  = vp[2];
    const GLint top    = vp[3];

    glPushAttrib( GL_ALL_ATTRIB_BITS );
    glMatrixMode( GL_MODELVIEW );  glPushMatrix(); glLoadIdentity();
    glMatrixMode( GL_PROJECTION ); glPushMatrix(); glLoadIdentity();
    glOrtho( left, right, top, bottom, -1, 1 ); // The origin is upper-left.
    glDisable( GL_DEPTH_TEST );
}

/*===========================================================================*/
/**
 *  @brief  Delimits the drawing.
 */
/*===========================================================================*/
void WidgetBase::end_draw( void )
{
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
    glPopAttrib();
}

/*==========================================================================*/
/**
 *  @brief  Draws the background.
 */
/*==========================================================================*/
void WidgetBase::draw_background( void )
{
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    {
        glDisable( GL_TEXTURE_1D );
        glDisable( GL_TEXTURE_2D );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        if ( m_background_color.a() > 0.0f )
        {
            // Draw background.
            glBegin( GL_POLYGON );
            {
                const GLubyte r = static_cast<GLubyte>( m_background_color.r() );
                const GLubyte g = static_cast<GLubyte>( m_background_color.g() );
                const GLubyte b = static_cast<GLubyte>( m_background_color.b() );
                const GLubyte a = static_cast<GLubyte>( m_background_color.a() * 255.0f );
                const GLfloat x0 = static_cast<GLfloat>( this->x0() );
                const GLfloat x1 = static_cast<GLfloat>( this->x1() );
                const GLfloat y0 = static_cast<GLfloat>( this->y0() );
                const GLfloat y1 = static_cast<GLfloat>( this->y1() );
                glColor4ub( r, g, b, a );
                glVertex2f( x0, y1 );
                glVertex2f( x0, y0 );
                glVertex2f( x1, y0 );
                glVertex2f( x1, y1 );
            }
            glEnd();
        }

        if ( m_background_border_width > 0.0f && m_background_border_color.a() > 0.0f )
        {
            // Draw outline of the background.
            glLineWidth( m_background_border_width );
            glBegin( GL_LINE_LOOP );
            {
                const GLubyte r = static_cast<GLubyte>( m_background_border_color.r() );
                const GLubyte g = static_cast<GLubyte>( m_background_border_color.g() );
                const GLubyte b = static_cast<GLubyte>( m_background_border_color.b() );
                const GLubyte a = static_cast<GLubyte>( m_background_border_color.a() * 255.0f );
                const GLfloat x0 = static_cast<GLfloat>( this->x0() );
                const GLfloat x1 = static_cast<GLfloat>( this->x1() );
                const GLfloat y0 = static_cast<GLfloat>( this->y0() );
                const GLfloat y1 = static_cast<GLfloat>( this->y1() );
                glColor4ub( r, g, b, a );
                glVertex2f( x0, y1 );
                glVertex2f( x0, y0 );
                glVertex2f( x1, y0 );
                glVertex2f( x1, y1 );
            }
            glEnd();
        }
    }
    glPopAttrib();
}

/*===========================================================================*/
/**
 *  @brief  Draws the text.
 *  @param  x [in] text position x
 *  @param  y [in] text position y
 *  @param  text [in] text
 */
/*===========================================================================*/
void WidgetBase::draw_text( const int x, const int y, const std::string& text )
{
    glColor3ub( m_text_color.r(), m_text_color.g(), m_text_color.b() );
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    {
        glDisable( GL_TEXTURE_1D );
        glDisable( GL_TEXTURE_2D );
        glDisable( GL_BLEND );

        glRasterPos2i( x, y );
        char* line_head = const_cast<char*>( text.c_str() );
        for( char* p = line_head; *p; p++ )
        {
            glutBitmapCharacter( ::Default::CharacterFont, *p );
        }
    }
    glPopAttrib();
}

/*===========================================================================*/
/**
 *  @brief  Swaps the colors.
 *  @param  color1 [in] color 1
 *  @param  color2 [in] color 2
 */
/*===========================================================================*/
void WidgetBase::swap_color( kvs::RGBColor& color1, kvs::RGBColor& color2 )
{
    const kvs::RGBColor temp = color1;
    color1 = color2;
    color2 = temp;
}

/*===========================================================================*/
/**
 *  @brief  Retruns the darkened color.
 *  @param  color [in] source color
 *  @param  darkness [in] coefficient value [0,1]
 *  @return darkened color
 */
/*===========================================================================*/
kvs::RGBColor WidgetBase::get_darkened_color( const kvs::RGBColor& color, const float darkness )
{
    kvs::HSVColor hsv( color );
    hsv.set( hsv.h(), hsv.s(), hsv.v() * darkness );

    return( kvs::RGBColor( hsv ) );
}

/*===========================================================================*/
/**
 *  @brief  Returns the fitted width.
 *  @return fitted width
 */
/*===========================================================================*/
int WidgetBase::get_fitted_width( void )
{
    return( 0 );
}

/*===========================================================================*/
/**
 *  @brief  Returns the fitted height.
 *  @return fitted height
 */
/*===========================================================================*/
int WidgetBase::get_fitted_height( void )
{
    return( 0 );
}

} // end of namespace glut

} // end of namespace kvs
