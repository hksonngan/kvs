/*****************************************************************************/
/**
 *  @file   StochasticRenderingCompositor.cpp
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
#include "StochasticRenderingCompositor.h"
#include "StochasticPointEngine.h"
#include "StochasticLineEngine.h"
#include "StochasticPolygonEngine.h"
#include "StochasticTetrahedraEngine.h"
#include <kvs/PointObject>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticRenderingCompositor class.
 *  @param  screen [in] pointer to the screen
 */
/*===========================================================================*/
StochasticRenderingCompositor::StochasticRenderingCompositor( kvs::ScreenBase* screen ):
    m_screen( screen ),
    m_object_id( 0 ),
    m_object( new kvs::PointObject() ),
    m_renderer( new kvs::glew::StochasticRendererBase() )
{
    const kvs::Vector3f t = screen->objectManager()->xform().translation();
    const kvs::Vector3f s = screen->objectManager()->xform().scaling();
    const kvs::Matrix33f r = screen->objectManager()->xform().rotation();
    const kvs::Vector3f obj_min = screen->objectManager()->minObjectCoord();
    const kvs::Vector3f obj_max = screen->objectManager()->maxObjectCoord();
    const kvs::Vector3f ext_min = screen->objectManager()->minExternalCoord();
    const kvs::Vector3f ext_max = screen->objectManager()->maxExternalCoord();
    m_object->xform_control().setInitialXform( t, s, r );
    m_object->setMinMaxObjectCoords( obj_min, obj_max );
    m_object->setMinMaxExternalCoords( ext_min, ext_max );

    std::pair<int,int> ids = m_screen->registerObject( m_object, m_renderer );
    m_object_id = ids.first;
}

/*===========================================================================*/
/**
 *  @brief  Destroys the StochasticRenderingCompositor class.
 */
/*===========================================================================*/
StochasticRenderingCompositor::~StochasticRenderingCompositor( void )
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
void StochasticRenderingCompositor::registerObject(
    kvs::ObjectBase* object,
    kvs::glew::StochasticRenderingEngine* engine )
{
    // Esitimate a suitable engine for the specified object if the engine is not specified.
    if ( !engine )
    {
        const kvs::ObjectBase::ObjectType object_type = object->objectType();
        if ( object_type == kvs::ObjectBase::Geometry )
        {
            kvs::GeometryObjectBase* geometry = kvs::GeometryObjectBase::DownCast( object );
            switch ( geometry->geometryType() )
            {
            case kvs::GeometryObjectBase::Point:
            {
                engine = new kvs::glew::StochasticPointEngine();
                engine->attachObject( object );
                break;
            }
            case kvs::GeometryObjectBase::Line:
            {
                engine = new kvs::glew::StochasticLineEngine();
                engine->attachObject( object );
                break;
            }
            case kvs::GeometryObjectBase::Polygon:
            {
                engine = new kvs::glew::StochasticPolygonEngine();
                engine->attachObject( object );
                break;
            }
            default:
            {
                kvsMessageError("Not supported object.");
                return;
            }
            }
        }
        else if ( object_type == kvs::ObjectBase::Volume )
        {
            kvs::VolumeObjectBase* volume = kvs::VolumeObjectBase::DownCast( object );
            switch ( volume->volumeType() )
            {
            case kvs::VolumeObjectBase::Structured:
            {
                kvsMessageError("Structured volume object is not supported.");
                return;
            }
            case kvs::VolumeObjectBase::Unstructured:
            {
                engine = new kvs::glew::StochasticTetrahedraEngine();
                engine->attachObject( object );
                break;
            }
            default:
            {
                kvsMessageError("Not supported object.");
                return;
            }
            }
        }
        else
        {
            kvsMessageError("Cannot register the specified object.");
            return;
        }
    }
    else
    {
        if ( !engine->object() ) engine->attachObject( object );
    }

    m_registered_objects.push_back( object );

    // Update boundary information of the object.
    const kvs::Vector3f o_min_coord = object->minObjectCoord();
    const kvs::Vector3f o_max_coord = object->maxObjectCoord();
    kvs::Vector3f n_min_coord = m_object->minObjectCoord();
    kvs::Vector3f n_max_coord = m_object->maxObjectCoord();
    if ( m_object->hasMinMaxObjectCoords() )
    {
        if ( o_min_coord.x() < n_min_coord.x() ) n_min_coord.x() = o_min_coord.x();
        if ( o_min_coord.y() < n_min_coord.y() ) n_min_coord.y() = o_min_coord.y();
        if ( o_min_coord.z() < n_min_coord.z() ) n_min_coord.z() = o_min_coord.z();

        if ( o_max_coord.x() > n_max_coord.x() ) n_max_coord.x() = o_max_coord.x();
        if ( o_max_coord.y() > n_max_coord.y() ) n_max_coord.y() = o_max_coord.y();
        if ( o_max_coord.z() > n_max_coord.z() ) n_max_coord.z() = o_max_coord.z();
    }
    else
    {
        n_min_coord = o_min_coord;
        n_max_coord = o_max_coord;
    }

    m_object->setMinMaxObjectCoords( n_min_coord, n_max_coord );
    m_object->setMinMaxExternalCoords( n_min_coord, n_max_coord );
    m_renderer->setRenderingEngine( engine );

    // Update xform information of the object manager.
    m_screen->objectManager()->change( m_object_id, m_object, false );
}

/*===========================================================================*/
/**
 *  @brief  Changes the registered object by the object name.
 *  @param  registered_object_name [in] registered object name
 *  @param  object [in] pointer to a new object
 *  @param  is_delete [in] the registered object is deleted if true
 */
/*===========================================================================*/
void StochasticRenderingCompositor::changeObject(
    std::string registered_object_name,
    kvs::ObjectBase* object,
    bool is_delete )
{
    // Swap the object and delete the registered object if the specified flag (is_delete) is true.
    std::vector<kvs::ObjectBase*>::iterator obj = m_registered_objects.begin();
    std::vector<kvs::ObjectBase*>::iterator last = m_registered_objects.end();
    while ( obj != last )
    {
        if ( (*obj)->name() == registered_object_name )
        {
            if ( is_delete ) delete *obj;
            *obj = object;
        }
        ++obj;
    }

    // Attach the object to the rendering engine in which the specified object is registered.
    kvs::glew::StochasticRenderingEngine* engine = m_renderer->find_engine( registered_object_name );
    if ( engine ) engine->attachObject( object );

    static_cast<kvs::glew::StochasticRendererBase*>( m_renderer )->clearEnsembleBuffer();
}

/*===========================================================================*/
/**
 *  @brief  Changes the registered object by the pointer to the object.
 *  @param  registered_object [in] pointer to the registered object
 *  @param  object [in] pointer to a new object
 *  @param  is_delete [in] the registered object is deleted if true
 */
/*===========================================================================*/
void StochasticRenderingCompositor::changeObject(
    kvs::ObjectBase* registered_object,
    kvs::ObjectBase* object,
    bool is_delete )
{
    // Swap the object and delete the registered object if the specified flag (is_delete) is true.
    std::vector<kvs::ObjectBase*>::iterator obj = m_registered_objects.begin();
    std::vector<kvs::ObjectBase*>::iterator last = m_registered_objects.end();
    while ( obj != last )
    {
        if ( *obj == registered_object )
        {
            if ( is_delete ) delete *obj;
            *obj = object;
        }
        ++obj;
    }

    // Attach the object to the rendering engine in which the specified object is registered.
    kvs::glew::StochasticRenderingEngine* engine = m_renderer->find_engine( registered_object );
    if ( engine ) engine->attachObject( object );

    static_cast<kvs::glew::StochasticRendererBase*>( m_renderer )->clearEnsembleBuffer();
}

bool StochasticRenderingCompositor::removeObject( std::string registered_object_name )
{
    // Find the object.
    kvs::ObjectBase* registered_object = NULL;
    std::vector<kvs::ObjectBase*>::iterator object = m_registered_objects.begin();
    std::vector<kvs::ObjectBase*>::iterator last = m_registered_objects.end();
    while ( object != last )
    {
        if ( (*object)->name() == registered_object_name )
        {
            registered_object = *object;
            break;
        }
        ++object;
    }

    if ( registered_object ) return this->removeObject( registered_object );

    return false;
}

bool StochasticRenderingCompositor::removeObject( kvs::ObjectBase* registered_object )
{
    std::vector<kvs::ObjectBase*>::iterator end = std::remove( m_registered_objects.begin(), m_registered_objects.end(), registered_object );
    m_registered_objects.erase( end, m_registered_objects.end() );
    if ( m_renderer->erase_engine( registered_object ) )
    {
        static_cast<kvs::glew::StochasticRendererBase*>( m_renderer )->clearEnsembleBuffer();
        return true;
    }

    return false;
}

bool StochasticRenderingCompositor::eraseObject( std::string registered_object_name )
{
    // Find the object.
    kvs::ObjectBase* registered_object = NULL;
    std::vector<kvs::ObjectBase*>::iterator object = m_registered_objects.begin();
    std::vector<kvs::ObjectBase*>::iterator last = m_registered_objects.end();
    while ( object != last )
    {
        if ( (*object)->name() == registered_object_name )
        {
            registered_object = *object;
            break;
        }
        ++object;
    }

    if ( registered_object ) return this->eraseObject( registered_object );

    return false;
}

bool StochasticRenderingCompositor::eraseObject( kvs::ObjectBase* registered_object )
{
    if ( this->removeObject( registered_object ) )
    {
        delete registered_object;
        return true;
    }

    return false;
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffers.
 */
/*===========================================================================*/
void StochasticRenderingCompositor::clearEnsembleBuffer( void )
{
    m_renderer->clearEnsembleBuffer();
}

void StochasticRenderingCompositor::updateEngine()
{
    m_renderer->update_engine();
}

/*===========================================================================*/
/**
 *  @brief  Sets a repetition level
 *  @param  repetition_level [in] repetition level
 */
/*===========================================================================*/
void StochasticRenderingCompositor::setRepetitionLevel( const size_t repetition_level )
{
    m_renderer->setRepetitionLevel( repetition_level );
}

/*===========================================================================*/
/**
 *  @brief  Enables level-of-detail control.
 *  @param  coarse_level [in] coarse rendering level
 */
/*===========================================================================*/
void StochasticRenderingCompositor::enableLODControl( const size_t coarse_level )
{
    m_renderer->enableLODControl( coarse_level );
}

/*===========================================================================*/
/**
 *  @brief  Disable level-of-detail control.
 */
/*===========================================================================*/
void StochasticRenderingCompositor::disableLODControl( void )
{
    m_renderer->disableLODControl();
}

/*===========================================================================*/
/**
 *  @brief  Enables exact depth testing.
 */
/*===========================================================================*/
void StochasticRenderingCompositor::enableExactDepthTesting( void )
{
    m_renderer->enable_exact_depth_testing();
}

/*===========================================================================*/
/**
 *  @brief  Disables exact depth testing.
 */
/*===========================================================================*/
void StochasticRenderingCompositor::disableExactDepthTesting( void )
{
    m_renderer->disable_exact_depth_testing();
}

} // end of namespace glew

} // end of namespace kvs
