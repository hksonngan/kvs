/*****************************************************************************/
/**
 *  @file   main.cpp
 *  @brief  Example program for kvs::Isosurface class.
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
#include <kvs/PolygonObject>
#include <kvs/Isosurface>
#include <kvs/HydrogenVolumeData>
#include <kvs/opencabin/Application>
#include <kvs/opencabin/Screen>

#include <kvs/PaintEventListener>
#include <kvs/RotationMatrix33>

class PaintEvent : public kvs::PaintEventListener
{
    void update( void )
    {
        /* Rotate object.
         */
        static const kvs::Matrix33f RX( kvs::XRotationMatrix33<float>( 5.0f ) );
        static const kvs::Matrix33f RY( kvs::YRotationMatrix33<float>( 5.0f ) );
        static const kvs::Matrix33f RZ( kvs::ZRotationMatrix33<float>( 5.0f ) );
        static const kvs::Matrix33f R = RX * RY * RZ;
        static const kvs::Vector3f O( 0.0f, 0.0f, 0.0f );
        screen()->objectManager()->object()->rotate( R, O );
        screen()->redraw();
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
    kvs::opencabin::Application app( argc, argv );
    kvs::opencabin::Application::EnableBarrier();

    /* Read volume data from the specified data file. If the data file is not
     * specified, scalar hydrogen volume data is created by using
     * kvs::HydrogenVolumeData class.
     */
    kvs::StructuredVolumeObject* volume = NULL;
    if ( argc > 1 ) volume = new kvs::StructuredVolumeImporter( std::string( argv[1] ) );
    else            volume = new kvs::HydrogenVolumeData( kvs::Vector3ui( 64, 64, 64 ) );

    if ( !volume )
    {
        kvsMessageError( "Cannot create a structured volume object." );
        return( false );
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
    const kvs::TransferFunction t = argc > 2 ? kvs::TransferFunction( argv[2] ) : kvs::TransferFunction( 256 );
    kvs::PolygonObject* object = new kvs::Isosurface( volume, i, n, d, t );
    if ( !object )
    {
        kvsMessageError( "Cannot create a polygon object." );
        delete volume;
        return( false );
    }

    delete volume;

    object->scale( kvs::Vector3f( 2.5f ), kvs::Vector3f( 0.0f ) );

    ::PaintEvent paint_event;

    // Screen.
    kvs::opencabin::Screen screen( &app );
    screen.addPaintEvent( &paint_event );
    screen.registerObject( object );
    //screen.setGeometry( 0, 0, 512, 512 );
    screen.setTitle( "kvs::Isosurface" );
    screen.show();

    return( app.run() );
}
