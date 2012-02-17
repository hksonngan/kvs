/*****************************************************************************/
/**
 *  @file   StochasticTetrahedraEngine.h
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
#ifndef KVS__GLEW__STOCHASTIC_TETRAHEDRA_ENGINE_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_TETRAHEDRA_ENGINE_H_INCLUDE

#include "StochasticRenderingEngine.h"
#include <kvs/UnstructuredVolumeObject>
#include <kvs/TransferFunction>
#include <kvs/glew/GeometryShader>
#include <kvs/glew/VertexBufferObject>
#include <kvs/glew/IndexBufferObject>
#include <kvs/glew/PreIntegrationTable>


namespace kvs
{

namespace glew
{

#define KVS_GLEW_STOCHASTIC_TETRAHEDRA_ENGINE__EMBEDDED_SHADER

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class for unstructured volume object.
 */
/*===========================================================================*/
class StochasticTetrahedraEngine : public kvs::glew::StochasticRenderingEngine
{
    friend class StochasticRendererBase;

    // Class name.
    kvsClassName( kvs::glew::StochasticTetrahedraEngine );

protected:

    class Volume;
    class Renderer;

protected:

    typedef kvs::glew::StochasticTetrahedraEngine BaseClass;
    typedef GLushort IndexType;
    typedef GLfloat CoordType;
    typedef GLfloat ValueType;
    typedef GLbyte NormalType;
    typedef GLuint ConnectType;

protected:

    const kvs::UnstructuredVolumeObject* m_ref_volume; ///< pointer to the volume data (reference only)
    kvs::TransferFunction m_tfunc; ///< transfer function
    kvs::glew::VertexBufferObject m_vbo; ///< buffer object for storing the indices, coords, values, and normals of the volume data
    kvs::glew::IndexBufferObject m_ibo; ///< buffer object for stroing the connections of the volume data
    size_t m_loc_identifier; ///< location identifier
    size_t m_loc_values; ///< location identifier of values
    Volume* m_volume; ///< volume data for rendering on GPU
    Renderer* m_renderer; ///< renderer for the volume on GPU
    kvs::glew::PreIntegrationTable m_table; ///< pre-integration table
    kvs::Texture2D m_decomposition_texture; ///< texture for the tetrahedral decomposition
    kvs::Texture2D m_depth_texture; ///< depth texture
    float m_edge_size; ///< edge size
    size_t m_nsteps; ///< number of time steps for time-varying volume datasets
    size_t m_step; ///< time step for time-varying volume datasets

public:

    StochasticTetrahedraEngine( void );

    StochasticTetrahedraEngine( const kvs::UnstructuredVolumeObject* volume, const size_t nsteps = 1 );

public:

    void initialize( void );

    void setNSteps( const size_t nsteps );

    void setStep( const size_t step );

    void setEdgeSize( const float edge_size );

    void setTransferFunction( const kvs::TransferFunction& tfunc );

public:

    const kvs::TransferFunction& transferFunction( void ) const;

    kvs::TransferFunction& transferFunction( void );

public:

    const kvs::ObjectBase* object( void ) const;

    const EngineType engineType( void ) const;

    void attachObject( const kvs::ObjectBase* object );

    void clearEnsembleBuffer( void );

private:

    void initialize_decomposition_texture( void );

    void create_preintegration_table( void );

    template <typename T>
    void create_vertexbuffer_from_volume( void );

    void create_shaders(
        kvs::glew::ProgramObject& program_object,
        const kvs::glew::ShaderSource& vertex_source,
        const kvs::glew::ShaderSource& geometry_source,
        const kvs::glew::ShaderSource& fragment_source );

    void setup_shader( const float modelview_matrix[16] );

    void initialize_shader( void );

    void create_vertex_buffer( void );

    void download_vertex_buffer( void );

    void draw_vertex_buffer( const float modelview_matrix[16] );

    void set_depth_texture( const kvs::Texture2D& depth_texture );
};

/*===========================================================================*/
/**
 *  @brief  Volume data class for the stochastic renderer.
 */
/*===========================================================================*/
class StochasticTetrahedraEngine::Volume
{
private:

    size_t m_nsteps; ///< number of time steps
    size_t m_nvertices; ///< number of vertices
    size_t m_ncells; ///< number of cells
    StochasticTetrahedraEngine::IndexType* m_indices; ///< index array
    StochasticTetrahedraEngine::CoordType* m_coords; ///< coordinate value array
    StochasticTetrahedraEngine::ValueType* m_values; ///< color value array
    StochasticTetrahedraEngine::NormalType* m_normals; ///< normal array
    StochasticTetrahedraEngine::ConnectType* m_connections; ///< connection array

public:

    Volume( void );

    ~Volume( void );

public:

    void release( void );

    void create( const size_t nsteps, const size_t nvertices, const size_t ncells );

public:

    const size_t nvertices( void ) const;

    const size_t ncells( void ) const;

    const size_t byteSizePerVertex( void ) const;

    const size_t byteSizeOfVertex( void ) const;

    const size_t byteSizePerCell( void ) const;

    const size_t byteSizeOfCell( void ) const;

    const StochasticTetrahedraEngine::IndexType* indices( void ) const;

    StochasticTetrahedraEngine::IndexType* indices( void );

    const StochasticTetrahedraEngine::CoordType* coords( void ) const;

    StochasticTetrahedraEngine::CoordType* coords( void );

    const StochasticTetrahedraEngine::ValueType* values( void ) const;

    StochasticTetrahedraEngine::ValueType* values( void );

    const StochasticTetrahedraEngine::NormalType* normals( void ) const;

    StochasticTetrahedraEngine::NormalType* normals( void );

    const StochasticTetrahedraEngine::ConnectType* connections( void ) const;

    StochasticTetrahedraEngine::ConnectType* connections( void );

};

/*===========================================================================*/
/**
 *  @brief  Renderer class for the stochastic renderer.
 */
/*===========================================================================*/
class StochasticTetrahedraEngine::Renderer
{
private:

    const StochasticTetrahedraEngine::Volume* m_volume; ///< pointer to the volume
    size_t m_nsteps; ///< number of time steps
    size_t m_nvertices; ///< number of vertices
    size_t m_ncells; ///< number of cells
    size_t m_off_index; ///< offset bytes for the index array
    size_t m_off_coord; ///< offset bytes for the coodinate value array
    size_t m_off_value; ///< offset bytes for the value array
    size_t m_off_normal; ///< offset bytes for the normal array
    size_t m_loc_identifier; ///< location identifier
    size_t m_loc_values; ///< location identifier of values

public:

    Renderer( void );

    void set(
        const StochasticTetrahedraEngine::Volume* volume,
        const size_t nsteps,
        const size_t nvertices,
        const size_t ncells,
        const size_t loc_identifier,
        const size_t loc_values );

    const bool download(
        kvs::glew::VertexBufferObject& vbo,
        kvs::glew::IndexBufferObject& ibo );

    void draw( const size_t step ) const;

};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_TETRAHEDRA_ENGINE_H_INCLUDE
