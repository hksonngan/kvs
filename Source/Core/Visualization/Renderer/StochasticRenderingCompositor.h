/*****************************************************************************/
/**
 *  @file   StochasticRenderingCompositor.h
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
#ifndef KVS__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE
#define KVS__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE

#include <string>
#include <vector>
#include <kvs/ClassName>
#include "StochasticRendererBase.h"


namespace kvs
{

class ObjectManager;
class RendererManager;
class IDManager;
class PointObject;
class ObjectBase;

class StochasticRenderingEngine;

/*===========================================================================*/
/**
 *  @brief  Compositor class for rendering multiple objects.
 */
/*===========================================================================*/
class StochasticRenderingCompositor
{
    kvsClassName( kvs::StochasticRenderingCompositor );

private:

    kvs::ObjectManager* m_object_manager; ///< pointer to the object manager (reference)
    kvs::RendererManager* m_renderer_manager; ///< pointer to the renderer manager (reference)
    kvs::IDManager* m_id_manager; ///< pointer to the ID manager (reference)
    int m_object_id; ///< object ID registered in the screen
    kvs::PointObject* m_object; ///< pointer to a dummy object
    kvs::StochasticRendererBase* m_renderer; ///< pointer to a stochastic renderer
    std::vector<kvs::ObjectBase*> m_registered_objects; ///< list of pointer to the registered object

public:

    StochasticRenderingCompositor(
        kvs::ObjectManager* object_manager,
        kvs::RendererManager* renderer_manager,
        kvs::IDManager* id_manager );

    virtual ~StochasticRenderingCompositor( void );

public:

    void registerObject( kvs::ObjectBase* object, kvs::StochasticRenderingEngine* engine = NULL );

    void changeObject(
        std::string registered_object_name,
        kvs::ObjectBase* object,
        bool is_delete = true );

    void changeObject(
        kvs::ObjectBase* registered_object,
        kvs::ObjectBase* object,
        bool is_delete = true );

    bool removeObject( std::string registered_object_name );

    bool removeObject( kvs::ObjectBase* registered_object );

    bool eraseObject( std::string registered_object_name );

    bool eraseObject( kvs::ObjectBase* registered_object );

    kvs::ObjectBase* object( const std::string& object_name );

    kvs::StochasticRenderingEngine* engine( const std::string& object_name );

    kvs::StochasticRenderingEngine* engine( const kvs::ObjectBase* object );

    void clearEnsembleBuffer( void );

    void updateEngine();

    void setRepetitionLevel( const size_t repetition_level );

    void enableLODControl( const size_t coarse_level = 1 );

    void disableLODControl( void );

    void enableExactDepthTesting( void );

    void disableExactDepthTesting( void );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE
