/*****************************************************************************/
/**
 *  @file   main.cpp
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
#include "main.h"
#include "Argument.h"
#include "Default.h"
#include "PointRenderer.h"
#include "LineRenderer.h"
#include "PolygonRenderer.h"
#include "Isosurface.h"
#include "SlicePlane.h"
#include "OrthoSlice.h"
#include <kvs/Message>


namespace kvsview
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new Main class.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
Main::Main( int argc, char** argv )
{
    m_argc = argc;
    m_argv = argv;
}

/*===========================================================================*/
/**
 *  @brief  Execute main process.
 */
/*===========================================================================*/
bool Main::exec( void )
{
    Argument arg( m_argc, m_argv );
    if( !arg.read() ) return( false );

    if ( arg.hasOption("help") )
    {
        const std::string c = arg.optionValue<std::string>("help");
        if ( c == "Default" ) return( Default::Argument( m_argc, m_argv ).parse() );
        if ( c == "PointRenderer" ) return( PointRenderer::Argument( m_argc, m_argv ).parse() );
        if ( c == "LineRenderer" ) return( LineRenderer::Argument( m_argc, m_argv ).parse() );
        if ( c == "PolygonRenderer" ) return( PolygonRenderer::Argument( m_argc, m_argv ).parse() );
        if ( c == "Isosurface" ) return( Isosurface::Argument( m_argc, m_argv ).parse() );
        if ( c == "SlicePlane" ) return( SlicePlane::Argument( m_argc, m_argv ).parse() );
        if ( c == "OrthoSlice" ) return( OrthoSlice::Argument( m_argc, m_argv ).parse() );

        kvsMessageError( "Unknown viewer '%s'.", c.c_str() );
        return( false );
    }

    if ( arg.hasOption("Defulat") ) return( Default::Main( m_argc, m_argv ).exec() );
    if ( arg.hasOption("PointRenderer") ) return( PointRenderer::Main( m_argc, m_argv ).exec() );
    if ( arg.hasOption("LineRenderer") ) return( LineRenderer::Main( m_argc, m_argv ).exec() );
    if ( arg.hasOption("PolygonRenderer") ) return( PolygonRenderer::Main( m_argc, m_argv ).exec() );
    if ( arg.hasOption("Isosurface") ) return( Isosurface::Main( m_argc, m_argv ).exec() );
    if ( arg.hasOption("SlicePlane") ) return( SlicePlane::Main( m_argc, m_argv ).exec() );
    if ( arg.hasOption("OrthoSlice") ) return( OrthoSlice::Main( m_argc, m_argv ).exec() );

    return( Default::Main( m_argc, m_argv ).exec() );
}

} // end of namespace kvsview


/*===========================================================================*/
/**
 *  @brief  Main function.
 *  @param  argc [i] argument count
 *  @param  argv [i] argument values
 */
/*===========================================================================*/
int main( int argc, char** argv )
{
    kvsview::Main m( argc, argv );
    return( m.exec() );
}
