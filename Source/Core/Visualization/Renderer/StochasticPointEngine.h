/*****************************************************************************/
/**
 *  @file   StochasticPointEngine.h
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
#ifndef KVS__STOCHASTIC_POINT_ENGINE_H_INCLUDE
#define KVS__STOCHASTIC_POINT_ENGINE_H_INCLUDE

#include <kvs/PointObject>
#include <kvs/VertexBufferObject>
#include "StochasticRenderingEngine.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class for point object.
 */
/*===========================================================================*/
class StochasticPointEngine : public kvs::StochasticRenderingEngine
{
    // Class name.
    kvsClassName( kvs::StochasticPointEngine );

protected:

    class Particles;
    class Renderer;

protected:

    typedef kvs::StochasticRenderingEngine BaseClass;
    typedef GLushort IndexType;
    typedef GLfloat CoordType;
    typedef GLubyte ColorType;
    typedef GLbyte NormalType;

protected:

    const kvs::PointObject* m_ref_particle; ///< pointer to the point object (reference only)
    kvs::VertexBufferObject* m_vbo; ///< vertex buffer object (VBO) for the volume
    size_t m_loc_identifier; ///< location indectifier of VBO
    Particles* m_particles; ///< pointer to the point set
    Renderer* m_renderer;///< pointer to the renderer for VBO
    float m_zooming_factor; ///< zooming factor
    size_t m_circle_threshold; ///< threshold for the shape of the particle
    float m_point_size; ///< point size
    size_t m_repetition_level; ///< repetition level

public:

    StochasticPointEngine();
    StochasticPointEngine( const kvs::PointObject* point, const size_t repetition_level = 1 );
    virtual ~StochasticPointEngine();

    void initialize();
    void setPointSize( const float point_size );
    void setRepetitionLevel( const size_t repetition_level );

    const kvs::ObjectBase* object() const;
    const EngineType engineType() const;
    void attachObject( const kvs::ObjectBase* object );
    void clearEnsembleBuffer();

private:

    void create_vertexbuffer_from_point();
    void calculate_zooming_factor();
    void setup_shader( const float modelview_matrix[16] );
    void initialize_shader();
    void create_vertex_buffer();
    void download_vertex_buffer();
    void draw_vertex_buffer( const float modelview_matrix[16] );
};

/*===========================================================================*/
/**
 *  @brief  Particle class for stochastic point rendering engine.
 */
/*===========================================================================*/
class StochasticPointEngine::Particles
{

private:

    size_t m_nvertices; ///< number of vertices
    StochasticPointEngine::IndexType* m_indices; ///< index array
    StochasticPointEngine::CoordType* m_coords; ///< coordinate value array
    StochasticPointEngine::NormalType* m_normals; ///< normal vector array
    StochasticPointEngine::ColorType* m_colors; ///< color value array

public:

    Particles( void );
    ~Particles( void );

    void release( void );
    void create( const size_t nvertices, const bool has_normal );

    const bool hasNormal( void ) const;
    const size_t nvertices( void ) const;
    const size_t byteSizePerVertex( void ) const;
    const size_t byteSize( void ) const;
    const StochasticPointEngine::IndexType* indices( void ) const;
    StochasticPointEngine::IndexType* indices( void );
    const StochasticPointEngine::CoordType* coords( void ) const;
    StochasticPointEngine::CoordType* coords( void );
    const StochasticPointEngine::NormalType* normals( void ) const;
    StochasticPointEngine::NormalType* normals( void );
    const StochasticPointEngine::ColorType* colors( void ) const;
    StochasticPointEngine::ColorType* colors( void );

};

/*===========================================================================*/
/**
 *  @brief  Rendering class for stochastic point rendering engine.
 */
/*===========================================================================*/
class StochasticPointEngine::Renderer
{
    const StochasticPointEngine::Particles*  m_particles; //< pointer to the particles
    size_t  m_start; ///< start number of input vertices
    size_t  m_count; ///< number of vertices
    size_t  m_off_index; ///< offset bytes for the index array
    size_t  m_off_coord; ///< offset bytes for the coodinate value array
    size_t  m_off_normal; ///< offset bytes for the normal vector array
    size_t  m_off_color; ///< offset bytes for the color value array
    size_t  m_loc_identifier; ///< location identifier

public:

    Renderer();

    void set(
        const StochasticPointEngine::Particles* particles,
        const size_t start,
        const size_t count,
        const size_t loc_identifier );
    const bool download( kvs::VertexBufferObject& vbo );
    void draw() const;
};

} // end of namespace kvs

#endif // KVS__STOCHASTIC_POINT_ENGINE_H_INCLUDE
