/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program of kvs::opencv::VideoRenderer.
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include <kvs/opencv/VideoObject>
#include <kvs/opencv/VideoRenderer>
#include <kvs/glut/GlobalBase>
#include <kvs/glut/ScreenBase>


/*===========================================================================*/
/**
 *  @brief  Global class.
 */
/*===========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    static size_t width; ///< video width
    static size_t height; ///< vide height

    Global( int count, char** values ):
        kvs::glut::GlobalBase( count, values )
    {
        kvs::opencv::CaptureDevice device;
        if ( !device.create( CV_CAP_ANY ) )
        {
            kvsMessageError("Cannot initialize the capture device.");
            exit( EXIT_FAILURE );
        }

        const IplImage* frame = device.queryFrame();
        if ( !frame )
        {
            kvsMessageError("Cannot query a new frame from the capture device.");
            exit( EXIT_FAILURE );
        }

        width = static_cast<size_t>( frame->width );
        height = static_cast<size_t>( frame->height );
    }
};

size_t Global::width;
size_t Global::height;

/*===========================================================================*/
/**
 *  @brief  Screen class.
 */
/*===========================================================================*/
class Screen : public kvs::glut::ScreenBase
{
public:

    Screen( void )
    {
        addInitializeFunc( initialize_func );
    }

    static void initialize_func( void )
    {
        kvs::opencv::VideoObject* object = new kvs::opencv::VideoObject( CV_CAP_ANY );
        if ( !object )
        {
            kvsMessageError("Cannot create a video object.");
            exit( EXIT_FAILURE );
        }

        kvs::opencv::VideoRenderer* renderer = new kvs::opencv::VideoRenderer();
        if ( !renderer )
        {
            kvsMessageError("Cannot create a video object.");
            delete object;
            exit( EXIT_FAILURE );
        }

        const int object_id = Global::object_manager->insert( object );
        const int renderer_id = Global::renderer_manager->insert( renderer );
        Global::id_manager->insert( object_id, renderer_id );
    }
};

/*===========================================================================*/
/**
 *  @brief  Main function.
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    // Create the global parameters.
    Global* global = new Global( argc, argv );
    if( !global )
    {
        kvsMessageError("Cannot allocate memory for 'global'.");
        return( 0 );
    }

    // Create and show the rendering screen.
    Screen* screen = new Screen();
    if( !screen )
    {
        kvsMessageError("Cannot allocate memory for 'screen'.");
        return( 0 );
    }
    screen->setGeometry( 0, 0, Global::width, Global::height );
    screen->setTitle( "kvs::opencv::VideoRenderer" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
