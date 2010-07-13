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
 *  $Id: main.cpp 502 2010-04-27 10:59:39Z naohisa.sakamoto $
 */
/*****************************************************************************/
#include <kvs/Message>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeImporter>
#include <kvs/PolygonObject>
#include <kvs/Isosurface>
#include <kvs/HydrogenVolumeData>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>

#include <kvs/PolygonRenderer>

#include <kvs/InitializeEventListener>
#include <kvs/PaintEventListener>
#include <kvs/IdleEventListener>
#include <kvs/RotationMatrix33>

#include "Application.h"
#include "Screen.h"
#include "Master.h"
#include "OpenCABIN.h"


class MInitEvent : public kvs::InitializeEventListener
{
    void update( void )
    {

    }
};

class MIdleEvent : public kvs::IdleEventListener
{
    void update( void )
    {

    }
};

class GInitEvent : public kvs::InitializeEventListener
{
    void update( void )
    {
        screen()->objectManager()->object()->scale( kvs::Vector3f( 2.0f ), kvs::Vector3f( 0.0f ) );
    }
};

class GDrawEvent : public kvs::PaintEventListener
{
    void update( void )
    {

    }
};

class GIdleEvent : public kvs::IdleEventListener
{
    void update( void )
    {
        screen()->objectManager()->object()->rotate( kvs::YRotationMatrix33<float>( 10.0f ), kvs::Vector3f( 0.0f ) );
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

/*
    MInitEvent minit;
    MIdleEvent midle;

    kvs::opencabin::Master master( &app );
    master.addInitializeEvent( &minit );
    master.addIdleEvent( &midle );
*/

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
    const kvs::TransferFunction t( 256 );
    kvs::PolygonObject* object = new kvs::Isosurface( volume, i, n, d, t );
    if ( !object )
    {
        kvsMessageError( "Cannot create a polygon object." );
        delete volume;
        return( false );
    }

    delete volume;

    GInitEvent ginit;
    GDrawEvent gdraw;
    GIdleEvent gidle;

    // Screen.
    kvs::opencabin::Screen screen( &app );
    screen.addInitializeEvent( &ginit );
    screen.addPaintEvent( &gdraw );
    screen.addIdleEvent( &gidle );
    screen.registerObject( object );
    screen.setGeometry( 0, 0, 600, 300 );
    screen.setTitle( "kvs::Isosurface" );
    screen.show();

    return( app.run() );
}
