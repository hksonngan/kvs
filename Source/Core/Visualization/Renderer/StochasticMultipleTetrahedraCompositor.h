/*****************************************************************************/
/**
 *  @file   StochasticMultipleTetrahedraCompositor.h
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
#ifndef KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_COMPOSITOR_H_INCLUDE
#define KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_COMPOSITOR_H_INCLUDE

#include "StochasticMultipleTetrahedraRenderer.h"
#include "StochasticMultipleTetrahedraEngine.h"


namespace kvs
{

class Scene;
class ObjectManager;
class RendererManager;
class IDManager;
class PointObject;

class StochasticMultipleTetrahedraCompositor
{
    kvsClassName( kvs::StochasticMultipleTetrahedraCompositor );

private:

    kvs::ObjectManager* m_object_manager; ///< pointer to the object manager (reference)
    kvs::RendererManager* m_renderer_manager; ///< pointer to the renderer manager (reference)
    kvs::IDManager* m_id_manager; ///< pointer to the ID manager (reference)
    int m_object_id; ///< object ID registered in the screen
    kvs::PointObject* m_object; ///< pointer to a dummy object
    kvs::StochasticMultipleTetrahedraRenderer* m_renderer; ///< pointer to a stochastic renderer
    std::vector<kvs::ObjectBase*> m_registered_objects; ///< list of pointer to the registered object

public:

    StochasticMultipleTetrahedraCompositor(
        kvs::ObjectManager* object_manager,
        kvs::RendererManager* renderer_manager,
        kvs::IDManager* id_manager );
    StochasticMultipleTetrahedraCompositor( kvs::Scene* scene );
    virtual ~StochasticMultipleTetrahedraCompositor();

    void registerObjects(
        kvs::UnstructuredVolumeObject* object1,
        kvs::UnstructuredVolumeObject* object2,
        kvs::StochasticMultipleTetrahedraEngine* engine = NULL );
    void clearEnsembleBuffer();
    void setRepetitionLevel( const size_t repetition_level );
    void enableLODControl( const size_t coarse_level = 1 );
    void disableLODControl();
    void enableExactDepthTesting();
    void disableExactDepthTesting();
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_MULTIPLE_TETRAHEDRA_COMPOSITOR_H_INCLUDE
