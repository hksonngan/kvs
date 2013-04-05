/*****************************************************************************/
/**
 *  @file   StochasticRendererBase.h
 *  @author Jun Nishimura
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
#ifndef KVS__STOCHASTIC_RENDERER_BASE_H_INCLUDE
#define KVS__STOCHASTIC_RENDERER_BASE_H_INCLUDE

#include <vector>
#include <kvs/Module>
#include <kvs/ObjectBase>
#include <kvs/RendererBase>
#include <kvs/FrameBufferObject>
#include <kvs/EnsembleAverageBuffer>
#include "StochasticRenderingEngine.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Base class of stochastic renderer.
 */
/*===========================================================================*/
class StochasticRendererBase : public kvs::RendererBase
{
    friend class StochasticRenderingCompositor;

    kvsModuleName( kvs::StochasticRendererBase );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::RendererBase );

public:

    typedef std::vector<kvs::StochasticRenderingEngine*> RenderingEngineList;

protected:

    size_t m_width; ///< rendering screen width
    size_t m_height; ///< rendering screen height
    size_t m_repetition_level; ///< repetition level
    size_t m_coarse_level; ///< coarse rendering level
    kvs::EnsembleAverageBuffer m_ensemble_buffer; ///< ensemble buffer
    kvs::FrameBufferObject m_framebuffer; ///< framebuffer object
    kvs::Texture2D m_color_texture; ///< color framebuffer
    kvs::Texture2D m_depth_texture; ///< depth framebuffer
    size_t m_random_texture_size; ///< size of random number texture
    kvs::Texture2D m_random_texture; ///< random number texture
    bool m_enable_lod; ///< flag to enable LOD controlling
    float m_modelview_matrix[16]; ///< modelview matrix
    bool m_clear_ensemble_buffer; ///< flag to clear ensemble buffer
    RenderingEngineList m_rendering_engines; ///< rendering engine list
    bool m_enable_exact_depth_testing; ///< flag to enable exact depth testing

public:

    StochasticRendererBase();
    virtual ~StochasticRendererBase();

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void initialize();
    void clear();
    void setRenderingEngine( kvs::StochasticRenderingEngine* rendering_engine );
    void clearEnsembleBuffer();
    void setRepetitionLevel( const size_t repetition_level );
    void enableLODControl( const size_t coarse_level = 1 );
    void disableLODControl();

protected:

    void create_image( const kvs::Camera* camera, const kvs::Light* light );
    kvs::StochasticRenderingEngine* get_engine( const size_t index );
    kvs::StochasticRenderingEngine* find_engine( const kvs::ObjectBase* object );
    kvs::StochasticRenderingEngine* find_engine( const std::string object_name );
    bool erase_engine( const kvs::ObjectBase* object );
    bool erase_engine( const std::string object_name );
    void update_engine();
    void enable_exact_depth_testing();
    void disable_exact_depth_testing();

    void initialize_opengl();
    void initialize_framebuffer_texture();
    void initialize_random_texture();
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_RENDERER_BASE_H_INCLUDE
