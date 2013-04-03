/*****************************************************************************/
/**
 *  @file   StochasticRenderingEngine.h
 *  @author Naoya Maeda
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
#ifndef KVS__STOCHASTIC_UNIFORM_GRID_ENGINE_H_INCLUDE
#define KVS__STOCHASTIC_UNIFORM_GRID_ENGINE_H_INCLUDE

#include <kvs/PolygonObject>
#include <kvs/StructuredVolumeObject>
#include <kvs/VertexBufferObject>
#include <kvs/IndexBufferObject>
#include <kvs/TransferFunction>
#include "StochasticRenderingEngine.h"
#include <kvs/Xorshift128>
#include <kvs/PreIntegrationTable>


namespace kvs
{

class TransferFunction;

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class for polygon object.
 */
/*===========================================================================*/
class StochasticUniformGridEngine : public kvs::StochasticRenderingEngine
{
    // Class name.
    kvsClassName( kvs::StochasticUniformGridEngine );

private:
    typedef kvs::StochasticRenderingEngine BaseClass;

private:
    const kvs::StructuredVolumeObject* m_ref_volume;
    size_t m_loc_identifier; ///< location indentifier for VBO
    GLuint m_volume_texture_name;
    kvs::TransferFunction m_transfer_function;
    kvs::Xorshift128 m_rng;
    GLuint m_pre_table_name;

public:
    StochasticUniformGridEngine();

    StochasticUniformGridEngine( const kvs::StructuredVolumeObject* volume );

public:
    void initialize();

public:
    const kvs::ObjectBase* object() const;

    const EngineType engineType() const;

    void attachObject( const kvs::ObjectBase* object );

    void clearEnsembleBuffer();

    void setTransferFunction( const kvs::TransferFunction& );

private:
    void setup_shader( const float modelview_matrix[16] );
    void initialize_shader();
    void create_vertex_buffer(){}
    void download_vertex_buffer(){}
    void draw_vertex_buffer( const float modelview_matrix[16] );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_UNIFORM_GRID_ENGINE_H_INCLUDE
