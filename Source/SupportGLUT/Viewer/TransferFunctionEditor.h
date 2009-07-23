/*****************************************************************************/
/**
 *  @file   TransferFunctionEditor.h
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
#ifndef KVS__TRANSFER_FUNCTION_EDITOR_H_INCLUDE
#define KVS__TRANSFER_FUNCTION_EDITOR_H_INCLUDE

#include <kvs/OpenGL>
#include <kvs/RGBColor>
#include <kvs/RGBAColor>
#include <kvs/Vector2>
#include <kvs/TransferFunction>
#include <kvs/Texture1D>
#include <kvs/Texture2D>
#include <kvs/glut/Text>
#include <string>


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  TransferFunctionEditor class.
 */
/*===========================================================================*/
class TransferFunctionEditor : public kvs::TransferFunction
{
    typedef kvs::TransferFunction BaseClass;

public:

    class Mouse;
    class Widget;

protected:

    int m_id; ///< window ID
    size_t m_x; ///< window x position
    size_t m_y; ///< window y position
    size_t m_width; ///< window width
    size_t m_height; ///< window height
    std::string m_title; ///< window title
    kvs::RGBColor m_background_color; ///< background color
    Mouse* m_mouse; ///< mouse for transfer function editor
    Widget* m_SV_palette; ///< SV (saturation and value) palette
    Widget* m_H_palette; ///< H (hue) palette
    Widget* m_selected_color_box; ///< seleceted RGB color box
    Widget* m_color_map_box; ///< color map box
    Widget* m_opacity_map_box; ///< opacity map box

    kvs::Texture1D m_color_map_texture; ///< color map texture
    kvs::Texture1D m_opacity_map_texture; ///< opacity map texture
    kvs::Texture2D m_checkerboard_texture; ///< checkerboard texture

    kvs::glut::Text m_SV_palette_label; ///< SV palette label
    kvs::glut::Text m_color_map_label; ///< color map label
    kvs::glut::Text m_selected_color_value; ///< selected color value
    kvs::glut::Text m_color_map_value; ///< color value on the color and opacity map

    int m_H_cursor; ///< H (hue) indicator
    int m_S_cursor; ///< S (saturation) indicator
    int m_V_cursor; ///< V (value) indicator
    int m_scalar_cursor; ///< scalar value (field value) indicator

protected:

    friend void initialize_function( void );
    friend void paint_event( void );
    friend void resize_event( int width, int height );
    friend void mouse_press_event( int button, int state, int x, int y );
    friend void mouse_move_event( int x, int y );

public:

    TransferFunctionEditor( void );

    virtual ~TransferFunctionEditor( void );

public:

    void create( const bool show = false );

    void setPosition( const size_t x, const size_t y );

    void setBackgroundColor( const kvs::RGBColor color );

    void hideWindow( void );

    void showWindow( void );

protected:

    void lay_out_widgets( void );

protected:

    void draw_SV_palette( void );

    void draw_H_palette( void );

    void draw_selected_color_box( void );

    void draw_color_map_box( void );

    void draw_opacity_map_box( void );

    void draw_H_cursor( void );

    void draw_S_cursor( void );

    void draw_V_cursor( void );

    void draw_scalar_cursor( void );

    void draw_selected_color_value( void );

    void draw_color_map_value( void );

protected:

    void press_SV_palette( void );

    void press_H_palette( void );

    void press_color_map_box( void );

    void press_opacity_map_box( void );

protected:

    void move_SV_palette( void );

    void move_H_palette( void );

    void move_color_map_box( void );

    void move_opacity_map_box( void );

protected:

    void initialize_color_map_texture( void );

    void initialize_opacity_map_texture( void );

    void initialize_checkerboard_texture( void );

protected:

    const kvs::RGBColor get_selected_color( void );
};

/*===========================================================================*/
/**
 *  @brief  Mouse class for transfer function editor.
 */
/*===========================================================================*/
class TransferFunctionEditor::Mouse
{
protected:

    kvs::Vector2i m_previous; ///< previous mouse position
    kvs::Vector2i m_current; ///< current mouse position

public:

    Mouse( void );

public:

    const kvs::Vector2i previous( void ) const;

    const kvs::Vector2i current( void ) const;

    void press( const int x, const int y );

    void move( const int x, const int y );

    void stop( void );
};

/*===========================================================================*/
/**
 *  @brief  Widget class for transfer function editor
 */
/*===========================================================================*/
class TransferFunctionEditor::Widget
{
protected:

    int m_x; ///< x position of widget
    int m_y; ///< y position of widet
    int m_width; ///< widget width
    int m_height; ///< widget height
    bool m_is_active; ///< check flag for widget activation

public:

    Widget( void );

    Widget( const int x, const int y, const int width, const int height, const bool active = false );

public:

    const int x( void ) const;

    const int y( void ) const;

    const int width( void ) const;

    const int height( void ) const;

    const int x0( void ) const;

    const int y0( void ) const;

    const int x1( void ) const;

    const int y1( void ) const;

    const bool isActive( void ) const;

public:

    void setX( const int x );

    void setY( const int y );

    void setWidth( const int width );

    void setHeight( const int height );

public:

    void activate( void );

    void deactivate( void );

    const bool contains( const int x, const int y, const bool proper = false );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__TRANSFER_FUNCTION_EDITOR_H_INCLUDE
