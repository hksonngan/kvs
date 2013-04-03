/*****************************************************************************/
/**
 *  @file   StochasticMultipleTetrahedraCompositor.cpp
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
#include "StochasticMultipleTetrahedraCompositor.h"
#include <kvs/ObjectManager>
#include <kvs/RendererManager>
#include <kvs/IDManager>
#include <kvs/PointObject>
#include <kvs/ObjectManager>


namespace kvs
{

StochasticMultipleTetrahedraCompositor::StochasticMultipleTetrahedraCompositor(
    kvs::ObjectManager* object_manager,
    kvs::RendererManager* renderer_manager,
    kvs::IDManager* id_manager ):
    m_object_manager( object_manager ),
    m_renderer_manager( renderer_manager ),
    m_id_manager( id_manager ),
    m_object_id( 0 ),
    m_object( new kvs::PointObject() ),
    m_renderer( new kvs::StochasticMultipleTetrahedraRenderer() )
{
    const kvs::Vector3f obj_min = m_object_manager->minObjectCoord();
    const kvs::Vector3f obj_max = m_object_manager->maxObjectCoord();
    const kvs::Vector3f ext_min = m_object_manager->minExternalCoord();
    const kvs::Vector3f ext_max = m_object_manager->maxExternalCoord();
    m_object->setXform( m_object_manager->xform() );
    m_object->saveXform();
    m_object->setMinMaxObjectCoords( obj_min, obj_max );
    m_object->setMinMaxExternalCoords( ext_min, ext_max );

    const size_t object_id   = m_object_manager->insert( m_object );
    const size_t renderer_id = m_renderer_manager->insert( m_renderer );
    m_id_manager->insert( object_id, renderer_id );
    m_object_id = object_id;
}

StochasticMultipleTetrahedraCompositor::~StochasticMultipleTetrahedraCompositor( void )
{
    std::vector<kvs::ObjectBase*>::iterator object = m_registered_objects.begin();
    std::vector<kvs::ObjectBase*>::iterator last = m_registered_objects.end();
    while ( object != last )
    {
        if ( *object ) delete *object;
        ++object;
    }

    m_registered_objects.clear();
}

/*===========================================================================*/
/**
 *  @brief  Registers an object and rendering engine.
 *  @param  object [in] pointer to an object
 *  @param  engine [in] pointer to a rendering engine
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraCompositor::registerObjects(
    kvs::UnstructuredVolumeObject* object1,
    kvs::UnstructuredVolumeObject* object2,
    kvs::StochasticMultipleTetrahedraEngine* engine )
{
    // Esitimate a suitable engine for the specified object if the engine is not specified.
    if ( !engine )
    {
        engine = new kvs::StochasticMultipleTetrahedraEngine();
        engine->attachObjects( object1, object2 );
    }
    else
    {
        if ( !engine->object() ) { engine->attachObjects( object1, object2 ); }
    }

    m_registered_objects.push_back( object1 );
    m_registered_objects.push_back( object2 );

    // Update boundary information of the object.
    const kvs::Vector3f o1_min_coord = object1->minObjectCoord();
    const kvs::Vector3f o1_max_coord = object1->maxObjectCoord();
    const kvs::Vector3f o2_min_coord = object2->minObjectCoord();
    const kvs::Vector3f o2_max_coord = object2->maxObjectCoord();
    kvs::Vector3f n_min_coord = m_object->minObjectCoord();
    kvs::Vector3f n_max_coord = m_object->maxObjectCoord();
    if ( o1_min_coord.x() < n_min_coord.x() ) n_min_coord.x() = o1_min_coord.x();
    if ( o1_min_coord.y() < n_min_coord.y() ) n_min_coord.y() = o1_min_coord.y();
    if ( o1_min_coord.z() < n_min_coord.z() ) n_min_coord.z() = o1_min_coord.z();
    if ( o2_min_coord.x() < n_min_coord.x() ) n_min_coord.x() = o2_min_coord.x();
    if ( o2_min_coord.y() < n_min_coord.y() ) n_min_coord.y() = o2_min_coord.y();
    if ( o2_min_coord.z() < n_min_coord.z() ) n_min_coord.z() = o2_min_coord.z();

    if ( o1_max_coord.x() > n_max_coord.x() ) n_max_coord.x() = o1_max_coord.x();
    if ( o1_max_coord.y() > n_max_coord.y() ) n_max_coord.y() = o1_max_coord.y();
    if ( o1_max_coord.z() > n_max_coord.z() ) n_max_coord.z() = o1_max_coord.z();
    if ( o2_max_coord.x() > n_max_coord.x() ) n_max_coord.x() = o2_max_coord.x();
    if ( o2_max_coord.y() > n_max_coord.y() ) n_max_coord.y() = o2_max_coord.y();
    if ( o2_max_coord.z() > n_max_coord.z() ) n_max_coord.z() = o2_max_coord.z();

    m_object->setMinMaxObjectCoords( n_min_coord, n_max_coord );
    m_object->setMinMaxExternalCoords( n_min_coord, n_max_coord );
    m_renderer->set_rendering_engine( engine );

    // Update xform information of the object manager.
    m_object_manager->change( m_object_id, m_object, false );
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffers.
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraCompositor::clearEnsembleBuffer( void )
{
    m_renderer->clearEnsembleBuffer();
}

/*===========================================================================*/
/**
 *  @brief  Sets a repetition level
 *  @param  repetition_level [in] repetition level
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraCompositor::setRepetitionLevel( const size_t repetition_level )
{
    m_renderer->setRepetitionLevel( repetition_level );
}

/*===========================================================================*/
/**
 *  @brief  Enables level-of-detail control.
 *  @param  coarse_level [in] coarse rendering level
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraCompositor::enableLODControl( const size_t coarse_level )
{
    m_renderer->enableLODControl( coarse_level );
}

/*===========================================================================*/
/**
 *  @brief  Disable level-of-detail control.
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraCompositor::disableLODControl( void )
{
    m_renderer->disableLODControl();
}

void StochasticMultipleTetrahedraCompositor::enableExactDepthTesting( void )
{
    m_renderer->enable_exact_depth_testing();
}

void StochasticMultipleTetrahedraCompositor::disableExactDepthTesting( void )
{
    m_renderer->disable_exact_depth_testing();
}

} // end of namespace kvs
