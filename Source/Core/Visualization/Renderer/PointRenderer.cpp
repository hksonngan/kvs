/****************************************************************************/
/**
 *  @file PointRenderer.cpp
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
#include "PointRenderer.h"
#include "PointRenderingFunction.h"
#include <kvs/OpenGL>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/ObjectBase>
#include <kvs/PointObject>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
PointRenderer::PointRenderer( void )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
PointRenderer::~PointRenderer( void )
{
}

/*==========================================================================*/
/**
 *  Point rendering method.
 *  @param object [in] pointer to the object
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void PointRenderer::exec( ObjectBase* object, Camera* camera, Light* light )
{
    kvs::IgnoreUnusedVariable( light );
    kvs::IgnoreUnusedVariable( camera );

    kvs::PointObject* point = reinterpret_cast<kvs::PointObject*>( object );

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

    if ( point->normals().size() == 0 ) { BaseClass::disableShading(); }

    RendererBase::initialize();

    glEnable( GL_DEPTH_TEST );
    {
        this->timer().start();
        ::PointRenderingFunction( point );
        this->timer().stop();
    }
    glDisable( GL_DEPTH_TEST );

    glPopAttrib();
}

/*==========================================================================*/
/**
 *  Initialize about the projection matrix.
 */
/*==========================================================================*/
void PointRenderer::initialize_projection( void )
{
   glMatrixMode( GL_PROJECTION );

   glMatrixMode( GL_MODELVIEW );
}

/*==========================================================================*/
/**
 *  Initialize about the modelview matrix.
 */
/*==========================================================================*/
void PointRenderer::initialize_modelview( void )
{
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable( GL_COLOR_MATERIAL );

    glDisable( GL_NORMALIZE );

    if( !this->isShading() ) glDisable( GL_LIGHTING );
    else                     glEnable( GL_LIGHTING );
}

} // end of namespace kvs
