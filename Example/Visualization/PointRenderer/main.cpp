/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::PointRenderer class.
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
#include <kvs/PointImporter>
#include <kvs/PointObject>
#include <kvs/PointRenderer>
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
        kvs::PointObject* object = new kvs::PointImporter( Global::filename );
        if ( !object )
        {
            kvsMessageError( "Cannot creat a point object.");
        }

        kvs::PointRenderer* renderer = new kvs::PointRenderer();
        if ( !renderer )
        {
            kvsMessageError( "Cannot creat a point renderer.");
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
    screen->setTitle( "kvs::PointRenderer" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
