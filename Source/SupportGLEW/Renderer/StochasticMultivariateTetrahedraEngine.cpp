/*****************************************************************************/
/**
 *  @file   StochasticMultivariateTetrahedraEngine.cpp
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
#include "StochasticMultivariateTetrahedraEngine.h"
#include "ProjectedTetrahedraTable.h"
#include <kvs/TetrahedralCell>
#include <kvs/Math>
#if defined ( KVS_GLEW_STOCHASTIC_MULTIVARIATE_TETRAHEDRA_ENGINE__EMBEDDED_SHADER )
#include "StochasticRenderingEngine/Shader.h"
#endif


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultivariateTetrahedraEngine class.
 */
/*===========================================================================*/
StochasticMultivariateTetrahedraEngine::StochasticMultivariateTetrahedraEngine( void )
{
    this->initialize();
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultivariateTetrahedraEngine class.
 *  @param  volume [in] pointer to volume data
 *  @param  nsteps [in] number of time steps
 */
/*===========================================================================*/
StochasticMultivariateTetrahedraEngine::StochasticMultivariateTetrahedraEngine(
    const kvs::UnstructuredVolumeObject* volume,
    const size_t nsteps )
{
    this->initialize();
    this->attachObject( volume );
    this->setNSteps( nsteps );
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::initialize( void )
{
    BaseClass::initialize();

    m_table2.setTableSize( 128, 128 );

    m_show_flag1 = true;
    m_show_flag2 = true;
}

/*===========================================================================*/
/**
 *  @brief  Sets a transfer function.
 *  @param  tfunc [in] transfer function
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index )
{
    if ( index == 0 ) BaseClass::setTransferFunction( tfunc );
    else if ( index == 1 )
    {
        m_tfunc2 = tfunc;

        if ( m_table2.isDownloaded() )
        {
            m_table2.release();
        }
    }
}

/*===========================================================================*/
/**
 *  @brief  Returns the transfer function.
 */
/*===========================================================================*/
const kvs::TransferFunction& StochasticMultivariateTetrahedraEngine::transferFunction( const size_t index ) const
{
    return index == 0 ? BaseClass::transferFunction() : m_tfunc2;
}

/*===========================================================================*/
/**
 *  @brief  Returns the transfer function withtout 'const'.
 */
/*===========================================================================*/
kvs::TransferFunction& StochasticMultivariateTetrahedraEngine::transferFunction( const size_t index )
{
    return index == 0 ? BaseClass::transferFunction() : m_tfunc2;
}

const bool StochasticMultivariateTetrahedraEngine::isShown( const size_t index ) const
{
    return index == 0 ? m_show_flag1 : m_show_flag2;
}

void StochasticMultivariateTetrahedraEngine::show( const size_t index )
{
    if ( index == 0 ) m_show_flag1 = true;
    else if ( index == 1 ) m_show_flag2 = true;
}

void StochasticMultivariateTetrahedraEngine::hide( const size_t index )
{
    if ( index == 0 ) m_show_flag1 = false;
    else if ( index == 1 ) m_show_flag2 = false;
}

/*===========================================================================*/
/**
 *  @brief  Returns the rendering engine type.
 *  @return rendering engine type
 */
/*===========================================================================*/
const StochasticRenderingEngine::EngineType StochasticMultivariateTetrahedraEngine::engineType( void ) const
{
    return( BaseClass::MultivariateTetrahedra );
}

/*===========================================================================*/
/**
 *  @brief  Attaches volume object.
 *  @param  object [in] pointer to volume object
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::attachObject( const kvs::ObjectBase* object )
{
    const kvs::UnstructuredVolumeObject* volume = kvs::UnstructuredVolumeObject::DownCast( object );

    if ( volume->cellType() != kvs::UnstructuredVolumeObject::Tetrahedra )
    {
        kvsMessageError( "Cell type of this volume is not tetrahedral cell." );
        return;
    }

    if ( volume->veclen() != 2 )
    {
        kvsMessageError( "Veclen of this volume is not 2." );
        return;
    }

    m_ref_volume = volume;

    BaseClass::enable_updating_vbo();
}

/*===========================================================================*/
/**
 *  @brief  Creates the pre-integration table.
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::create_preintegration_table( void )
{
    BaseClass::create_preintegration_table();

    m_table2.setTransferFunction( m_tfunc2, 0.0f, 1.0f );
    m_table2.create( m_edge_size );
    m_table2.download();
}

/*===========================================================================*/
/**
 *  @brief  Creates the vertex buffer object from the volume data.
 */
/*===========================================================================*/
template <typename T>
void StochasticMultivariateTetrahedraEngine::create_vertexbuffer_from_volume( void )
{
    if ( m_volume ) delete m_volume;
    m_volume = new Volume();

    const size_t nvertices = m_ref_volume->numberOfNodes();
    const size_t ncells = m_ref_volume->numberOfCells();
    const size_t veclen = m_ref_volume->veclen();

    m_volume->create( m_nsteps, nvertices, ncells, veclen );

    const kvs::Real32* src_coord   = m_ref_volume->coords().data();
    const kvs::UInt32* src_connect = m_ref_volume->connections().data();
    const T* src_value = static_cast<const T*>( m_ref_volume->values().data() );

    kvs::Real64 min_value[2] = { 0.0, 0.0 };
    kvs::Real64 max_value[2] = { 0.0, 0.0 };
    kvs::Real64 normalize_factor[2] = { 0.0, 0.0 };
    for ( size_t i = 0; i < nvertices; i++ )
    {
        for ( size_t j = 0; j < 2; j++ )
        {
            if ( i == 0 )
            {
                min_value[j] = static_cast<kvs::Real64>( src_value[j] );
                max_value[j] = static_cast<kvs::Real64>( src_value[j] );
            }
            else
            {
                if ( min_value[j] > src_value[ i * 2 + j ] ) min_value[j] = src_value[ i * 2 + j ];
                if ( max_value[j] < src_value[ i * 2 + j ] ) max_value[j] = src_value[ i * 2 + j ];
            }
        }
    }

    for ( size_t j = 0; j < 2; j++ )
    {
        if ( max_value[j] == min_value[j] ) normalize_factor[j] = 1.0;
        else normalize_factor[j] = 1.0 / ( max_value[j] - min_value[j] );
    }

    IndexType*   dst_indices     = m_volume->indices();
    CoordType*   dst_coords      = m_volume->coords();
    ValueType*   dst_values      = m_volume->values();
    NormalType*  dst_normals     = m_volume->normals();
    ConnectType* dst_connections = m_volume->connections();

    const size_t random_texture_size = m_random_texture.width();

    for ( size_t i = 0; i < nvertices; i++ )
    {
        *(dst_coords)++ = src_coord[ i * 3     ];
        *(dst_coords)++ = src_coord[ i * 3 + 1 ];
        *(dst_coords)++ = src_coord[ i * 3 + 2 ];

        unsigned int index = i * 12347;
        *(dst_indices)++ = static_cast<IndexType>( index % random_texture_size );
        *(dst_indices)++ = static_cast<IndexType>( ( index / random_texture_size ) % random_texture_size );
    }

    for ( size_t step = 0; step < m_nsteps; step++ )
    {
        for ( size_t i = 0; i < nvertices; i++ )
        {
            for ( size_t j = 0; j < 2; j++ )
            {
                ValueType value = static_cast<ValueType>( *src_value++ );
                *(dst_values)++ = static_cast<ValueType>( ( value - min_value[j] ) * normalize_factor[j] );
            }
        }
    }

    for ( size_t i = 0; i < ncells; i++ )
    {
        *(dst_connections)++ = src_connect[ i * 4     ];
        *(dst_connections)++ = src_connect[ i * 4 + 1 ];
        *(dst_connections)++ = src_connect[ i * 4 + 2 ];
        *(dst_connections)++ = src_connect[ i * 4 + 3 ];
    }

    kvs::TetrahedralCell<T> cell( m_ref_volume );
    kvs::ValueArray<int> counter( nvertices );
    kvs::ValueArray<float> normals( 3 * nvertices );
    counter.fill( 0 );
    normals.fill( 0 );
    for ( size_t i = 0; i < ncells; i++ )
    {
        cell.bindCell( i );

        const kvs::Vector3f g = - cell.gradient();
        const kvs::UInt32 id0 = m_ref_volume->connections().at( 4 * i );
        const kvs::UInt32 id1 = m_ref_volume->connections().at( 4 * i + 1 );
        const kvs::UInt32 id2 = m_ref_volume->connections().at( 4 * i + 2 );
        const kvs::UInt32 id3 = m_ref_volume->connections().at( 4 * i + 3 );

        counter[id0]++;
        counter[id1]++;
        counter[id2]++;
        counter[id3]++;

        normals[ 3 * id0 + 0 ] += g.x();
        normals[ 3 * id0 + 1 ] += g.y();
        normals[ 3 * id0 + 2 ] += g.z();

        normals[ 3 * id1 + 0 ] += g.x();
        normals[ 3 * id1 + 1 ] += g.y();
        normals[ 3 * id1 + 2 ] += g.z();

        normals[ 3 * id2 + 0 ] += g.x();
        normals[ 3 * id2 + 1 ] += g.y();
        normals[ 3 * id2 + 2 ] += g.z();

        normals[ 3 * id3 + 0 ] += g.x();
        normals[ 3 * id3 + 1 ] += g.y();
        normals[ 3 * id3 + 2 ] += g.z();
    }

    for ( size_t i = 0; i < nvertices; i++ )
    {
        const kvs::Vector3f v( normals.data() + i * 3 );
        const kvs::Vector3f n = ( v / (float)counter[i] ).normalized() * 127.0f;
        *(dst_normals)++ = static_cast<NormalType>(n[0]);
        *(dst_normals)++ = static_cast<NormalType>(n[1]);
        *(dst_normals)++ = static_cast<NormalType>(n[2]);
    }
}

/*===========================================================================*/
/**
 *  @brief  Sets parameters to the shaders.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::setup_shader( const float modelview_matrix[16] )
{
    int scramble_count = m_repetition_count * 12347;
    size_t random_texture_size = m_random_texture.width();
    float rp_x = ( scramble_count                       ) % random_texture_size;
    float rp_y = ( scramble_count / random_texture_size ) % random_texture_size;

    const GLfloat random_texture_size_inv = 1.0f / random_texture_size;

    const GLfloat screen_scale_x = m_width * 0.5f;
    const GLfloat screen_scale_y = m_height * 0.5f;

    m_shader_program.setUniformValuef( "random_texture_size_inv", random_texture_size_inv );
    m_shader_program.setUniformValuef( "random_offset", rp_x, rp_y );

    m_shader_program.setUniformValuef( "screen_scale", screen_scale_x, screen_scale_y );
    m_shader_program.setUniformValuef( "screen_scale_inv", 1.0f / m_width, 1.0f / m_height );

    m_shader_program.setUniformValuef( "preintegration_scale_offset",
        1.0 - 1.0 / m_table.sizeDepth() / m_edge_size,
        1.0 / ( 2.0 * m_table.sizeDepth() ) );

    int start_volume = 0;
    int end_volume = 2;
    if ( !m_show_flag1 ) start_volume++;
    if ( !m_show_flag2 ) end_volume--;

    m_shader_program.setUniformValuei( "start_volume", start_volume );
    m_shader_program.setUniformValuei( "end_volume", end_volume );

    m_shader_program.setUniformValuei( "preintegration_texture0", 0 );
    m_shader_program.setUniformValuei( "preintegration_texture1", 1 );
    m_shader_program.setUniformValuei( "random_texture", 2 );
    m_shader_program.setUniformValuei( "decomposion_texture", 3 );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the shaders.
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::initialize_shader( void )
{
#if defined( KVS_GLEW_STOCHASTIC_MULTIVARIATE_TETRAHEDRA_ENGINE__EMBEDDED_SHADER )
    const std::string vert_code = kvs::glew::glsl::StochasticRenderingEngine::Vertex::multivariate_tetrahedra;
    const std::string geom_code = kvs::glew::glsl::StochasticRenderingEngine::Geometry::multivariate_tetrahedra;
    const std::string frag_code = kvs::glew::glsl::StochasticRenderingEngine::Fragment::multivariate_tetrahedra;
#else
    const std::string vert_code = "StochasticRenderingEngine/multivariate_tetrahedra.vert";
    const std::string geom_code = "StochasticRenderingEngine/multivariate_tetrahedra.geom";
    const std::string frag_code = "StochasticRenderingEngine/multivariate_tetrahedra.frag";
#endif

    kvs::glew::ShaderSource vert( vert_code );
    kvs::glew::ShaderSource geom( geom_code );
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

    this->create_shaders( m_shader_program, vert, geom, frag );
    m_loc_identifier = m_shader_program.attributeLocation( "identifier" );
    m_loc_values = m_shader_program.attributeLocation( "value" );

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

    // Inititlize the textures.
    this->initialize_decomposition_texture();
    this->create_preintegration_table();
}

/*===========================================================================*/
/**
 *  @brief  Creates the vertex and index buffer objects.
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::create_vertex_buffer( void )
{
    // Extract surfaces.
    const std::type_info& type = m_ref_volume->values().typeInfo()->type();
    if (      type == typeid( kvs::Int8   ) ) this->create_vertexbuffer_from_volume<kvs::Int8>();
    else if ( type == typeid( kvs::Int16  ) ) this->create_vertexbuffer_from_volume<kvs::Int16>();
    else if ( type == typeid( kvs::Int32  ) ) this->create_vertexbuffer_from_volume<kvs::Int32>();
    else if ( type == typeid( kvs::Int64  ) ) this->create_vertexbuffer_from_volume<kvs::Int64>();
    else if ( type == typeid( kvs::UInt8  ) ) this->create_vertexbuffer_from_volume<kvs::UInt8>();
    else if ( type == typeid( kvs::UInt16 ) ) this->create_vertexbuffer_from_volume<kvs::UInt16>();
    else if ( type == typeid( kvs::UInt32 ) ) this->create_vertexbuffer_from_volume<kvs::UInt32>();
    else if ( type == typeid( kvs::UInt64 ) ) this->create_vertexbuffer_from_volume<kvs::UInt64>();
    else if ( type == typeid( kvs::Real32 ) ) this->create_vertexbuffer_from_volume<kvs::Real32>();
    else if ( type == typeid( kvs::Real64 ) ) this->create_vertexbuffer_from_volume<kvs::Real64>();
    else
    {
        kvsMessageError( "Unsupported data type '%s'.", m_ref_volume->values().typeInfo()->typeName() );
    }

    if ( m_renderer ) delete m_renderer;
    m_renderer = new Renderer();

    m_vbo.release();
    m_ibo.release();

    m_vbo.create( m_volume->byteSizeOfVertex() );
    m_ibo.create( m_volume->byteSizeOfCell() );
    m_renderer->set( m_volume, m_nsteps, m_volume->nvertices(), m_volume->ncells(), m_loc_identifier, m_loc_values );
    m_renderer->download( m_vbo, m_ibo );
}

/*===========================================================================*/
/**
 *  @brief  Draws the volume data stored in the vertex and index buffer objects.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticMultivariateTetrahedraEngine::draw_vertex_buffer( const float modelview_matrix[16] )
{
    if ( !m_table.isTexture() || !m_table2.isTexture() )
    {
        this->create_preintegration_table();
    }

    if ( BaseClass::isEnabledShading() ) glEnable( GL_LIGHTING );
    else                                 glDisable( GL_LIGHTING );

    m_vbo.bind();
    m_ibo.bind();

    glActiveTexture(GL_TEXTURE0);     m_table.bind();                   glEnable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE1);     m_table2.bind();                  glEnable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE2);     m_random_texture.bind();          glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE3);     m_decomposition_texture.bind();   glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);

    m_shader_program.bind();

    this->setup_shader( modelview_matrix );
    m_renderer->draw( m_step );

    m_shader_program.unbind();

    glActiveTexture(GL_TEXTURE3);    m_decomposition_texture.unbind();  glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE2);    m_random_texture.unbind();         glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);    m_table2.unbind();                 glDisable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE0);    m_table.unbind();                  glDisable(GL_TEXTURE_3D);

    m_repetition_count++;
}

} // end of namespace glew

} // end of namespace kvs
