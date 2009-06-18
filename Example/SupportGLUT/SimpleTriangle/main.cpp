/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program to display a simple triangle using GLUT.
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
// SupportGLUT
#include <kvs/glut/ScreenBase>
#include <kvs/glut/GlobalBase>
#include <kvs/glut/Text>


/*===========================================================================*/
/**
 *  @brief  User-defined global parameter class.
 *
 *  Users have to define a 'global' class by inheriting the kvs::glut::GlobalBase
 *  class. Users can define some global parameters in this class according to
 *  their needs. If a user defines some global parameters, they will have to be
 *  inilialized in a constructor and cleared in a destructor.
 */
/*===========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    static kvs::glut::Text message; ///< text message

    Global( int count, char** values ) :
        kvs::glut::GlobalBase( count, values )
    {
        /* The arguments of this constructor are command line arguments. It is
         * necessary to assign some arguments to a constructor of the inherited
         * kvs::glut::GlobalBase class. In this initial configuration, no
         * arguments is passed to the constructor.
         */

        // Message of the mouse manipulation.
        message.addText( "Rotation:    [Left Button]" );
        message.addText( "Translation: [Right Button] or [Ctrl] + [Left Button]" );
        message.addText( "Scaling:     [Shift] + [Left Button]" );
        message.addText( "Quit:        [Esc] or [q]" );
    }
};

// Instantiation.
kvs::glut::Text Global::message;

/*===========================================================================*/
/**
 *  @brief  User-defined screen class.
 *
 *  Users have to define a 'screen' class by inheriting the kvs::glut::ScreenBase
 *  class. Users can register some event functions to the screen class by calling
 *  add-functions or set-functions which are defined in the kvs::glut::ScreenBase
 *  class. In this example, a simple paint-event function is registered to the
 *  screen class by caling the addPaintEvent function.
 */
/*===========================================================================*/
class Screen : public kvs::glut::ScreenBase
{
public:

    Screen( void )
    {
        /* In this constructor, an additional paint event function is registered
         * to the 'screen' class.
         */
        addPaintEvent( additional_paint_event );
    }

    static void additional_paint_event( void )
    {
        /* This sample method draws a rainbow colored triangle in the screen by
         * using GL_TRIANGLES.
         */
        glBegin( GL_TRIANGLES );
        glColor3ub( 255,   0,   0 ); glVertex3d(  0.0,  3.0, 0.0 );
        glColor3ub(   0, 255,   0 ); glVertex3d(  3.0, -3.0, 0.0 );
        glColor3ub(   0,   0, 255 ); glVertex3d( -3.0, -3.0, 0.0 );
        glEnd();

        /* The message of the mouse manipulation is drawn on the screen. The
         * position of the message is specified in the window coordinate system.
         * The origin of the window coordinate system is at the bottom left of
         * the screen.
         */
        const int x = 10;
        const int y = 50;
        Global::message.setPosition( x, y );
        Global::message.draw();
    }
};

/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 *
 *  Inside the main routine, users should create some global parameters as
 *  'Global' class and a screen as 'Screen' class. These can be done by
 *  declaring the 'Global' and 'Screen' class by inheriting the
 *  kvs::glut::GlobalBase and kvs::glut::ScreenBase class, respectively.
 *  In this routine, some properties can be set to the screen if necessary.
 *  Finally, this program is executed by calling the Screen::show() method.
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
    screen->setGeometry( 0, 0, 512, 512 );
    screen->setTitle( "SimpleTriangle" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
