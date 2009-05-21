/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Isosurface class.
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
#include <kvs/Message>
#include <kvs/CommandLine>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/PolygonObject>
#include <kvs/PolygonRenderer>
#include <kvs/Isosurface>
// SupportGLUT
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

    static std::string filename;   ///< input filename

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

        /* Extract surfaces by using the Isosurface class.
         *    i: isolevel
         *    n: NormalType (PolygonNormal/VertexNormal)
         *    d: check flag whether the duplicate vertices are deleted (false) or not
         *    t: transfer function
         */
        volume->updateMinMaxValues();
        const double i = ( volume->maxValue() + volume->minValue() ) * 0.5;
        const kvs::PolygonObject::NormalType n = kvs::PolygonObject::VertexNormal;
        const bool d = false;
        const kvs::TransferFunction t( 256 );
        kvs::PolygonObject* object = new kvs::Isosurface( volume, i, n, d, t );
        if ( !object )
        {
            kvsMessageError( "Cannot create a polygon object." );
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
    screen->setTitle( "kvs::Isosurface" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
