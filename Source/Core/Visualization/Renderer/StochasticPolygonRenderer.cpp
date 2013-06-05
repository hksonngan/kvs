/*****************************************************************************/
/**
 *  @file   StochasticPolygonRenderer.cpp
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
#include "StochasticPolygonRenderer.h"
#include <cmath>
#include <kvs/OpenGL>
#include <kvs/PolygonObject>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/Assert>
#include <kvs/Message>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Returns vertex-normal array.
 *  @param  polygon [in] pointer to the polygon object
 */
/*===========================================================================*/
kvs::ValueArray<kvs::Real32> VertexNormals( const kvs::PolygonObject* polygon )
{
    if ( polygon->normals().size() != 0 &&
         polygon->normalType() == kvs::PolygonObject::VertexNormal )
    {
        return polygon->normals();
    }

    const size_t nconnections = polygon->numberOfConnections();
    const size_t nvertices = polygon->numberOfVertices();
    const size_t npolygons = nconnections == 0 ? nvertices / 3 : nconnections;
    const kvs::Real32* pcoords = polygon->coords().data();
    const kvs::UInt32* pconnections = polygon->connections().data();

    kvs::ValueArray<kvs::Real32> normals( nvertices * 3 );
    normals.fill( 0 );
    for ( size_t i = 0; i < npolygons; i++ )
    {
        size_t index[3];
        kvs::Vec3 vertex[3];
        for ( size_t j = 0; j < 3; j++ )
        {
            index[j] = nconnections > 0 ? pconnections[ 3 * i + j ] : 3 * i + j;
            vertex[j] = kvs::Vec3( pcoords + 3 * index[j] );
        }

        const kvs::Vec3 normal( ( vertex[1] - vertex[0] ).cross( vertex[2] - vertex[0] ) );
        for ( size_t j = 0; j < 3; j++ )
        {
            normals[ 3 * index[j] + 0 ] += normal.x();
            normals[ 3 * index[j] + 1 ] += normal.y();
            normals[ 3 * index[j] + 2 ] += normal.z();
        }
    }

    const kvs::Real32* pnormals = normals.data();
    for ( size_t i = 0; i < nvertices; i++ )
    {
        kvs::Vec3 normal( pnormals + 3 * i );
        normal.normalize();
        normals[ 3 * i + 0 ] = normal.x();
        normals[ 3 * i + 1 ] = normal.y();
        normals[ 3 * i + 2 ] = normal.z();
    }

    return normals;
}

/*===========================================================================*/
/**
 *  @brief  Returns vertex-color array.
 *  @param  polygon [in] pointer to the polygon object
 */
/*===========================================================================*/
kvs::ValueArray<kvs::UInt8> VertexColors( const kvs::PolygonObject* polygon )
{
    const size_t nvertices = polygon->numberOfVertices();
    const bool is_single_color = polygon->colors().size() == 3;
    const bool is_single_alpha = polygon->opacities().size() == 1;
    const kvs::UInt8* pcolors = polygon->colors().data();
    const kvs::UInt8* palphas = polygon->opacities().data();

    kvs::ValueArray<kvs::UInt8> colors( nvertices * 4 );
    for ( size_t i = 0; i < nvertices; i++ )
    {
        colors[ 4 * i + 0 ] = is_single_color ? pcolors[0] : pcolors[ 3 * i + 0 ];
        colors[ 4 * i + 1 ] = is_single_color ? pcolors[1] : pcolors[ 3 * i + 1 ];
        colors[ 4 * i + 2 ] = is_single_color ? pcolors[2] : pcolors[ 3 * i + 2 ];
        colors[ 4 * i + 3 ] = is_single_alpha ? palphas[0] : palphas[i];
    }

    return colors;
}

}


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPolygonRenderer class.
 */
/*===========================================================================*/
StochasticPolygonRenderer::StochasticPolygonRenderer():
    StochasticRendererBase( new Engine() )
{
}

/*===========================================================================*/
/**
 *  @brief  Sets a polygon offset.
 *  @param  offset [in] offset value
 */
/*===========================================================================*/
void StochasticPolygonRenderer::setPolygonOffset( const float offset )
{
    static_cast<Engine&>( engine() ).setPolygonOffset( offset );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Engine class.
 */
/*===========================================================================*/
StochasticPolygonRenderer::Engine::Engine():
    m_has_normal( false ),
    m_has_connection( false ),
    m_random_index( 0 ),
    m_polygon_offset( 0.0f )
{
}

/*===========================================================================*/
/**
 *  @brief  Releases the GPU resources.
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::release()
{
    m_shader_program.release();
    m_vbo.release();
    m_ibo.release();
}

/*===========================================================================*/
/**
 *  @brief  Create shaders, VBO, and framebuffers.
 *  @param  polygon [in] pointer to the polygon object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::create( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::PolygonObject* polygon = kvs::PolygonObject::DownCast( object );
    m_has_normal = polygon->normals().size() > 0;
    m_has_connection = polygon->numberOfConnections() > 0;
    if ( !m_has_normal ) setEnabledShading( false );

    attachObject( object );
    createRandomTexture();
    this->create_shader_program();
    this->create_buffer_object( polygon );
}

/*===========================================================================*/
/**
 *  @brief  Update.
 *  @param  polygon [in] pointer to the polygon object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::update( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
}

/*===========================================================================*/
/**
 *  @brief  Set up.
 *  @param  reset_count [in] flag for the repetition count
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::setup( const bool reset_count )
{
    if ( reset_count ) resetRepetitions();
    m_random_index = m_shader_program.attributeLocation("random_index");
}

/*===========================================================================*/
/**
 *  @brief  Draw an ensemble.
 *  @param  polygon [in] pointer to the polygon object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::draw( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::PolygonObject* polygon = kvs::PolygonObject::DownCast( object );

    kvs::VertexBufferObject::Binder bind1( m_vbo );
    kvs::ProgramObject::Binder bind2( m_shader_program );
    kvs::Texture::Binder bind3( randomTexture() );
    {
        const size_t size = randomTextureSize();
        const int count = repetitionCount() * 12347;
        const float offset_x = static_cast<float>( ( count ) % size );
        const float offset_y = static_cast<float>( ( count / size ) % size );
        const kvs::Vec2 random_offset( offset_x, offset_y );

        m_shader_program.setUniform( "random_texture_size_inv", 1.0f / randomTextureSize() );
        m_shader_program.setUniform( "random_offset", random_offset );
        m_shader_program.setUniform( "random_texture", 0 );
        m_shader_program.setUniform( "polygon_offset", m_polygon_offset );

        const size_t nconnections = polygon->numberOfConnections();
        const size_t nvertices = polygon->numberOfVertices();
        const size_t npolygons = nconnections == 0 ? nvertices / 3 : nconnections;
        const size_t index_size = nvertices * 2 * sizeof( kvs::UInt16 );
        const size_t coord_size = nvertices * 3 * sizeof( kvs::Real32 );
        const size_t color_size = nvertices * 4 * sizeof( kvs::UInt8 );

        KVS_GL_CALL( glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ) );

        // Enable coords.
        KVS_GL_CALL( glEnableClientState( GL_VERTEX_ARRAY ) );
        KVS_GL_CALL( glVertexPointer( 3, GL_FLOAT, 0, (GLbyte*)NULL + index_size ) );

        // Enable colors.
        KVS_GL_CALL( glEnableClientState( GL_COLOR_ARRAY ) );
        KVS_GL_CALL( glColorPointer( 4, GL_UNSIGNED_BYTE, 0, (GLbyte*)NULL + index_size + coord_size ) );

        // Enable normals.
        if ( m_has_normal )
        {
            KVS_GL_CALL( glEnableClientState( GL_NORMAL_ARRAY ) );
            KVS_GL_CALL( glNormalPointer( GL_FLOAT, 0, (GLbyte*)NULL + index_size + coord_size + color_size ) );
        }

        // Enable random index.
        KVS_GL_CALL( glEnableVertexAttribArray( m_random_index ) );
        KVS_GL_CALL( glVertexAttribPointer( m_random_index, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, (GLubyte*)NULL + 0 ) );

        // Draw triangles.
        if ( m_has_connection )
        {
            kvs::IndexBufferObject::Binder bind4( m_ibo );
            KVS_GL_CALL( glDrawElements( GL_TRIANGLES, 3 * npolygons, GL_UNSIGNED_INT, 0 ) );
        }
        else
        {
            KVS_GL_CALL( glDrawArrays( GL_TRIANGLES, 0, 3 * npolygons ) );
        }

        // Disable coords.
        KVS_GL_CALL( glDisableClientState( GL_VERTEX_ARRAY ) );

        // Disable colors.
        KVS_GL_CALL( glDisableClientState( GL_COLOR_ARRAY ) );

        // Disable normals.
        if ( m_has_normal )
        {
            KVS_GL_CALL( glDisableClientState( GL_NORMAL_ARRAY ) );
        }

        // Disable random index.
        KVS_GL_CALL( glDisableVertexAttribArray( m_random_index ) );
    }

    countRepetitions();
}

/*===========================================================================*/
/**
 *  @brief  Creates shader program.
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::create_shader_program()
{
    kvs::ShaderSource vert( "SR_polygon.vert" );
    kvs::ShaderSource frag( "SR_polygon.frag" );
    if ( isEnabledShading() )
    {
        switch ( shader().type() )
        {
        case kvs::Shader::LambertShading: frag.define("ENABLE_LAMBERT_SHADING"); break;
        case kvs::Shader::PhongShading: frag.define("ENABLE_PHONG_SHADING"); break;
        case kvs::Shader::BlinnPhongShading: frag.define("ENABLE_BLINN_PHONG_SHADING"); break;
        default: break; // NO SHADING
        }

        if ( kvs::OpenGL::Boolean( GL_LIGHT_MODEL_TWO_SIDE ) == GL_TRUE )
        {
            frag.define("ENABLE_TWO_SIDE_LIGHTING");
        }
    }
    m_shader_program.build( vert, frag );
    m_shader_program.bind();
    m_shader_program.setUniform( "shading.Ka", shader().Ka );
    m_shader_program.setUniform( "shading.Kd", shader().Kd );
    m_shader_program.setUniform( "shading.Ks", shader().Ks );
    m_shader_program.setUniform( "shading.S",  shader().S );
    m_shader_program.unbind();
}

/*===========================================================================*/
/**
 *  @brief  Create buffer objects.
 *  @param  polygon [in] pointer to the polygon object
 */
/*===========================================================================*/
void StochasticPolygonRenderer::Engine::create_buffer_object( const kvs::PolygonObject* polygon )
{
    if ( polygon->polygonType() != kvs::PolygonObject::Triangle )
    {
        kvsMessageError("Not supported polygon type.");
        return;
    }

    if ( polygon->colors().size() != 3 && polygon->colorType() == kvs::PolygonObject::PolygonColor )
    {
        kvsMessageError("Not supported polygon color type.");
        return;
    }

    const size_t nvertices = polygon->numberOfVertices();
    kvs::ValueArray<kvs::UInt16> indices( nvertices * 2 );
    for ( size_t i = 0; i < nvertices; i++ )
    {
        const unsigned int count = i * 12347;
        indices[ 2 * i + 0 ] = static_cast<kvs::UInt16>( ( count ) % randomTextureSize() );
        indices[ 2 * i + 1 ] = static_cast<kvs::UInt16>( ( count / randomTextureSize() ) % randomTextureSize() );
    }
    kvs::ValueArray<kvs::Real32> coords = polygon->coords();
    kvs::ValueArray<kvs::UInt8> colors = ::VertexColors( polygon );
    kvs::ValueArray<kvs::Real32> normals = ::VertexNormals( polygon );

    const size_t index_size = indices.byteSize();
    const size_t coord_size = coords.byteSize();
    const size_t color_size = colors.byteSize();
    const size_t normal_size = normals.byteSize();
    const size_t byte_size = index_size + coord_size + color_size + normal_size;

    m_vbo.create( byte_size );
    m_vbo.bind();
    m_vbo.load( index_size, indices.data(), 0 );
    m_vbo.load( coord_size, coords.data(), index_size );
    m_vbo.load( color_size, colors.data(), index_size + coord_size );
    if ( normal_size > 0 )
    {
        m_vbo.load( normal_size, normals.data(), index_size + coord_size + color_size );
    }
    m_vbo.unbind();

    if ( m_has_connection )
    {
        const size_t connection_size = polygon->connections().byteSize();
        m_ibo.create( connection_size );
        m_ibo.bind();
        m_ibo.load( connection_size, polygon->connections().data(), 0 );
        m_ibo.unbind();
    }
}

} // end of namespace kvs
