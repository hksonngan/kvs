/****************************************************************************/
/**
 *  @file Screen.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "Screen.h"


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
 *  Construct a new Screen class.
 *  @param width [in] screen width
 *  @param height [in] screen height
 */
/*==========================================================================*/
Screen::Screen( const size_t width, const size_t height ):
    kvs::glut::ScreenBase()
{
    kvs::glut::ScreenBase::setSize( width, height );
}

/*==========================================================================*/
/**
 *  Construct a new Screen class.
 *  @param x [in] x value of screen position
 *  @param y [in] y value of screen position
 *  @param width [in] screen width
 *  @param height [in] screen height
 */
/*==========================================================================*/
Screen::Screen( const size_t x, const size_t y, const size_t width, const size_t height ):
    kvs::glut::ScreenBase()
{
    kvs::glut::ScreenBase::setGeometry( x, y, width, height );
}

/*==========================================================================*/
/**
 *  Destruct.
 */
/*==========================================================================*/
Screen::~Screen( void )
{
}

} // end of namesapce glut

} // end of namespace kvs
