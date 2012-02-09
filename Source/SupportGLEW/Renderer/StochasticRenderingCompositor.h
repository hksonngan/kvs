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
#ifndef KVS__GLEW__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE

#include <vector>
#include <kvs/ClassName>
#include <kvs/ScreenBase>
#include <kvs/PointObject>
#include "StochasticRendererBase.h"


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Compositor class for rendering multiple objects.
 */
/*===========================================================================*/
class StochasticRenderingCompositor
{
    kvsClassName( kvs::StochasticRenderingCompositor );

private:

    kvs::ScreenBase* m_screen; ///< pointer to the screen (reference)
    int m_object_id; ///< object ID registered in the screen
    kvs::PointObject* m_object; ///< pointer to a dummy object
    kvs::glew::StochasticRendererBase* m_renderer; ///< pointer to a stochastic renderer
    std::vector<kvs::ObjectBase*> m_registered_objects; ///< list of pointer to the registered object

public:

    StochasticRenderingCompositor( kvs::ScreenBase* screen );

    virtual ~StochasticRenderingCompositor( void );

public:

    void registerObject( kvs::ObjectBase* object, kvs::glew::StochasticRenderingEngine* engine = NULL );

    void changeObject(
        std::string registered_object_name,
        kvs::ObjectBase* object,
        bool is_delete = true );

    void changeObject(
        kvs::ObjectBase* registered_object,
        kvs::ObjectBase* object,
        bool is_delete = true );

    void clearEnsembleBuffer( void );

    void setRepetitionLevel( const size_t repetition_level );

    void enableLODControl( const size_t coarse_level = 1 );

    void disableLODControl( void );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_RENDERING_COMPOSITOR_H_INCLUDE
