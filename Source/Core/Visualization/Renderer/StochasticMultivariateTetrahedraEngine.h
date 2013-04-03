/*****************************************************************************/
/**
 *  @file   StochasticMultivariateTetrahedraEngine.h
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
#ifndef KVS__STOCHASTIC_MULTIVARIATE_TETRAHEDRA_ENGINE_H_INCLUDE
#define KVS__STOCHASTIC_MULTIVARIATE_TETRAHEDRA_ENGINE_H_INCLUDE

#include "StochasticRenderingEngine.h"
#include "StochasticTetrahedraEngine.h"
#include <kvs/UnstructuredVolumeObject>
#include <kvs/TransferFunction>
#include <kvs/GeometryShader>
#include <kvs/VertexBufferObject>
#include <kvs/IndexBufferObject>
#include <kvs/PreIntegrationTable>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticMultivariateTetrahedraEngine : public kvs::StochasticTetrahedraEngine
{
    friend class StochasticRendererBase;

    // Class name.
    kvsClassName( kvs::StochasticMultivariateTetrahedraEngine );

public:

    typedef kvs::StochasticTetrahedraEngine BaseClass;

protected:

    kvs::TransferFunction m_tfunc2; ///< transfer function for the 2nd component
    kvs::PreIntegrationTable m_table2; ///< pre-integration table for the 2nd component
    bool m_show_flag1; ///< show flag for the 1st component
    bool m_show_flag2; ///< show flag for the 2nd component

public:

    StochasticMultivariateTetrahedraEngine();
    StochasticMultivariateTetrahedraEngine( const kvs::UnstructuredVolumeObject* volume, const size_t nsteps = 1 );

    void initialize();
    void setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index );

    const kvs::TransferFunction& transferFunction( const size_t index ) const;
    kvs::TransferFunction& transferFunction( const size_t index );
    const bool isShown( const size_t index ) const;
    void show( const size_t index );
    void hide( const size_t index );

    const EngineType engineType() const;
    void attachObject( const kvs::ObjectBase* object );

private:

    void create_preintegration_table();
    template <typename T>
    void create_vertexbuffer_from_volume();
    void setup_shader( const float modelview_matrix[16] );
    void initialize_shader();
    void create_vertex_buffer();
    void draw_vertex_buffer( const float modelview_matrix[16] );
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_MULTIVARIATE_TETRAHEDRA_ENGINE_H_INCLUDE
