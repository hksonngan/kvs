/*****************************************************************************/
/**
 *  @file   StochasticPolygonEngine.h
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
#ifndef KVS__GLEW__STOCHASTIC_POLYGON_ENGINE_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_POLYGON_ENGINE_H_INCLUDE

#include "StochasticRenderingEngine.h"
#include <kvs/PolygonObject>
#include <kvs/VertexBufferObject>
#include <kvs/IndexBufferObject>


namespace kvs
{

namespace glew
{

#define KVS_GLEW_STOCHASTIC_POLYGON_ENGINE__EMBEDDED_SHADER

/*===========================================================================*/
/**
 *  @brief  Stochastic rendering engine class for polygon object.
 */
/*===========================================================================*/
class StochasticPolygonEngine : public kvs::glew::StochasticRenderingEngine
{
    // Class name.
    kvsClassName( kvs::glew::StochasticPolygonEngine );

protected:

    typedef kvs::glew::StochasticRenderingEngine BaseClass;
    typedef GLushort IndexType;
    typedef GLfloat CoordType;
    typedef GLubyte ColorType;
    typedef GLbyte NormalType;
    typedef GLuint ConnectType;

protected:

    const kvs::PolygonObject* m_ref_polygon; ///< pointer to a polygon object (reference only)
    kvs::VertexBufferObject m_vbo; ///< buffer object for storing the indices, coords, values, and normals of volume data
    kvs::IndexBufferObject m_ibo; ///< buffer object for stroing the connections of volume data
    size_t m_loc_identifier; ///< location indentifier for VBO
    size_t m_off_index; ///< offset index for VBO
    size_t m_off_coord; ///< offset index of coordinates for VBO
    size_t m_off_color; ///< offset index of color values for VBO
    size_t m_off_normal; ///< offset index of normal vector for VBO
    float m_polygon_offset; ///< polygon offset

public:

    StochasticPolygonEngine( void );

    StochasticPolygonEngine( const kvs::PolygonObject* polygon );

public:

    void initialize( void );

    void setPolygonOffset( const float polygon_offset );

public:

    const kvs::ObjectBase* object( void ) const;

    const EngineType engineType( void ) const;

    void attachObject( const kvs::ObjectBase* object );

    void clearEnsembleBuffer( void );

private:

    void setup_shader( const float modelview_matrix[16] );

    void initialize_shader( void );

    void create_vertex_buffer( void );

    void download_vertex_buffer( void );

    void draw_vertex_buffer( const float modelview_matrix[16] );
};

} // end of namespace glew

} // end of namespace kvs

#endif // KVS__GLEW__STOCHASTIC_POLYGON_ENGINE_H_INCLUDE
