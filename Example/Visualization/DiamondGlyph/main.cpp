/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Streamline class.
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
#include <kvs/Message>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/DiamondGlyph>
#include <kvs/GlyphRenderer>
#include <kvs/TornadoVolumeData>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>


/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument counter
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    kvs::glut::Application app( argc, argv );

    /* Read volume data from the specified data file. If the data file is not
     * specified, scalar hydrogen volume data is created by using
     * kvs::HydrogenVolumeData class.
     */
    kvs::StructuredVolumeObject* volume = NULL;
    if ( argc > 1 ) volume = new kvs::StructuredVolumeImporter( std::string( argv[1] ) );
    else            volume = new kvs::TornadoVolumeData( kvs::Vector3ui( 8, 8, 8 ) );

    if ( !volume )
    {
        kvsMessageError( "Cannot create a structured volume object." );
        return( false );
    }

    const kvs::TransferFunction transfer_function( 256 );
    kvs::DiamondGlyph* object = new kvs::DiamondGlyph( volume, transfer_function );
    if ( !object )
    {
        kvsMessageError( "Cannot creat a glyph object.");
        return( false );
    }

    delete volume;

    kvs::GlyphRenderer* renderer = new kvs::GlyphRenderer();

    kvs::glut::Screen screen( &app );
    screen.registerObject( object, renderer );
    screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::ArrowGlyph" );
    screen.show();

    return( app.run() );
}
