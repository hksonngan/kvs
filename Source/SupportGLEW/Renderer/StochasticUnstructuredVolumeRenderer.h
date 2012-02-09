/*****************************************************************************/
/**
 *  @file   StochasticUnstructuredVolumeRenderer.h
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
#ifndef KVS__GLEW__STOCHASTIC_UNSTRUCTURED_VOLUME_RENDERER_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_UNSTRUCTURED_VOLUME_RENDERER_H_INCLUDE

#include "StochasticRendererBase.h"
#include "StochasticUnstructuredVolumeEngine.h"
#include <kvs/UnstructuredVolumeObject>


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Stochastic renderer class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticUnstructuredVolumeRenderer : public kvs::glew::StochasticRendererBase
{
    // Class name.
    kvsClassName( kvs::glew::StochasticUnstructuredVolumeRenderer );

    // Module information.
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::glew::StochasticRendererBase );

public:

    StochasticUnstructuredVolumeRenderer( void );

    StochasticUnstructuredVolumeRenderer( kvs::UnstructuredVolumeObject* object );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

public:

    void attachObject( const kvs::UnstructuredVolumeObject* object );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_UNSTRUCTURED_VOLUME_RENDERER_H_INCLUDE
