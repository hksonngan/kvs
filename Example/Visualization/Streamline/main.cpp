/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Streamline class.
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
#include <kvs/LineObject>
#include <kvs/LineRenderer>
#include <kvs/Streamline>
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
        add_value( "input file (AVS Field data).", true ); // required
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

    static std::string filename;

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
            kvsMessageError( "Cannot creat a structured volume object.");
        }

        std::vector<kvs::Real32> v;
        kvs::Vector3i min_coord( 15, 15,  0 );
        kvs::Vector3i max_coord( 20, 20, 30 );
        for ( int k = min_coord.z(); k < max_coord.z(); k++ )
        {
            for ( int j = min_coord.y(); j < max_coord.y(); j++ )
            {
                for ( int i = min_coord.x(); i < max_coord.x(); i++ )
                {
                    v.push_back( static_cast<kvs::Real32>(i) );
                    v.push_back( static_cast<kvs::Real32>(j) );
                    v.push_back( static_cast<kvs::Real32>(k) );
                }
            }
        }
        kvs::PointObject* point = new kvs::PointObject( kvs::ValueArray<kvs::Real32>( v ) );
        if ( !point )
        {
            kvsMessageError( "Cannot creat a structured volume object.");
        }

        const kvs::TransferFunction transfer_function( 256 );
        kvs::LineObject* object = new kvs::Streamline( volume, point, transfer_function );
        if ( !object )
        {
            kvsMessageError( "Cannot creat a streamline object.");
        }

        delete point;
        delete volume;

        kvs::LineRenderer* renderer = new kvs::LineRenderer();
        if ( !renderer )
        {
            kvsMessageError( "Cannot creat a line renderer.");
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
    screen->setTitle( "kvs::Streamline" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
