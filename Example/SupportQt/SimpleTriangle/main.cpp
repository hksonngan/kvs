/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program to display a simple triangle using Qt.
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
// KVS
#include <kvs/OpenGL>
#include <kvs/Message>
#include <kvs/RGBColor>
// SupportQt
#include <kvs/qt/ScreenBase>
#include <kvs/qt/GlobalBase>
// SupportGLUT
#include <kvs/glut/Text>


/*===========================================================================*/
/**
 *  @class  Global
 *  @brief  User-defined global parameter class.
 */
/*===========================================================================*/
class Global : public kvs::qt::GlobalBase
{
public:

    static kvs::glut::Text message; ///< text message

    Global( int count, char** values ) :
        kvs::qt::GlobalBase( count, values )
    {
        // Message of the mouse manipulation.
        message.addText( "Rotation:    [Left Button]" );
        message.addText( "Translation: [Right Button] or [Ctrl] + [Left Button]" );
        message.addText( "Scaling:     [Shift] + [Left Button] or [Wheel Scroll]" );
        message.addText( "Quit:        [Esc] or [q]" );
    }
};

// Instantiation.
kvs::glut::Text Global::message;

/*===========================================================================*/
/**
 *  @class  Screen
 *  @brief  User-defined screen class.
 */
/*===========================================================================*/
class Screen : public kvs::qt::ScreenBase
{
public:

    Screen( void )
    {
        addPaintEvent( additional_paint_event );
    }

    static void additional_paint_event( void )
    {
        glBegin( GL_TRIANGLES );
        glColor3ub( 255,   0,   0 ); glVertex3d(  0.0,  3.0, 0.0 );
        glColor3ub(   0, 255,   0 ); glVertex3d(  3.0, -3.0, 0.0 );
        glColor3ub(   0,   0, 255 ); glVertex3d( -3.0, -3.0, 0.0 );
        glEnd();

        const int x = 10;
        const int y = 50;
        Global::message.setPosition( x, y );
        Global::message.draw();
    }
};

/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument counter
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    // Create the global parameters.
    Global* global = new Global( argc, argv );
    if( !global )
    {
        kvsMessageError("Cannot allocate memory for 'global'.");
        return( false );
    }

    // Create and show the rendering screen.
    Screen* screen = new Screen();
    if( !screen )
    {
        kvsMessageError("Cannot allocate memory for 'screen'.");
        return( false );
    }
    screen->setGeometry( 50, 50, 512, 512 );
    screen->setTitle( "SimpleTriangle" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
