/*****************************************************************************/
/**
 *  @file   StochasticUniformGridRenderer.h
 *  @author Naoya Maeda, Naohisa Sakamoto
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
#ifndef KVS__STOCHASTIC_UNIFORM_GRID_RENDERER_H_INCLUDE
#define KVS__STOCHASTIC_UNIFORM_GRID_RENDERER_H_INCLUDE

#include <kvs/Module>
#include <kvs/ProgramObject>
#include <kvs/Texture2D>
#include <kvs/Texture3D>
#include <kvs/Xorshift128>
#include <kvs/TransferFunction>
#include "StochasticRenderingEngine.h"
#include "StochasticRendererBase.h"


namespace kvs
{

class StructuredVolumeObject;

/*===========================================================================*/
/**
 *  @brief  Stochastic uniform grid renderer class.
 */
/*===========================================================================*/
class StochasticUniformGridRenderer : public kvs::StochasticRendererBase
{
    kvsModuleName( kvs::StochasticUniformGridRenderer );
    kvsModuleBaseClass( kvs::StochasticRendererBase );
    kvsModuleCategory( Renderer );

public:

    class Engine;

public:

    StochasticUniformGridRenderer();
    void setNumberOfSlices( const size_t nslices );
    void setTransferFunction( const kvs::TransferFunction& transfer_function );
};

/*===========================================================================*/
/**
 *  @brief  Engine class for stochastic uniform grid renderer.
 */
/*===========================================================================*/
class StochasticUniformGridRenderer::Engine : public kvs::StochasticRenderingEngine
{
private:

    size_t m_random_index; ///< index used for refering the random texture
    size_t m_nslices; ///< number of slices
    bool m_transfer_function_changed; ///< flag for changin transfer function
    kvs::TransferFunction m_transfer_function; ///< transfer function
    kvs::ProgramObject m_shader_program; ///< shader program
    kvs::Texture3D m_volume_texture; ///< volume data
    kvs::Texture2D m_preintegration_table; ///< pre-integration table 2D
    kvs::Xorshift128 m_random; ///< random number generator

public:

    Engine();
    void release();
    void create( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void update( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
    void setup( const bool reset_count );
    void draw( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void setNumberOfSlices( const size_t nslices ) { m_nslices = nslices; }
    void setTransferFunction( const kvs::TransferFunction& transfer_function )
    {
        m_transfer_function = transfer_function;
        m_transfer_function_changed = true;
    }

private:

    void create_shader_program();
    void create_texture_object( const kvs::StructuredVolumeObject* volume );
    void create_preintegration_table();
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_UNIFORM_GRID_RENDERER_H_INCLUDE
