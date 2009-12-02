/*****************************************************************************/
/**
 *  @file   WidgetBase.h
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
#ifndef KVS__GLUT__WIDGET_BASE_H_INCLUDE
#define KVS__GLUT__WIDGET_BASE_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/RGBAColor>
#include <kvs/EventListener>
#include <kvs/glut/Screen>

namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  Base class of the widget.
 */
/*===========================================================================*/
class WidgetBase : public kvs::EventListener
{
    // Class name.
    kvsClassName( WidgetBase );

protected:

    kvs::glut::Screen* m_screen; ///< pointer to the screen;
    int                m_x; ///< x position of widget on the window coordinate (org: upper-left)
    int                m_y; ///< y position of widet on the window coordinate (org: upper-left)
    int                m_width; ///< widget width
    int                m_height; ///< widget height
    int                m_margin; ///< margin
    bool               m_is_active; ///< check flag for widget activation
    bool               m_is_shown; ///< check flag whether the widget is shown or not
    kvs::RGBColor      m_text_color; ///< text color
    kvs::RGBAColor     m_background_color; ///< background color
    kvs::RGBAColor     m_background_border_color; ///< background border color
    float              m_background_border_width; ///< background border width
    int                m_character_width; ///< character width
    int                m_character_height; ///< character height

public:

    WidgetBase( kvs::glut::Screen* screen );

    virtual ~WidgetBase( void );

protected:

    kvs::glut::Screen* screen( void );

public:

    const int x( void ) const;

    const int y( void ) const;

    const int width( void ) const;

    const int height( void ) const;

    const int margin( void ) const;

    const int x0( void ) const;

    const int y0( void ) const;

    const int x1( void ) const;

    const int y1( void ) const;

    const bool isActive( void ) const;

    const bool isShown( void ) const;

    const kvs::RGBColor& textColor( void ) const;

    const kvs::RGBAColor& backgroundColor( void ) const;

    const kvs::RGBAColor& backgroundBorderColor( void ) const;

    const float backgroundBorderWidth( void ) const;

    const int characterWidth( void ) const;

    const int characterHeight( void ) const;

public:

    void setX( const int x );

    void setY( const int y );

    void setWidth( const int width );

    void setHeight( const int height );

    void setMargin( const int margin );

    void setPosition( const int x, const int y );

    void setSize( const int width, const int height );

    void setGeometry( const int x, const int y, const int width, const int height );

    void setTextColor( const kvs::RGBColor& text_color );

    void setBackgroundColor( const kvs::RGBAColor& background_color );

    void setBackgroundOpacity( const float opacity );

    void setBackgroundBorderColor( const kvs::RGBAColor& border_color );

    void setBackgroundBorderOpacity( const float opacity );

    void setBackgroundBorderWidth( const float border_width );

public:

    void show( void );

    void hide( void );

    void activate( void );

    void deactivate( void );

    const bool contains( const int x, const int y, const bool proper = false );

protected:

    virtual void begin_draw( void );

    virtual void end_draw( void );

    virtual void draw_background( void );

    virtual void draw_text( const int x, const int y, const std::string& text );

    virtual void swap_color( kvs::RGBColor& color1, kvs::RGBColor& color2 );

    virtual kvs::RGBColor get_darkened_color( const kvs::RGBColor& color, const float darkness );

    virtual int get_fitted_width( void );

    virtual int get_fitted_height( void );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__WIDGET_BASE_H_INCLUDE
