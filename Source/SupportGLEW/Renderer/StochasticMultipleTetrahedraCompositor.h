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
#ifndef KVS__GLEW__STOCHASTIC_MULTIPLE_TETRAHEDRA_COMPOSITOR_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_MULTIPLE_TETRAHEDRA_COMPOSITOR_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/ScreenBase>
#include <kvs/PointObject>
#include "StochasticMultipleTetrahedraRenderer.h"
#include "StochasticMultipleTetrahedraEngine.h"


namespace kvs
{

namespace glew
{

class StochasticMultipleTetrahedraCompositor
{
    kvsClassName( kvs::StochasticMultipleTetrahedraCompositor );

private:

    kvs::ScreenBase* m_screen; ///< pointer to the screen (reference)
    int m_object_id; ///< object ID registered in the screen
    kvs::PointObject* m_object; ///< pointer to a dummy object
    kvs::glew::StochasticMultipleTetrahedraRenderer* m_renderer; ///< pointer to a stochastic renderer
    std::vector<kvs::ObjectBase*> m_registered_objects; ///< list of pointer to the registered object

public:

    StochasticMultipleTetrahedraCompositor( kvs::ScreenBase* screen );

    virtual ~StochasticMultipleTetrahedraCompositor( void );

public:

    void registerObjects(
        kvs::UnstructuredVolumeObject* object1,
        kvs::UnstructuredVolumeObject* object2,
        kvs::glew::StochasticMultipleTetrahedraEngine* engine = NULL );

    void clearEnsembleBuffer( void );

    void setRepetitionLevel( const size_t repetition_level );

    void enableLODControl( const size_t coarse_level = 1 );

    void disableLODControl( void );

    void enableExactDepthTesting( void );

    void disableExactDepthTesting( void );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_MULTIPLE_TETRAHEDRA_COMPOSITOR_H_INCLUDE
