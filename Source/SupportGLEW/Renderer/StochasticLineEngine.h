/*****************************************************************************/
/**
 *  @file   StochasticLineEngine.h
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
#ifndef KVS__GLEW__STOCHASTIC_LINE_ENGINE_H_INCLUDE
#define KVS__GLEW__STOCHASTIC_LINE_ENGINE_H_INCLUDE

#include "StochasticRenderingEngine.h"
#include <kvs/LineObject>
#include <kvs/VertexBufferObject>
#include <kvs/IndexBufferObject>


namespace kvs
{

namespace glew
{

#define KVS_GLEW_STOCHASTIC_LINE_ENGINE__EMBEDDED_SHADER

/*===========================================================================*/
/**
 *  @brief  StochasticRenderingEngine class for line object.
 */
/*===========================================================================*/
class StochasticLineEngine : public kvs::glew::StochasticRenderingEngine
{
    // Class name.
    kvsClassName( kvs::glew::StochasticLineEngine );

protected:

    typedef kvs::glew::StochasticRenderingEngine BaseClass;
    typedef GLushort IndexType;
    typedef GLfloat CoordType;
    typedef GLubyte ColorType;
    typedef GLuint ConnectType;

protected:

    const kvs::LineObject* m_ref_line; ///< pointer to line object (reference only)
    kvs::VertexBufferObject m_vbo; ///< buffer object for storing the indices, coords, values, and normals of the volume data
    kvs::IndexBufferObject m_ibo; ///< buffer object for stroing the connections of the volume data
    size_t m_loc_identifier; ///< location indentifier for VBO
    size_t m_off_index; ///< offset index for VBO
    size_t m_off_coord; ///< offset index of the coordinates for VBO
    size_t m_off_color; ///< offset index of the color values for VBO
    float m_line_opacity; ///< opacity value of the line object

public:

    StochasticLineEngine( void );

    StochasticLineEngine( const kvs::LineObject* line );

public:

    void initialize( void );

    void setOpacity( const unsigned char opacity );

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

#endif // KVS__GLEW__STOCHASTIC_LINE_ENGINE_H_INCLUDE
