/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program of SupportGLUT.
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
// SupportSAGE
#include <kvs/sage/SAGE>
#include <kvs/sage/ScreenBase>
#include <kvs/sage/GlobalBase>


/*===========================================================================*/
/**
 *  @brief  Global class.
 */
/*===========================================================================*/
class Global : public kvs::sage::GlobalBase
{
public:

    Global( int count, char** values ):
        kvs::sage::GlobalBase( count, values )
    {
    }
};

/*===========================================================================*/
/**
 *  @brief  Screen class.
 */
/*===========================================================================*/
class Screen : public kvs::sage::ScreenBase
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
    if ( !global )
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
