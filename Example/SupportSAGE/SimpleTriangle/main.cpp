/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program to display a simple triangle on TDW using SAGE.
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
#include <kvs/PaintEventListener>
// SupportGLUT
#include <kvs/sage/Application>
#include <kvs/sage/Screen>


/*===========================================================================*/
/**
 *  @brief  User-defined paint event.
 */
/*===========================================================================*/
class PaintEvent : public kvs::PaintEventListener
{
    void update( void )
    {
        /* This sample method draws a rainbow colored triangle in the screen by
         * using GL_TRIANGLES.
         */
        glBegin( GL_TRIANGLES );
        glColor3ub( 255,   0,   0 ); glVertex3d(  0.0,  3.0, 0.0 );
        glColor3ub(   0, 255,   0 ); glVertex3d(  3.0, -3.0, 0.0 );
        glColor3ub(   0,   0, 255 ); glVertex3d( -3.0, -3.0, 0.0 );
        glEnd();
    }
};

/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    // Application.
    kvs::sage::Application app( argc, argv );

    // User specified event.
    PaintEvent paint_event;

    // Screen.
    kvs::sage::Screen screen( &app );
    screen.addPaintEvent( &paint_event );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "SimpleTriangle" );
    screen.show();

    return( app.run() );
}
