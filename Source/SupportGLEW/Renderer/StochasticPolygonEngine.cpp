/*****************************************************************************/
/**
 *  @file   StochasticPolygonEngine.cpp
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
#include "StochasticPolygonEngine.h"
#if defined ( KVS_GLEW_STOCHASTIC_POLYGON_ENGINE__EMBEDDED_SHADER )
#include "StochasticRenderingEngine/Shader.h"
#endif


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPolygonEngine class.
 */
/*===========================================================================*/
StochasticPolygonEngine::StochasticPolygonEngine( void )
{
    this->initialize();
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPolygonEngine class.
 *  @param  polygon [in] pointer to a plygon object
 */
/*===========================================================================*/
StochasticPolygonEngine::StochasticPolygonEngine( const kvs::PolygonObject* polygon )
{
    this->initialize();
    this->attachObject( polygon );
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticPolygonEngine::initialize( void )
{
    m_ref_polygon = NULL;

    m_loc_identifier = 0;
    m_off_index = 0;
    m_off_coord = 0;
    m_off_color = 0;
    m_off_normal = 0;

    m_polygon_offset = 0.001f;
}

/*===========================================================================*/
/**
 *  @brief  Sets a polygon offset.
 *  @param  polygon_offset [in] polygon offset
 */
/*===========================================================================*/
void StochasticPolygonEngine::setPolygonOffset( const float polygon_offset )
{
    m_polygon_offset = polygon_offset;
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the polygon object.
 *  @return pointer to the polygon object
 */
/*===========================================================================*/
const kvs::ObjectBase* StochasticPolygonEngine::object( void ) const
{
    return( m_ref_polygon );
}

/*===========================================================================*/
/**
 *  @brief  Attaches a polygon object.
 *  @param  object [in] pointer to a polygon object
 */
/*===========================================================================*/
void StochasticPolygonEngine::attachObject( const kvs::ObjectBase* object )
{
    const kvs::PolygonObject* polygon = kvs::PolygonObject::DownCast( object );

    // Check polygon object for rendering.
    if ( polygon->polygonType() != kvs::PolygonObject::Triangle )
    {
        kvsMessageError( "Polygon type of this polygon is not triangle." );
        return;
    }

    if ( polygon->ncolors() != polygon->nvertices() && polygon->ncolors() > 1 )
    {
        kvsMessageError( "Color type of this polygon is not vertex color." );
        return;
    }

    if ( polygon->nopacities() != polygon->nvertices() && polygon->nopacities() > 1 )
    {
        kvsMessageError( "Opacity type of this polygon is not vertex opacity." );
        return;
    }

    if ( polygon->nnormals() != polygon->nvertices() && polygon->nnormals() > 0 )
    {
        kvsMessageError( "Normal type of this polygon is not supported." );
        return;
    }

    m_ref_polygon = polygon;

    if ( m_ref_polygon->normals().pointer() == NULL ||
         m_ref_polygon->nnormals() == 0 )
    {
        BaseClass::disableShading();
    }

    BaseClass::enable_updating_vbo();
}

/*===========================================================================*/
/**
 *  @brief  Returns the rendering engine type.
 *  @return rendering engine type
 */
/*===========================================================================*/
const StochasticRenderingEngine::EngineType StochasticPolygonEngine::engineType( void ) const
{
    return( BaseClass::Polygon );
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffer.
 */
/*===========================================================================*/
void StochasticPolygonEngine::clearEnsembleBuffer( void )
{
    m_repetition_count = 0;
}

/*===========================================================================*/
/**
 *  @brief  Sets parameters to the shaders.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticPolygonEngine::setup_shader( const float modelview_matrix[16] )
{
    const size_t random_texture_size = m_random_texture.width();
    const int scramble_count = m_repetition_count++ * 12347;
    const float rp_x = ( scramble_count ) % random_texture_size;
    const float rp_y = ( scramble_count / random_texture_size ) % random_texture_size;
    const GLfloat random_texture_size_inv = 1.0f / random_texture_size;
    const GLfloat screen_scale_x = m_width * 0.5f;
    const GLfloat screen_scale_y = m_height * 0.5f;

    m_shader_program.setUniformValuef( "random_texture_size_inv", random_texture_size_inv );
    m_shader_program.setUniformValuef( "random_offset", rp_x, rp_y );
    m_shader_program.setUniformValuef( "screen_scale", screen_scale_x, screen_scale_y );
    m_shader_program.setUniformValuef( "screen_scale_inv", 1.0 / m_width, 1.0 / m_height );
    m_shader_program.setUniformValuei( "random_texture", 0 );
    m_shader_program.setUniformValuef( "polygon_offset", m_polygon_offset );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the shaders.
 */
/*===========================================================================*/
void StochasticPolygonEngine::initialize_shader( void )
{
#if defined( KVS_GLEW_STOCHASTIC_POLYGON_ENGINE__EMBEDDED_SHADER )
    const std::string vert_code = kvs::glew::glsl::StochasticRenderingEngine::Vertex::polygon;
    const std::string frag_code = kvs::glew::glsl::StochasticRenderingEngine::Fragment::polygon;
#else
    const std::string vert_code = "StochasticRenderingEngine/polygon.vert";
    const std::string frag_code = "StochasticRenderingEngine/polygon.frag";
#endif

    kvs::glew::ShaderSource vert( vert_code );
    kvs::glew::ShaderSource frag( frag_code );

    if ( BaseClass::isEnabledShading() )
    {
        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading: frag.define("ENABLE_LAMBERT_SHADING"); break;
        case kvs::Shader::PhongShading: frag.define("ENABLE_PHONG_SHADING"); break;
        case kvs::Shader::BlinnPhongShading: frag.define("ENABLE_BLINN_PHONG_SHADING"); break;
        default: /* NO SHADING */ break;
        }

        GLboolean status = 0; glGetBooleanv( GL_LIGHT_MODEL_TWO_SIDE, &status );
        if ( status == GL_TRUE ) { frag.define("ENABLE_TWO_SIDE_LIGHTING"); }
    }

    if ( BaseClass::is_enabled_exact_depth_testing() )
    {
        vert.define("ENABLE_EXACT_DEPTH_TESTING");
        frag.define("ENABLE_EXACT_DEPTH_TESTING");
    }

    this->create_shaders( m_shader_program, vert, frag );
    m_loc_identifier = m_shader_program.attributeLocation( "identifier" );

    if ( BaseClass::isEnabledShading() )
    {
        m_shader_program.bind();
        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading:
        {
            const GLfloat Ka = ((kvs::Shader::Lambert*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::Lambert*)(BaseClass::m_shader))->Kd;
            m_shader_program.setUniformValuef( "shading.Ka", Ka );
            m_shader_program.setUniformValuef( "shading.Kd", Kd );
            break;
        }
        case kvs::Shader::PhongShading:
        {
            const GLfloat Ka = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Kd;
            const GLfloat Ks = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Ks;
            const GLfloat S  = ((kvs::Shader::Phong*)(BaseClass::m_shader))->S;
            m_shader_program.setUniformValuef( "shading.Ka", Ka );
            m_shader_program.setUniformValuef( "shading.Kd", Kd );
            m_shader_program.setUniformValuef( "shading.Ks", Ks );
            m_shader_program.setUniformValuef( "shading.S",  S );
            break;
        }
        case kvs::Shader::BlinnPhongShading:
        {
            const GLfloat Ka = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Kd;
            const GLfloat Ks = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Ks;
            const GLfloat S  = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->S;
            m_shader_program.setUniformValuef( "shading.Ka", Ka );
            m_shader_program.setUniformValuef( "shading.Kd", Kd );
            m_shader_program.setUniformValuef( "shading.Ks", Ks );
            m_shader_program.setUniformValuef( "shading.S",  S );
            break;
        }
        default: /* NO SHADING */ break;
        }
        m_shader_program.unbind();
    }
}

/*===========================================================================*/
/**
 *  @brief  Creates the vertex and index buffer.
 */
/*===========================================================================*/
void StochasticPolygonEngine::create_vertex_buffer( void )
{
    m_vbo.release();
    m_ibo.release();

    const size_t nvertices = m_ref_polygon->nvertices();
    const size_t npolygons = m_ref_polygon->nconnections();

    const bool has_color    = m_ref_polygon->ncolors() > 1;
    const bool has_opacity  = ( m_ref_polygon->nopacities() > 1 && has_color );
    const bool has_normal   = ( m_ref_polygon->nnormals() > 0 && BaseClass::isEnabledShading() );
    const bool has_connect  = m_ref_polygon->nconnections() > 0;

    const size_t size_i = sizeof(IndexType) * 2 * nvertices;
    const size_t size_v = sizeof(CoordType) * 3 * nvertices;
    const size_t size_c = has_color ? sizeof(ColorType) * 4 * nvertices : 0;
    const size_t size_n = sizeof(NormalType) * 3 * nvertices;
    const size_t size_of_vertex = size_i + size_v + size_c + size_n;

    const size_t off_i = 0;
    const size_t off_v = off_i + size_i;
    const size_t off_c = off_v + size_v;
    const size_t off_n = off_c + size_c;

    const size_t random_texture_size = m_random_texture.width();
    kvs::ValueArray<IndexType> indices( 2 * nvertices );
    for ( size_t i = 0; i < nvertices; i++ )
    {
        unsigned int index = i * 12347;
        indices[ i * 2     ] = static_cast<IndexType>( index % random_texture_size );
        indices[ i * 2 + 1 ] = static_cast<IndexType>( ( index / random_texture_size ) % random_texture_size );
    }

    kvs::ValueArray<ColorType> colors;
    if ( has_color )
    {
        const unsigned char* p_colors = m_ref_polygon->colors().pointer();
        const unsigned char* p_opacities = m_ref_polygon->opacities().pointer();
        colors.allocate( 4 * nvertices );
        for ( size_t i = 0; i < nvertices; i++ )
        {
            colors[ i * 4     ] = p_colors[ i * 3     ];
            colors[ i * 4 + 1 ] = p_colors[ i * 3 + 1 ];
            colors[ i * 4 + 2 ] = p_colors[ i * 3 + 2 ];
            if ( has_opacity )
            {
                colors[ i * 4 + 3 ] = p_opacities[i];
            }
            else
            {
                colors[ i * 4 + 3 ] = p_opacities[0];
            }
        }
    }

    kvs::ValueArray<NormalType> normals;
    if ( has_normal )
    {
        const float* p_normals = m_ref_polygon->normals().pointer();
        normals.allocate( 3 * nvertices );
        for ( size_t i = 0; i < nvertices; i++ )
        {
            const kvs::Vector3f v( p_normals + i * 3 );
            const kvs::Vector3f n = v.normalizedVector() * 127.0f;
            normals[ i * 3     ] = static_cast<NormalType>(n[0]);
            normals[ i * 3 + 1 ] = static_cast<NormalType>(n[1]);
            normals[ i * 3 + 2 ] = static_cast<NormalType>(n[2]);
        }
    }

    const IndexType*  ptr_i = indices.pointer();
    const CoordType*  ptr_v = m_ref_polygon->coords().pointer();
    const ColorType*  ptr_c = colors.pointer();
    const NormalType* ptr_n = normals.pointer();

    m_vbo.create( size_of_vertex );
    m_vbo.bind();
    m_vbo.download( size_i, ptr_i, off_i );
    m_vbo.download( size_v, ptr_v, off_v );
    if ( has_color )  m_vbo.download( size_c, ptr_c, off_c );
    if ( has_normal ) m_vbo.download( size_n, ptr_n, off_n );

    if ( has_connect )
    {
        const size_t size_of_polygon = sizeof(ConnectType) * 3 * npolygons;
        const ConnectType* ptr_conn = m_ref_polygon->connections().pointer();

        m_ibo.create( size_of_polygon );
        m_ibo.bind();
        m_ibo.download( size_of_polygon, ptr_conn, 0 );
    }

    GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "Vertex Buffer Object download failed: %s(%d).", gluErrorString( error ), error );
    }

    m_off_index  = off_i;
    m_off_coord  = off_v;
    m_off_color  = off_c;
    m_off_normal = off_n;
}

/*===========================================================================*/
/**
 *  @brief  Downloads the vertex dataset to the vertex buffer.
 */
/*===========================================================================*/
void StochasticPolygonEngine::download_vertex_buffer( void )
{
    this->create_vertex_buffer();
}

/*===========================================================================*/
/**
 *  @brief  Draws the vertex buffer.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticPolygonEngine::draw_vertex_buffer( const float modelview_matrix[16] )
{
    m_vbo.bind();
    m_ibo.bind();

    glActiveTexture(GL_TEXTURE0);     m_random_texture.bind();          glEnable(GL_TEXTURE_2D);

    m_shader_program.bind();

    this->setup_shader( modelview_matrix );

    const size_t npolygons = m_ref_polygon->nconnections();

    const bool has_color    = m_ref_polygon->ncolors() > 1;
    //const bool has_opacity  = ( m_ref_polygon->nopacities() > 1 && has_color );
    const bool has_normal   = ( m_ref_polygon->nnormals() > 0 && BaseClass::isEnabledShading() );
    const bool has_connect  = m_ref_polygon->nconnections() > 0;

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, (char*)(m_off_coord) );

    glEnableVertexAttribArray( m_loc_identifier );
    glVertexAttribPointer( m_loc_identifier, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, (char*)(m_off_index) );

    kvs::RGBColor color = m_ref_polygon->color();
    const unsigned char opacity = m_ref_polygon->opacity();
    glColor4ub( color.r(), color.g(), color.b(), opacity );

    if ( has_color )
    {
        glEnableClientState( GL_COLOR_ARRAY );
        glColorPointer( 4, GL_UNSIGNED_BYTE, 0, (char*)(m_off_color) );
    }

    if ( has_normal )
    {
        glEnableClientState( GL_NORMAL_ARRAY );
        glNormalPointer( GL_BYTE, 0, (char*)(m_off_normal) );
    }

    if ( has_connect )
    {
        glDrawElements( GL_TRIANGLES, 3 * npolygons, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( GL_TRIANGLES, 0, 3 * npolygons );
    }

    if ( has_normal ) glDisableClientState( GL_NORMAL_ARRAY );
    if ( has_color )  glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableVertexAttribArray( m_loc_identifier );

    m_shader_program.unbind();

    glActiveTexture(GL_TEXTURE0);    m_random_texture.unbind();         glDisable(GL_TEXTURE_2D);
}

} // end of namespace glew

} // end of namespace kvs
