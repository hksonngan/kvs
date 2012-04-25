/*****************************************************************************/
/**
 *  @file   StochasticPointEngine.cpp
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
#include "StochasticPointEngine.h"
#include <kvs/CellByCellParticleGenerator>
#if defined ( KVS_GLEW_STOCHASTIC_POINT_ENGINE__EMBEDDED_SHADER )
#include "StochasticRenderingEngine/Shader.h"
#endif


namespace kvs
{

namespace glew
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPointEngine::Particles class.
 */
/*===========================================================================*/
StochasticPointEngine::Particles::Particles( void ):
    m_nvertices( 0 ),
    m_indices( NULL ),
    m_coords( NULL ),
    m_normals( NULL ),
    m_colors( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destroys the StochasticPointEngine::Particles class.
 */
/*===========================================================================*/
StochasticPointEngine::Particles::~Particles( void )
{
    this->release();
}

/*===========================================================================*/
/**
 *  @brief  Releases the particles.
 */
/*===========================================================================*/
void StochasticPointEngine::Particles::release( void )
{
    if ( m_indices ) { delete[] m_indices; m_indices = NULL; }
    if ( m_coords )  { delete[] m_coords;  m_coords  = NULL; }
    if ( m_normals ) { delete[] m_normals; m_normals = NULL; }
    if ( m_colors )  { delete[] m_colors;  m_colors  = NULL; }
}

/*===========================================================================*/
/**
 *  @brief  Creates the particles region.
 *  @param  nvertices [in] number of vertices
 *  @param  has_normal [in] true if the particle has a normal vector
 */
/*===========================================================================*/
void StochasticPointEngine::Particles::create(
    const size_t nvertices,
    const bool has_normal )
{
    this->release();

    m_nvertices = nvertices;
    m_coords = new StochasticPointEngine::CoordType [ nvertices * 3 ];
    m_colors = new StochasticPointEngine::ColorType [ nvertices * 3 ];
    m_indices = new StochasticPointEngine::IndexType [ nvertices * 2 ];
    if ( has_normal ) m_normals = new StochasticPointEngine::NormalType [ nvertices * 3 ];
}

/*===========================================================================*/
/**
 *  @brief  Returns status whether or not the particle has a normal vector.
 *  @return true if the particle has a normal vector
 */
/*===========================================================================*/
const bool StochasticPointEngine::Particles::hasNormal( void ) const
{
    return( m_normals != NULL );
}

/*===========================================================================*/
/**
 *  @brief  Returns the number of the vertices (particles).
 *  @return number of the vertices
 */
/*===========================================================================*/
const size_t StochasticPointEngine::Particles::nvertices( void ) const
{
    return( m_nvertices );
}

/*===========================================================================*/
/**
 *  @brief  Returns data size per a vertex (particle).
 *  @return data size per a vertex in bytes
 */
/*===========================================================================*/
const size_t StochasticPointEngine::Particles::byteSizePerVertex( void ) const
{
    const size_t index_size  = sizeof( StochasticPointEngine::IndexType ) * 2;
    const size_t coord_size  = sizeof( StochasticPointEngine::CoordType ) * 3;
    const size_t normal_size = this->hasNormal() ? sizeof( StochasticPointEngine::NormalType ) * 3 : 0;
    const size_t color_size  = sizeof( StochasticPointEngine::ColorType ) * 3;
    return( index_size + coord_size + normal_size + color_size );
}

/*===========================================================================*/
/**
 *  @brief  Returns data size of the all vertices (particles).
 *  @return data size of the all vertices in bytes.
 */
/*===========================================================================*/
const size_t StochasticPointEngine::Particles::byteSize( void ) const
{
    return( this->byteSizePerVertex() * m_nvertices );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the index array.
 *  @return pointer to the index array
 */
/*===========================================================================*/
const StochasticPointEngine::IndexType* StochasticPointEngine::Particles::indices( void ) const
{
    return( m_indices );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the index array without 'const'.
 *  @return pointer to the index array
 */
/*===========================================================================*/
StochasticPointEngine::IndexType* StochasticPointEngine::Particles::indices( void )
{
    return( m_indices );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the coordinate array.
 *  @return pointer to the coordinate array
 */
/*===========================================================================*/
const StochasticPointEngine::CoordType* StochasticPointEngine::Particles::coords( void ) const
{
    return( m_coords );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the coordinate array without 'const'.
 *  @return pointer to the coordinate array
 */
/*===========================================================================*/
StochasticPointEngine::CoordType* StochasticPointEngine::Particles::coords( void )
{
    return( m_coords );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the normal vector array.
 *  @return pointer to the normal vector array
 */
/*===========================================================================*/
const StochasticPointEngine::NormalType* StochasticPointEngine::Particles::normals( void ) const
{
    return( m_normals );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the normal vector array without 'const'.
 *  @return pointer to the normal vector array
 */
/*===========================================================================*/
StochasticPointEngine::NormalType* StochasticPointEngine::Particles::normals( void )
{
    return( m_normals );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the color value array.
 *  @return pointer to the color value array
 */
/*===========================================================================*/
const StochasticPointEngine::ColorType* StochasticPointEngine::Particles::colors( void ) const
{
    return( m_colors );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the color value array withou 'const'.
 *  @return pointer to the color value array
 */
/*===========================================================================*/
StochasticPointEngine::ColorType* StochasticPointEngine::Particles::colors( void )
{
    return( m_colors );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPointEngine::Renderer class.
 */
/*===========================================================================*/
StochasticPointEngine::Renderer::Renderer( void ):
    m_particles(NULL),
    m_start(0),
    m_count(0),
    m_off_index(0),
    m_off_coord(0),
    m_off_normal(0),
    m_off_color(0),
    m_loc_identifier(0)
{
}

/*===========================================================================*/
/**
 *  @brief  Sets particles to the renderer.
 *  @param  particles [in] pointer to the particles
 *  @param  start [in] start particle number
 *  @param  count [in] number of particles
 *  @param  loc_identifier [in] location identifier
 */
/*===========================================================================*/
void StochasticPointEngine::Renderer::set(
    const StochasticPointEngine::Particles* particles,
    const size_t start,
    const size_t count,
    const size_t loc_identifier )
{
    m_particles = particles;

    m_start = start; // start vertex number

    size_t end = start + count;
    if ( end > m_particles->nvertices() )
    {
        end = m_particles->nvertices(); // end vertex number + 1
    }

    m_count = end - start;  // number of vertices

    m_loc_identifier = loc_identifier;
}

/*===========================================================================*/
/**
 *  @brief  Downloads the particles to the VBO.
 *  @param  vbo [in/out] vertex buffer object
 *  @return true if the downloading is done successfully
 */
/*===========================================================================*/
const bool StochasticPointEngine::Renderer::download( kvs::glew::VertexBufferObject& vbo )
{
    if ( m_particles == NULL ) return( false );

    const bool has_normal = m_particles->hasNormal();

    const size_t start = m_start;
    size_t end = m_start + m_count;
    if ( end > m_particles->nvertices() ) end = m_particles->nvertices(); // end vertex number + 1

    const size_t size = end - start;  // number of vertices
    const size_t size_i = sizeof(StochasticPointEngine::IndexType) * 2 * size;
    const size_t size_v = sizeof(StochasticPointEngine::CoordType) * 3 * size;
    const size_t size_n = has_normal ? sizeof(StochasticPointEngine::NormalType) * 3 * size : 0;
    const size_t size_c = sizeof(StochasticPointEngine::ColorType) * 3 * size;
    const size_t off_i = 0;
    const size_t off_v = off_i + size_i;
    const size_t off_n = off_v + size_v;
    const size_t off_c = off_n + size_n;

    const StochasticPointEngine::IndexType*  ptr_i = m_particles->indices() + start * 2;
    const StochasticPointEngine::CoordType*  ptr_v = m_particles->coords() + start * 3;
    const StochasticPointEngine::NormalType* ptr_n = has_normal ? m_particles->normals() + start * 3 : NULL;
    const StochasticPointEngine::ColorType*  ptr_c = m_particles->colors() + start * 3;

    vbo.download( size_i, ptr_i, off_i );
    vbo.download( size_v, ptr_v, off_v );
    if ( has_normal ) vbo.download( size_n, ptr_n, off_n );
    vbo.download( size_c, ptr_c, off_c );

    GLenum error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        kvsMessageError( "Vertex Buffer Object download failed: %s(%d).", gluErrorString( error ), error );
        return false;
    }

    m_off_index  = off_i;
    m_off_coord  = off_v;
    m_off_normal = off_n;
    m_off_color  = off_c;

    return( true );
}

/*===========================================================================*/
/**
 *  @brief  Draws the particles.
 */
/*===========================================================================*/
void StochasticPointEngine::Renderer::draw( void ) const
{
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, (char*)(m_off_coord) );

    if ( m_particles->hasNormal() )
    {
        glEnableClientState( GL_NORMAL_ARRAY );
        glNormalPointer( GL_BYTE, 0, (char*)(m_off_normal) );
    }

    glEnableClientState( GL_COLOR_ARRAY );
    glColorPointer( 3, GL_UNSIGNED_BYTE, 0, (char*)(m_off_color) );

    glEnableVertexAttribArray( m_loc_identifier );
    glVertexAttribPointer( m_loc_identifier, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, (char*)(m_off_index) );

    glDrawArrays( GL_POINTS, 0, m_count );

    glDisableClientState( GL_VERTEX_ARRAY );
    if ( m_particles->hasNormal() ) glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableVertexAttribArray( m_loc_identifier );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPointEngine class.
 */
/*===========================================================================*/
StochasticPointEngine::StochasticPointEngine( void ) :
    m_ref_particle( NULL )
{
    this->initialize();

    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticPointEngine class.
 *  @param  point [in] pointer to the point object
 *  @param  repetition_level [in] repetition level
 */
/*===========================================================================*/
StochasticPointEngine::StochasticPointEngine(
    const kvs::PointObject* point,
    const size_t repetition_level ) :
    m_ref_particle( NULL )
{
    this->initialize();
    this->attachObject( point );
    this->setRepetitionLevel( repetition_level );

    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Destroys the StochasticPointEngine class.
 */
/*===========================================================================*/
StochasticPointEngine::~StochasticPointEngine( void )
{
    delete [] m_vbo;
    delete [] m_particles;
    delete [] m_renderer;
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticPointEngine::initialize( void )
{
    m_vbo = NULL;
    m_particles = NULL;
    m_renderer = NULL;

    m_zooming_factor = 1.0f;
    m_circle_threshold = 3;
    m_point_size = 1.0f;

    m_repetition_level = 1;
}

/*===========================================================================*/
/**
 *  @brief  Sets a point size.
 *  @param  point_size [in] point size
 */
/*===========================================================================*/
void StochasticPointEngine::setPointSize( const float point_size )
{
    m_point_size = point_size;
}

/*===========================================================================*/
/**
 *  @brief  Sets a repetition level.
 *  @param  repetition_level [in] repetition level
 */
/*===========================================================================*/
void StochasticPointEngine::setRepetitionLevel( const size_t repetition_level )
{
    m_repetition_level = repetition_level;
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the point object.
 *  @return pointer to the point object
 */
/*===========================================================================*/
const kvs::ObjectBase* StochasticPointEngine::object( void ) const
{
    return( m_ref_particle );
}

/*===========================================================================*/
/**
 *  @brief  Returns the rendering engine type.
 *  @return rendering engine type
 */
/*===========================================================================*/
const StochasticRenderingEngine::EngineType StochasticPointEngine::engineType( void ) const
{
    return( BaseClass::Point );
}

/*===========================================================================*/
/**
 *  @brief  Attaches a point object.
 *  @param  object [in] pointer to a point object
 */
/*===========================================================================*/
void StochasticPointEngine::attachObject( const kvs::ObjectBase* object )
{
    const kvs::PointObject* point = kvs::PointObject::DownCast( object );

    m_ref_particle = point;

    if ( m_ref_particle->normals().pointer() == NULL ||
         m_ref_particle->nnormals() == 0 )
    {
        BaseClass::disableShading();
    }

    BaseClass::enable_updating_vbo();
}

/*===========================================================================*/
/**
 *  @brief  Creates vertex buffer from the attached point object.
 */
/*===========================================================================*/
void StochasticPointEngine::create_vertexbuffer_from_point( void )
{
    if ( m_particles ) delete [] m_particles;
    m_particles = new Particles[ m_repetition_level ];

    const size_t total_vertices = m_ref_particle->nvertices();

    const bool has_normal = BaseClass::isEnabledShading();

    const kvs::Real32* src_coord   = m_ref_particle->coords().pointer();
    const kvs::UInt8*  src_color   = m_ref_particle->colors().pointer();
    const kvs::Real32* src_normal  = m_ref_particle->normals().pointer();

    // Distination pointers.
    static const size_t max_repetition = 1024;
    IndexType*  dst_indices[ max_repetition ];
    ColorType*  dst_colors[ max_repetition ];
    CoordType*  dst_coords[ max_repetition ];
    NormalType* dst_normals[ max_repetition ];
    if ( m_repetition_level >= max_repetition )
    {
        kvsMessageError( "Repetition level is too large.");
    }

    // Allocate memory for each vertex array.
    size_t memorysize = 0;
    const size_t each_vertices = ( total_vertices - 1 ) / m_repetition_level + 1;
    const size_t overflow = each_vertices * m_repetition_level - total_vertices;
    for ( size_t rp = 0; rp < m_repetition_level; rp++ )
    {
        // first  [m_repetition_level - overflow] arrays have [each_vertices    ] vertices.
        // latter [                 overflow] arrays have [each_vertices - 1] vertices.
        size_t size = ( rp < m_repetition_level - overflow ) ?  each_vertices : each_vertices - 1;
        try
        {
            m_particles[rp].create( size, BaseClass::isEnabledShading() );
        }
        catch (...)
        {
            kvsMessageError( "Cannot allocate vertex memory.");
        }
        dst_coords [rp] = m_particles[rp].coords();
        dst_normals[rp] = m_particles[rp].normals();
        dst_colors [rp] = m_particles[rp].colors();
        dst_indices[rp] = m_particles[rp].indices();
        memorysize += m_particles[rp].byteSize();
    }

    const size_t random_texture_size = m_random_texture.width();
    // Distribute vertex into [m_repetition_level] arrays
    for ( size_t i = 0, rp = 0; i < total_vertices; i++ )
    {
        *(dst_coords[rp])++ = *src_coord++;
        *(dst_coords[rp])++ = *src_coord++;
        *(dst_coords[rp])++ = *src_coord++;

        *(dst_colors[rp])++ = *src_color++;
        *(dst_colors[rp])++ = *src_color++;
        *(dst_colors[rp])++ = *src_color++;

        if ( has_normal )
        {
            kvs::Vector3f v( src_normal );
            src_normal += 3;
            kvs::Vector3f n = v.normalizedVector() * 127.0f;
            *(dst_normals[rp])++ = static_cast<NormalType>(n[0]);
            *(dst_normals[rp])++ = static_cast<NormalType>(n[1]);
            *(dst_normals[rp])++ = static_cast<NormalType>(n[2]);
        }

        unsigned int index = i * 12347;
        *(dst_indices[rp])++ = static_cast<IndexType>( index % random_texture_size );
        *(dst_indices[rp])++ = static_cast<IndexType>( ( index / random_texture_size ) % random_texture_size );
        if ( ++rp >= m_repetition_level ) rp = 0;
    }
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffer.
 */
/*===========================================================================*/
void StochasticPointEngine::clearEnsembleBuffer( void )
{
    m_repetition_count = 0;
}

/*===========================================================================*/
/**
 *  @brief  Calculates zooming factor.
 */
/*===========================================================================*/
void StochasticPointEngine::calculate_zooming_factor( void )
{
    const kvs::PointObject* point = m_ref_particle;
    kvs::Camera* camera = new kvs::Camera();
    camera->setWindowSize( m_width, m_height );

    // Calculate a transform matrix.
    GLdouble modelview[16];  ::GetModelviewMatrix( camera, point, &modelview );
    GLdouble projection[16]; ::GetProjectionMatrix( camera, &projection );
    GLint viewport[4];       ::GetViewport( camera, &viewport );

    // Calculate a depth of the center of gravity of the object.
    const float object_depth =
        kvs::CellByCellParticleGenerator::CalculateObjectDepth(
            point, modelview, projection, viewport );

    // Calculate suitable subpixel length.
    const float subpixel_length =
        kvs::CellByCellParticleGenerator::CalculateSubpixelLength(
            1, object_depth, modelview, projection, viewport );

    delete camera;

    m_zooming_factor = m_point_size * subpixel_length;
}

/*===========================================================================*/
/**
 *  @brief  Sets parameters to the shaders.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticPointEngine::setup_shader( const float modelview_matrix[16] )
{
    float projection_matrix[16]; glGetFloatv( GL_PROJECTION_MATRIX, projection_matrix );
    const float tan_inv = projection_matrix[5]; // (1,1)

    const float* mat = modelview_matrix;
    const float width = static_cast<float>( m_width );
    const float scale = sqrtf( mat[0] * mat[0] + mat[1] * mat[1] + mat[2] * mat[2] );

    int scramble_count = m_repetition_count * 12347;
    const size_t random_texture_size = m_random_texture.width();
    float rp_x = ( scramble_count                       ) % random_texture_size;
    float rp_y = ( scramble_count / random_texture_size ) % random_texture_size;

    const GLfloat densityFactor = m_zooming_factor * 0.5f * tan_inv * width * scale;
    const GLfloat random_texture_size_inv = 1.0f / random_texture_size;
    const GLint   circle_threshold = static_cast<GLint>( m_circle_threshold );
    const GLfloat screen_scale_x = m_width * 0.5f;
    const GLfloat screen_scale_y = m_height * 0.5f;

    m_shader_program.setUniformValuef( "densityFactor", densityFactor );
    m_shader_program.setUniformValuef( "random_texture_size_inv", random_texture_size_inv );
    m_shader_program.setUniformValuef( "random_offset", rp_x, rp_y );
    m_shader_program.setUniformValuei( "circle_threshold", circle_threshold );
    m_shader_program.setUniformValuef( "screen_scale", screen_scale_x, screen_scale_y );
    m_shader_program.setUniformValuei( "random_texture", 0 );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the shaders.
 */
/*===========================================================================*/
void StochasticPointEngine::initialize_shader( void )
{
#if defined( KVS_GLEW_STOCHASTIC_POINT_ENGINE__EMBEDDED_SHADER )
    const std::string vert_code = kvs::glew::glsl::StochasticRenderingEngine::Vertex::point;
    const std::string frag_code = kvs::glew::glsl::StochasticRenderingEngine::Fragment::point;
#else
    const std::string vert_code = "StochasticRenderingEngine/point.vert";
    const std::string frag_code = "StochasticRenderingEngine/point.frag";
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
void StochasticPointEngine::create_vertex_buffer( void )
{
    this->create_vertexbuffer_from_point();

    size_t memorysize = 0;
    for ( size_t rp = 0; rp < m_repetition_level; rp++ )
    {
        memorysize += m_particles[rp].byteSize();
    }

    delete [] m_renderer;
    delete [] m_vbo;

    m_renderer = new Renderer[ m_repetition_level ];
    m_vbo = new kvs::glew::VertexBufferObject[ m_repetition_level ];

    size_t memorymax = 0;
    for ( size_t rp = 0; rp < m_repetition_level; rp++ )
    {
        const size_t nvertices  = m_particles[rp].nvertices();
        const size_t copysize = nvertices;
        m_renderer[rp].set( &m_particles[rp], 0, copysize, m_loc_identifier );
        const size_t memorysize = m_particles[rp].byteSize();

        // if m_share_vbo is false, vertex buffer data is downloaded beforehand.
        m_vbo[rp].create( memorysize );
        m_renderer[rp].download( m_vbo[rp] );

        if ( memorymax < memorysize ) memorymax = memorysize;
    }
}

/*===========================================================================*/
/**
 *  @brief  Downloads the vertex dataset to the vertex buffer.
 */
/*===========================================================================*/
void StochasticPointEngine::download_vertex_buffer( void )
{
    for ( size_t i = 0; i < m_repetition_level; i++ )
    {
        m_vbo[i].bind();
        m_renderer[i].download( m_vbo[i] );
    }
}

/*===========================================================================*/
/**
 *  @brief  Draws the vertex buffer.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticPointEngine::draw_vertex_buffer( const float modelview_matrix[16] )
{
    m_vbo[ m_repetition_count ].bind();

    glActiveTexture( GL_TEXTURE0 ); m_random_texture.bind(); glEnable( GL_TEXTURE_2D );

    m_shader_program.bind();

    glEnable( GL_VERTEX_PROGRAM_POINT_SIZE );
    this->calculate_zooming_factor();
    this->setup_shader( modelview_matrix );
    m_renderer[ m_repetition_count ].draw();

    m_shader_program.unbind();

    glActiveTexture( GL_TEXTURE0 ); m_random_texture.unbind(); glDisable( GL_TEXTURE_2D );

    if ( ++m_repetition_count >= m_repetition_level ) m_repetition_count = 0;
}

} // end of namespace glew

} // end of namespace kvs
