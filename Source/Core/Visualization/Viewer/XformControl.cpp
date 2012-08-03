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
XformControl::XformControl()
{
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
    m_initial_xform = m_current_xform;
}

/*==========================================================================*/
/**
 *  Reset xform.
 */
/*==========================================================================*/
void XformControl::resetXform( void )
{
    m_current_xform = m_initial_xform;
}

/*==========================================================================*/
/**
 *  Set xform.
 *  @param xform [in] xform matrix.
 */
/*==========================================================================*/
void XformControl::setXform( const kvs::Xform& xform )
{
    m_current_xform = xform;
}

/*==========================================================================*/
/**
 *  Apply xform matrix.
 */
/*==========================================================================*/
void XformControl::applyXform( void ) const
{
    float xform[16];
    m_current_xform.get( &xform );
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
    return m_current_xform;
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
    m_current_xform.updateRotation( rotation );
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
    m_current_xform.updateTranslation( translation );
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
    m_current_xform.updateScaling( scaling );
    this->translate( position );
}

} // end of namespace kvs
