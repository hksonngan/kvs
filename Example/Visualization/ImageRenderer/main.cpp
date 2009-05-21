/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::ImageRenderer.
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
#include <kvs/ImageObject>
#include <kvs/ImageImporter>
#include <kvs/ImageRenderer>
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

    static std::string filename; ///< input filename
    static size_t width; ///< image width
    static size_t height; ///< image height

    Global( int count, char** values ):
        kvs::glut::GlobalBase( count, values )
    {
        Argument arg( count, values );
        if ( !arg.parse() ) exit( EXIT_FAILURE );

        // Get the specified image filename.
        filename = arg.value<std::string>();
    }
};

// Instantiation.
std::string Global::filename;
size_t Global::width;
size_t Global::height;

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
        kvs::ImageObject* object = new kvs::ImageImporter( Global::filename );
        if ( !object )
        {
            kvsMessageError("Cannot creat a image object.");
            return;
        }

        Global::width = object->width();
        Global::height = object->height();

        kvs::ImageRenderer* renderer = new kvs::ImageRenderer( kvs::ImageRenderer::Stretching );
        if ( !renderer )
        {
            kvsMessageError("Cannot create a image renderer.");
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
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 *  @return true, if the main process is done succesfully
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
    screen->setGeometry( 0, 0, Global::width, Global::height );
    screen->setTitle( "kvs::ImageRenderer" );
    screen->show();

    // Delete the global parameters and the rendering screen.
    delete global;
    delete screen;

    return( true );
}
