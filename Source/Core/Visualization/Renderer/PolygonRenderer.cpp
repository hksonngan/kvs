/****************************************************************************/
/**
 *  @file PolygonRenderer.cpp
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
#include "PolygonRenderer.h"
#include "PolygonRenderingFunction.h"
#include <kvs/OpenGL>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/ObjectBase>
#include <kvs/PolygonObject>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
PolygonRenderer::PolygonRenderer( void ):
    m_two_side_lighting_flag( true )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
PolygonRenderer::~PolygonRenderer( void )
{
}

/*==========================================================================*/
/**
 *  Polygon rendering method.
 *  @param object [in] pointer to the object
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void PolygonRenderer::exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::IgnoreUnusedVariable( light );
    kvs::IgnoreUnusedVariable( camera );

    kvs::PolygonObject* polygon = reinterpret_cast<kvs::PolygonObject*>( object );

    glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );

/*
    if ( this->isShading() )
    {
        if ( polygon->normals().size() == 0 )
        {
            glEnable( GL_AUTO_NORMAL );
        }
    }
*/

    RendererBase::initialize();
    polygon->applyMaterial();

    glEnable( GL_DEPTH_TEST );
    {
        this->timer().start();
        ::PolygonRenderingFunction( polygon );
        this->timer().stop();
    }
    glDisable( GL_DEPTH_TEST );

    glPopAttrib();
}

const bool PolygonRenderer::isTwoSideLighting( void ) const
{
    return( m_two_side_lighting_flag );
}

void PolygonRenderer::enableTwoSideLighting( void ) const
{
    m_two_side_lighting_flag = true;
}

void PolygonRenderer::disableTwoSideLighting( void ) const
{
    m_two_side_lighting_flag = false;
}

/*==========================================================================*/
/**
 *  Initialize about the projection matrix.
 */
/*==========================================================================*/
void PolygonRenderer::initialize_projection( void )
{
   glMatrixMode( GL_PROJECTION );

   glMatrixMode( GL_MODELVIEW );
}

/*==========================================================================*/
/**
 *  Initialize about the modelview matrix.
 */
/*==========================================================================*/
void PolygonRenderer::initialize_modelview( void )
{
    glDisable( GL_LINE_SMOOTH );

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glShadeModel( GL_SMOOTH );

    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable( GL_COLOR_MATERIAL );

    if( !this->isShading() )
    {
        glDisable( GL_NORMALIZE );
        glDisable( GL_LIGHTING );
    }
    else
    {
        glEnable( GL_NORMALIZE );
        glEnable( GL_LIGHTING );
    }

    kvs::Light::setModelTwoSide( this->isTwoSideLighting() );
}

} // end of namespace kvs
