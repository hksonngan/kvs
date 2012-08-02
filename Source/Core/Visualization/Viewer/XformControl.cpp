/****************************************************************************/
/**
 *  @file XformControl.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#include "XformControl.h"
#include <kvs/OpenGL>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param collision [in] conllision flag
 */
/*==========================================================================*/
XformControl::XformControl() :
    kvs::Xform()
{
    m_initial_xform.initialize();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
XformControl::~XformControl( void )
{
}

/*==========================================================================*/
/**
 *  Save xform.
 */
/*==========================================================================*/
void XformControl::saveXform( void )
{
    m_initial_xform.set( *this );
}

/*==========================================================================*/
/**
 *  Reset xform.
 */
/*==========================================================================*/
void XformControl::resetXform( void )
{
    kvs::Xform::set( m_initial_xform );
}

/*==========================================================================*/
/**
 *  Set xform.
 *  @param xform [in] xform matrix.
 */
/*==========================================================================*/
void XformControl::setXform( const kvs::Xform& xform )
{
    kvs::Xform::set( xform );
}

/*==========================================================================*/
/**
 *  Apply xform matrix.
 */
/*==========================================================================*/
void XformControl::applyXform( void ) const
{
    float xform[16];
    kvs::Xform::get( &xform );
    glMultMatrixf( xform );
}

/*==========================================================================*/
/**
 *  Get xform.
 *  @return xform matrix
 */
/*==========================================================================*/
const kvs::Xform XformControl::xform( void ) const
{
    return( kvs::Xform::get() );
}

/*==========================================================================*/
/**
 *  Rotate.
 *  @param rotation [in] current rotation matrix.
 */
/*==========================================================================*/
void XformControl::rotate( const kvs::Matrix33f& rotation )
{
    kvs::Vector3f position = this->xform().translation();

    this->translate( -position );
    kvs::Xform::updateRotation( rotation );
    this->translate( position );
}

/*==========================================================================*/
/**
 *  Translate.
 *  @param translation [in] current translation vector.
 */
/*==========================================================================*/
void XformControl::translate( const kvs::Vector3f& translation )
{
    kvs::Xform::updateTranslation( translation );
}

/*==========================================================================*/
/**
 *  Scaling.
 *  @param scale [in] current scaling value.
 */
/*==========================================================================*/
void XformControl::scale( const kvs::Vector3f& scaling )
{
    kvs::Vector3f position = this->xform().translation();

    this->translate( -position );
    kvs::Xform::updateScaling( scaling );
    this->translate( position );
}

} // end of namespace kvs
