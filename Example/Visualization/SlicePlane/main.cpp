/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::SlicePlane class.
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
#include <kvs/CommandLine>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/PolygonObject>
#include <kvs/PolygonRenderer>
#include <kvs/SlicePlane>
// GLUT
#include <kvs/glut/ScreenBase>
#include <kvs/glut/GlobalBase>


/*===========================================================================*/
/**
 *  @brief  User-defined argument class.
 */
/*===========================================================================*/
class Argument : public kvs::CommandLine
{
public:

    Argument( int argc, char** argv ):
        kvs::CommandLine( argc, argv )
    {
        // Add help option (generate help message automatically).
        add_help_option();

        // Add input value.
        add_value( "input file.", true ); // required
    }
};

/*===========================================================================*/
/**
 *  @brief  User-defined global parameter class.
 */
/*===========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    static std::string filename; ///< input filename

    Global( int count, char** values ):
        kvs::glut::GlobalBase( count, values )
    {
        Argument arg( count, values );
        if ( !arg.parse() ) exit( EXIT_FAILURE );

        filename = arg.value<std::string>();
    }
};

// Instantiation.
std::string Global::filename;


/*===========================================================================*/
/**
 *  @brief  User-defined screen class.
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
        kvs::StructuredVolumeObject* volume = new kvs::StructuredVolumeImporter( Global::filename );
        if ( !volume )
        {
            kvsMessageError( "Cannot create a structured volume object." );
            return;
        }

        /* Extract planes by using SlicePlane class.
         *    c: center of gravity of the volume object.
         *    p: point located on the plane.
         *    n: normal vector of the plane.
         *    t: transfer function.
         */
        const kvs::Vector3f c( ( volume->maxObjectCoord() + volume->minObjectCoord() ) * 0.5f );
        const kvs::Vector3f p( c );
        const kvs::Vector3f n( 1.5, 0.8, 2.0 );
        const kvs::TransferFunction t( 256 );
        kvs::PolygonObject* object = new kvs::SlicePlane( volume, p, n, t );
        if ( !object )
        {
            kvsMessageError( "Cannot create a polygon object by Slice plane." );
            delete volume;
            return;
        }

        delete volume;

        kvs::PolygonRenderer* renderer = new kvs::PolygonRenderer();
        if ( !renderer )
        {
            kvsMessageError( "Cannot create a polygon renderer" );
            delete object;
            return;
        }

        const int object_id = Global::object_manager->insert( object );
        const int renderer_id = Global::renderer_manager->insert( renderer );
        Global::id_manager->insert( object_id, renderer_id );
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
    screen->setGeometry( 0, 0, 512, 512 );
    screen->setTitle( "kvs::SlicePlane" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
