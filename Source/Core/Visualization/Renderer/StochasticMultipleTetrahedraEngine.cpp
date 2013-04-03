/*****************************************************************************/
/**
 *  @file   StochasticMultipleTetrahedraEngine.cpp
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
#include "StochasticMultipleTetrahedraEngine.h"
#include "ProjectedTetrahedraTable.h"
#include <kvs/TetrahedralCell>
#include <kvs/ShaderSource>
#include <kvs/Math>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultipleTetrahedraEngine class.
 */
/*===========================================================================*/
StochasticMultipleTetrahedraEngine::StochasticMultipleTetrahedraEngine( void )
{
    this->initialize();
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticMultipleTetrahedraEngine class.
 *  @param  volume [in] pointer to volume data
 *  @param  nsteps [in] number of time steps
 */
/*===========================================================================*/
StochasticMultipleTetrahedraEngine::StochasticMultipleTetrahedraEngine(
    const kvs::UnstructuredVolumeObject* volume1,
    const kvs::UnstructuredVolumeObject* volume2 )
{
    this->initialize();
    this->attachObject( volume1, 0 );
    this->attachObject( volume2, 1 );
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraEngine::initialize( void )
{
    BaseClass::initialize();

    m_ref_volume2 = NULL;
    m_table2.setTableSize( 128, 128 );
}

/*===========================================================================*/
/**
 *  @brief  Sets a transfer function.
 *  @param  tfunc [in] transfer function
 */
/*===========================================================================*/
//void StochasticMultipleTetrahedraEngine::setTransferFunction( const kvs::TransferFunction& tfunc )
void StochasticMultipleTetrahedraEngine::setTransferFunction( const kvs::TransferFunction& tfunc, const size_t index )
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
//const kvs::TransferFunction& StochasticMultipleTetrahedraEngine::transferFunction( void ) const
const kvs::TransferFunction& StochasticMultipleTetrahedraEngine::transferFunction( const size_t index ) const
{
    return index == 0 ? BaseClass::transferFunction() : m_tfunc2;
}

/*===========================================================================*/
/**
 *  @brief  Returns the transfer function withtout 'const'.
 */
/*===========================================================================*/
//kvs::TransferFunction& StochasticMultipleTetrahedraEngine::transferFunction( void )
kvs::TransferFunction& StochasticMultipleTetrahedraEngine::transferFunction( const size_t index )
{
    return index == 0 ? BaseClass::transferFunction() : m_tfunc2;
}

void StochasticMultipleTetrahedraEngine::attachObjects( const kvs::ObjectBase* object1, const kvs::ObjectBase* object2 )
{
    this->attachObject( object1, 0 );
    this->attachObject( object2, 1 );
}

/*===========================================================================*/
/**
 *  @brief  Attaches volume object.
 *  @param  object [in] pointer to volume object
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraEngine::attachObject( const kvs::ObjectBase* object, const size_t index )
{
    if ( index == 0 ) BaseClass::attachObject( object );
    else if ( index == 1 )
    {
        const kvs::UnstructuredVolumeObject* volume = kvs::UnstructuredVolumeObject::DownCast( object );

        if ( volume->cellType() != kvs::UnstructuredVolumeObject::Tetrahedra )
        {
            kvsMessageError( "Cell type of this volume is not tetrahedral cell." );
            return;
        }

        m_ref_volume2 = volume;

        BaseClass::enable_updating_vbo();
    }
}

/*===========================================================================*/
/**
 *  @brief  Creates the pre-integration table.
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraEngine::create_preintegration_table( void )
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
void StochasticMultipleTetrahedraEngine::create_vertexbuffer_from_volume_of( const size_t index )
{
    const kvs::UnstructuredVolumeObject* ref_volume[2] = { m_ref_volume, m_ref_volume2 };

    const size_t nvertices = ref_volume[index]->numberOfNodes();
    const size_t ncells = ref_volume[index]->numberOfCells();
    const size_t veclen = ref_volume[index]->veclen(); // ADD

//    m_volume->create( m_nsteps, nvertices, ncells );
    m_volume[index].create( m_nsteps, nvertices, ncells, veclen );

    const kvs::Real32* src_coord   = ref_volume[index]->coords().data();
    const kvs::UInt32* src_connect = ref_volume[index]->connections().data();
    const T* src_value = static_cast<const T*>( ref_volume[index]->values().data() );

    if ( !ref_volume[index]->hasMinMaxValues() ) ref_volume[index]->updateMinMaxValues();
    const kvs::Real64 min_value = ref_volume[index]->minValue();
    const kvs::Real64 max_value = ref_volume[index]->maxValue();
    const kvs::Real64 normalize_factor = 1.0 / ( max_value - min_value );

    IndexType*   dst_indices     = m_volume[index].indices();
    CoordType*   dst_coords      = m_volume[index].coords();
    ValueType*   dst_values      = m_volume[index].values();
    NormalType*  dst_normals     = m_volume[index].normals();
    ConnectType* dst_connections = m_volume[index].connections();

    const size_t random_texture_size = m_random_texture.width();

    for ( size_t i = 0; i < nvertices; i++ )
    {
        *(dst_coords)++ = src_coord[ i * 3     ];
        *(dst_coords)++ = src_coord[ i * 3 + 1 ];
        *(dst_coords)++ = src_coord[ i * 3 + 2 ];

        unsigned int index = i * 12347;
        *(dst_indices)++ = static_cast<IndexType>( index % random_texture_size );
        *(dst_indices)++ = static_cast<IndexType>( ( index / random_texture_size ) % random_texture_size );

        ValueType value = static_cast<ValueType>( *src_value++ );
        *(dst_values)++ = static_cast<ValueType>( ( value - min_value ) * normalize_factor );
    }

    for ( size_t i = 0; i < ncells; i++ )
    {
        *(dst_connections)++ = src_connect[ i * 4     ];
        *(dst_connections)++ = src_connect[ i * 4 + 1 ];
        *(dst_connections)++ = src_connect[ i * 4 + 2 ];
        *(dst_connections)++ = src_connect[ i * 4 + 3 ];
    }

    kvs::TetrahedralCell<T> cell( ref_volume[index] );
    kvs::ValueArray<int> counter( nvertices );
    kvs::ValueArray<float> normals( 3 * nvertices );
    counter.fill( 0 );
    normals.fill( 0 );
    for ( size_t i = 0; i < ncells; i++ )
    {
        cell.bindCell( i );

        const kvs::Vector3f g = - cell.gradient();
        const kvs::UInt32 id0 = ref_volume[index]->connections().at( 4 * i );
        const kvs::UInt32 id1 = ref_volume[index]->connections().at( 4 * i + 1 );
        const kvs::UInt32 id2 = ref_volume[index]->connections().at( 4 * i + 2 );
        const kvs::UInt32 id3 = ref_volume[index]->connections().at( 4 * i + 3 );

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
void StochasticMultipleTetrahedraEngine::setup_shader_of( const size_t index )
{
    int scramble_count = m_repetition_count * 12347;
    size_t random_texture_size = m_random_texture.width();
    float rp_x = ( scramble_count                       ) % random_texture_size;
    float rp_y = ( scramble_count / random_texture_size ) % random_texture_size;

    const GLfloat random_texture_size_inv = 1.0f / random_texture_size;

    const GLfloat screen_scale_x = m_width * 0.5f;
    const GLfloat screen_scale_y = m_height * 0.5f;

    kvs::ProgramObject& shader_program = ( index == 0 ) ? m_shader_program : m_shader_program2;
    kvs::PreIntegrationTable& table = ( index == 0 ) ? m_table : m_table2;

    shader_program.setUniformValuef( "random_texture_size_inv", random_texture_size_inv );
    shader_program.setUniformValuef( "random_offset", rp_x, rp_y );

    shader_program.setUniformValuef( "screen_scale", screen_scale_x, screen_scale_y );
    shader_program.setUniformValuef( "screen_scale_inv", 1.0f / m_width, 1.0f / m_height );

    shader_program.setUniformValuef( "preintegration_scale_offset",
        1.0 - 1.0 / table.sizeDepth() / m_edge_size,
        1.0 / ( 2.0 * table.sizeDepth() ) );

    shader_program.setUniformValuei( "preintegration_texture0", 0 );
    shader_program.setUniformValuei( "preintegration_texture1", 1 );
    shader_program.setUniformValuei( "random_texture", 2 );
    shader_program.setUniformValuei( "decomposion_texture", 3 );
    shader_program.setUniformValuei( "depth_texture", 4 );
    shader_program.setUniformValuei( "extra_texture", 5 );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the shaders.
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraEngine::initialize_shader( void )
{
    // Inititlize the shaders.
    for ( size_t i = 0; i < 2; i++ ) { this->initialize_shader_of( i ); }

    // Inititlize the textures.
    this->initialize_decomposition_texture();
    this->create_preintegration_table();
}

void StochasticMultipleTetrahedraEngine::initialize_shader_of( const size_t index )
{
    const std::string vert_code = index == 0 ? "SR_multiple_tetrahedra1.vert" : "SR_multiple_tetrahedra2.vert";
    const std::string geom_code = index == 0 ? "SR_multiple_tetrahedra1.geom" : "SR_multiple_tetrahedra2.geom";
    const std::string frag_code = index == 0 ? "SR_multiple_tetrahedra1.frag" : "SR_multiple_tetrahedra2.frag";

    kvs::ShaderSource vert( vert_code );
    kvs::ShaderSource geom( geom_code );
    kvs::ShaderSource frag( frag_code );

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

    kvs::ProgramObject& shader_program = index == 0 ? m_shader_program : m_shader_program2;
    size_t& loc_identifier = index == 0 ? m_loc_identifier : m_loc_identifier2;
    size_t& loc_values = index == 0 ? m_loc_values : m_loc_values2;

    this->create_shaders( shader_program, vert, geom, frag );
    loc_identifier = shader_program.attributeLocation( "identifier" );
    loc_values = shader_program.attributeLocation( "value" );

    if ( BaseClass::isEnabledShading() )
    {
        shader_program.bind();
        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading:
        {
            const GLfloat Ka = ((kvs::Shader::Lambert*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::Lambert*)(BaseClass::m_shader))->Kd;
            shader_program.setUniformValuef( "shading.Ka", Ka );
            shader_program.setUniformValuef( "shading.Kd", Kd );
            break;
        }
        case kvs::Shader::PhongShading:
        {
            const GLfloat Ka = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Kd;
            const GLfloat Ks = ((kvs::Shader::Phong*)(BaseClass::m_shader))->Ks;
            const GLfloat S  = ((kvs::Shader::Phong*)(BaseClass::m_shader))->S;
            shader_program.setUniformValuef( "shading.Ka", Ka );
            shader_program.setUniformValuef( "shading.Kd", Kd );
            shader_program.setUniformValuef( "shading.Ks", Ks );
            shader_program.setUniformValuef( "shading.S",  S );
            break;
        }
        case kvs::Shader::BlinnPhongShading:
        {
            const GLfloat Ka = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Ka;
            const GLfloat Kd = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Kd;
            const GLfloat Ks = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->Ks;
            const GLfloat S  = ((kvs::Shader::BlinnPhong*)(BaseClass::m_shader))->S;
            shader_program.setUniformValuef( "shading.Ka", Ka );
            shader_program.setUniformValuef( "shading.Kd", Kd );
            shader_program.setUniformValuef( "shading.Ks", Ks );
            shader_program.setUniformValuef( "shading.S",  S );
            break;
        }
        default: /* NO SHADING */ break;
        }
        shader_program.unbind();
    }
}


/*===========================================================================*/
/**
 *  @brief  Creates the vertex and index buffer objects.
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraEngine::create_vertex_buffer( void )
{
    if ( m_volume ) delete [] m_volume;
    m_volume = new Volume[2];

    const kvs::UnstructuredVolumeObject* ref_volume[2] = { m_ref_volume, m_ref_volume2 };
    for ( size_t i = 0; i < 2; i++ )
    {
        // Extract surfaces.
        const std::type_info& type = ref_volume[i]->values().typeInfo()->type();
        if (      type == typeid( kvs::Int8   ) ) this->create_vertexbuffer_from_volume_of<kvs::Int8>(i);
        else if ( type == typeid( kvs::Int16  ) ) this->create_vertexbuffer_from_volume_of<kvs::Int16>(i);
        else if ( type == typeid( kvs::Int32  ) ) this->create_vertexbuffer_from_volume_of<kvs::Int32>(i);
        else if ( type == typeid( kvs::Int64  ) ) this->create_vertexbuffer_from_volume_of<kvs::Int64>(i);
        else if ( type == typeid( kvs::UInt8  ) ) this->create_vertexbuffer_from_volume_of<kvs::UInt8>(i);
        else if ( type == typeid( kvs::UInt16 ) ) this->create_vertexbuffer_from_volume_of<kvs::UInt16>(i);
        else if ( type == typeid( kvs::UInt32 ) ) this->create_vertexbuffer_from_volume_of<kvs::UInt32>(i);
        else if ( type == typeid( kvs::UInt64 ) ) this->create_vertexbuffer_from_volume_of<kvs::UInt64>(i);
        else if ( type == typeid( kvs::Real32 ) ) this->create_vertexbuffer_from_volume_of<kvs::Real32>(i);
        else if ( type == typeid( kvs::Real64 ) ) this->create_vertexbuffer_from_volume_of<kvs::Real64>(i);
        else
        {
            kvsMessageError( "Unsupported data type '%s'.", ref_volume[i]->values().typeInfo()->typeName() );
        }
    }

    if ( m_renderer ) delete [] m_renderer;
    m_renderer = new Renderer[2];

    m_vbo.release();
    m_ibo.release();

    m_vbo.create( m_volume[0].byteSizeOfVertex() );
    m_ibo.create( m_volume[0].byteSizeOfCell() );
    m_renderer[0].set( &m_volume[0], m_nsteps, m_volume[0].nvertices(), m_volume[0].ncells(), m_loc_identifier, m_loc_values );
    m_renderer[0].download( m_vbo, m_ibo );

    m_vbo2.release();
    m_ibo2.release();

    m_vbo2.create( m_volume[1].byteSizeOfVertex() );
    m_ibo2.create( m_volume[1].byteSizeOfCell() );
    m_renderer[1].set( &m_volume[1], m_nsteps, m_volume[1].nvertices(), m_volume[1].ncells(), m_loc_identifier2, m_loc_values2 );
    m_renderer[1].download( m_vbo2, m_ibo2 );
}

void StochasticMultipleTetrahedraEngine::download_vertex_buffer( void )
{
    BaseClass::download_vertex_buffer();

    m_vbo2.bind();
    m_ibo2.bind();
    m_renderer[1].download( m_vbo2, m_ibo2 );
}

/*===========================================================================*/
/**
 *  @brief  Draws the volume data stored in the vertex and index buffer objects.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticMultipleTetrahedraEngine::draw_vertex_buffer( const float modelview_matrix[16] )
{
    if ( !m_table.isTexture() || !m_table2.isTexture() )
    {
        this->create_preintegration_table();
    }

    if ( BaseClass::isEnabledShading() ) glEnable( GL_LIGHTING );
    else                                 glDisable( GL_LIGHTING );

    glActiveTexture(GL_TEXTURE0); m_table.bind(); glEnable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE1); m_table2.bind();
    glActiveTexture(GL_TEXTURE2); m_random_texture.bind(); glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE3); m_decomposition_texture.bind();
    glActiveTexture(GL_TEXTURE4); m_depth_texture.bind();
    glActiveTexture(GL_TEXTURE5); m_extra_texture.bind();
    glActiveTexture(GL_TEXTURE0);

    m_vbo.bind();
    m_ibo.bind();
    m_shader_program.bind();
    {
        this->setup_shader_of(0);
        m_renderer[0].draw( m_step );
    }
    m_shader_program.unbind();

    m_vbo2.bind();
    m_ibo2.bind();
    m_shader_program2.bind();
    {
        this->setup_shader_of(1);
        m_renderer[1].draw( m_step );
    }
    m_shader_program2.unbind();

    glActiveTexture(GL_TEXTURE5); m_extra_texture.unbind();
    glActiveTexture(GL_TEXTURE4); m_depth_texture.unbind();
    glActiveTexture(GL_TEXTURE3); m_decomposition_texture.unbind();
    glActiveTexture(GL_TEXTURE2); m_random_texture.unbind(); glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1); m_table2.unbind();
    glActiveTexture(GL_TEXTURE0); m_table.unbind(); glDisable(GL_TEXTURE_3D);

    m_repetition_count++;
}

void StochasticMultipleTetrahedraEngine::set_extra_texture( const kvs::Texture2D& extra_texture )
{
    m_extra_texture = extra_texture;
}

} // end of namespace kvs
