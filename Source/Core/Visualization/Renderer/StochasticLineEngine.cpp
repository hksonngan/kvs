/*****************************************************************************/
/**
 *  @file   StochasticLineEngine.cpp
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
#include "StochasticLineEngine.h"
#include <kvs/ShaderSource>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticLineEngine class.
 */
/*===========================================================================*/
StochasticLineEngine::StochasticLineEngine()
{
    this->initialize();
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticLineEngine class.
 *  @param  line [in] pointer to a line object
 */
/*===========================================================================*/
StochasticLineEngine::StochasticLineEngine( const kvs::LineObject* line )
{
    this->initialize();
    this->attachObject( line );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticLineEngine::initialize()
{
    m_ref_line = NULL;

    m_loc_identifier = 0;
    m_off_index = 0;
    m_off_coord = 0;
    m_off_color = 0;

    m_line_opacity = 1.0f;
}

/*===========================================================================*/
/**
 *  @brief  Sets an opacity value for the line object.
 *  @param  opacity [in] opaciti value
 */
/*===========================================================================*/
void StochasticLineEngine::setOpacity( const unsigned char opacity )
{
    m_line_opacity = static_cast<float>( opacity / 255.0f );
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the line object.
 *  @return <ReturnValue>
 */
/*===========================================================================*/
const kvs::ObjectBase* StochasticLineEngine::object() const
{
    return( m_ref_line );
}

/*===========================================================================*/
/**
 *  @brief  Returns rendering engine type.
 *  @return rendering engine type
 */
/*===========================================================================*/
const StochasticRenderingEngine::EngineType StochasticLineEngine::engineType() const
{
    return( BaseClass::Line );
}

/*===========================================================================*/
/**
 *  @brief  Attaches a line object.
 *  @param  object [in] pointer to a line object
 */
/*===========================================================================*/
void StochasticLineEngine::attachObject( const kvs::ObjectBase* object )
{
    const kvs::LineObject* line = kvs::LineObject::DownCast( object );

    // Check line object for rendering.
    if ( line->numberOfColors() != line->numberOfVertices() && line->numberOfColors() > 1 )
    {
        kvsMessageError( "Color type of this line is not vertex color." );
        exit(1);
    }

    m_ref_line = line;

    BaseClass::disableShading();
    BaseClass::enable_updating_vbo();
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffer.
 */
/*===========================================================================*/
void StochasticLineEngine::clearEnsembleBuffer()
{
    m_repetition_count = 0;
}

/*===========================================================================*/
/**
 *  @brief  Sets parameters to the shaders.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticLineEngine::setup_shader( const float modelview_matrix[16] )
{
    const size_t random_texture_size = m_random_texture.width();
    const int scramble_count = m_repetition_count++ * 12347;
//    const float rp_x = ( scramble_count ) % random_texture_size;
//    const float rp_y = ( scramble_count / random_texture_size ) % random_texture_size;
    const kvs::Vector2f random_offset(
        ( scramble_count ) % random_texture_size,
        ( scramble_count / random_texture_size ) % random_texture_size );
    const GLfloat random_texture_size_inv = 1.0f / random_texture_size;
//    const GLfloat screen_scale_x = m_width * 0.5f;
//    const GLfloat screen_scale_y = m_height * 0.5f;
    const kvs::Vector2f screen_scale( m_width * 0.5f, m_height * 0.5f );
    const kvs::Vector2f screen_scale_inv( 1.0 / m_width, 1.0 / m_height );

    m_shader_program.setUniform( "random_texture_size_inv", random_texture_size_inv );
    m_shader_program.setUniform( "random_offset", random_offset );
    m_shader_program.setUniform( "screen_scale", screen_scale );
    m_shader_program.setUniform( "screen_scale_inv", screen_scale_inv );
    m_shader_program.setUniform( "random_texture", 0 );
    m_shader_program.setUniform( "opacity", m_line_opacity );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the shaders.
 */
/*===========================================================================*/
void StochasticLineEngine::initialize_shader()
{
    const std::string vert_code = "SR_line.vert";
    const std::string frag_code = "SR_line.frag";

    kvs::ShaderSource vert( vert_code );
    kvs::ShaderSource frag( frag_code );

    if ( BaseClass::is_enabled_exact_depth_testing() )
    {
        vert.define("ENABLE_EXACT_DEPTH_TESTING");
        frag.define("ENABLE_EXACT_DEPTH_TESTING");
    }

    m_shader_program.create( vert, frag );
    m_loc_identifier = m_shader_program.attributeLocation( "identifier" );
}

/*===========================================================================*/
/**
 *  @brief  Creates the vertex and index buffer.
 */
/*===========================================================================*/
void StochasticLineEngine::create_vertex_buffer()
{
    m_vbo.release();
    m_ibo.release();

    const size_t nvertices = m_ref_line->numberOfVertices();
    const size_t nlines = m_ref_line->numberOfConnections();

    const bool has_color    = m_ref_line->numberOfColors() > 1;
    const bool has_connect  = m_ref_line->numberOfConnections() > 0 &&
        ( m_ref_line->lineType() == kvs::LineObject::Segment ||
          m_ref_line->lineType() == kvs::LineObject::Uniline );

    const size_t size_i = sizeof(IndexType) * 2 * nvertices;
    const size_t size_v = sizeof(CoordType) * 3 * nvertices;
    const size_t size_c = has_color ? sizeof(ColorType) * 3 * nvertices : 0;
    const size_t size_of_vertex = size_i + size_v + size_c;

    const size_t off_i = 0;
    const size_t off_v = off_i + size_i;
    const size_t off_c = off_v + size_v;

    const size_t random_texture_size = m_random_texture.width();
    kvs::ValueArray<IndexType> indices( 2 * nvertices );
    for ( size_t i = 0; i < nvertices; i++ )
    {
        unsigned int index = i * 12347;
        indices[ i * 2     ] = static_cast<IndexType>( index % random_texture_size );
        indices[ i * 2 + 1 ] = static_cast<IndexType>( ( index / random_texture_size ) % random_texture_size );
    }

    const IndexType*  ptr_i = indices.data();
    const CoordType*  ptr_v = m_ref_line->coords().data();
    const ColorType*  ptr_c = m_ref_line->colors().data();

    m_vbo.create( size_of_vertex );
    m_vbo.bind();
    m_vbo.load( size_i, ptr_i, off_i );
    m_vbo.load( size_v, ptr_v, off_v );
    if ( has_color )  m_vbo.load( size_c, ptr_c, off_c );
    m_vbo.unbind();

    if ( has_connect )
    {
        const size_t size_of_line = sizeof(ConnectType) * 2 * nlines;
        const ConnectType* ptr_conn = m_ref_line->connections().data();

        m_ibo.create( size_of_line );
        m_ibo.bind();
        m_ibo.load( size_of_line, ptr_conn, 0 );
        m_ibo.unbind();
    }

    m_off_index  = off_i;
    m_off_coord  = off_v;
    m_off_color  = off_c;
}

/*===========================================================================*/
/**
 *  @brief  Downloads the vertex dataset to the vertex buffer.
 */
/*===========================================================================*/
void StochasticLineEngine::download_vertex_buffer()
{
    this->create_vertex_buffer();
}

/*===========================================================================*/
/**
 *  @brief  Draws the vertex buffer.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticLineEngine::draw_vertex_buffer( const float modelview_matrix[16] )
{
    m_vbo.bind();
    m_ibo.bind();

    glActiveTexture(GL_TEXTURE0);     m_random_texture.bind();          glEnable(GL_TEXTURE_2D);

    m_shader_program.bind();

    this->setup_shader( modelview_matrix );

    const size_t nlines = m_ref_line->numberOfConnections();

    const bool has_color    = m_ref_line->numberOfColors() > 1;
    const bool has_connect  = m_ref_line->numberOfConnections() > 0 &&
        ( m_ref_line->lineType() == kvs::LineObject::Segment ||
          m_ref_line->lineType() == kvs::LineObject::Uniline );

//    glPolygonOffset( 1.0, 0.0 );
//    glEnable( GL_POLYGON_OFFSET_FILL );
    glEnable( GL_LINE_SMOOTH );

    const float width = m_ref_line->size();
    glLineWidth( width );

    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, (char*)(m_off_coord) );

    glEnableVertexAttribArray( m_loc_identifier );
    glVertexAttribPointer( m_loc_identifier, 2, GL_UNSIGNED_SHORT, GL_FALSE, 0, (char*)(m_off_index) );

    kvs::RGBColor color = m_ref_line->color();
    glColor3ub( color.r(), color.g(), color.b() );

    if ( has_color )
    {
        glEnableClientState( GL_COLOR_ARRAY );
        glColorPointer( 3, GL_UNSIGNED_BYTE, 0, (char*)(m_off_color) );
    }

    if ( has_connect )
    {
        switch ( m_ref_line->lineType() )
        {
            case kvs::LineObject::Uniline:
            {
                glDrawElements( GL_LINE_STRIP, nlines, GL_UNSIGNED_INT, 0 );
                break;
            }
            case kvs::LineObject::Segment:
            {
                glDrawElements( GL_LINES, 2 * nlines, GL_UNSIGNED_INT, 0 );
                break;
            }
            default: break;
        }
    }
    else
    {
        switch ( m_ref_line->lineType() )
        {
            case kvs::LineObject::Polyline:
            {
                size_t count = 0;
                const unsigned int* p_connect = m_ref_line->connections().data();
                for ( size_t i = 0; i < nlines; i++ )
                {
                    const size_t nvertices = p_connect[ i * 2 + 1 ] - p_connect[ i * 2 ] + 1;
                    glDrawArrays( GL_LINE_STRIP, count, nvertices );
                    count += nvertices;
                }
                break;
            }
            default:
            {
                const size_t nvertices = m_ref_line->numberOfVertices();
                glDrawArrays( GL_LINE_STRIP, 0, nvertices );
                break;
            }
        }
    }

    if ( has_color )  glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableVertexAttribArray( m_loc_identifier );

//    glDisable( GL_POLYGON_OFFSET_FILL );
    glDisable( GL_LINE_SMOOTH );

    m_shader_program.unbind();

    glActiveTexture(GL_TEXTURE0);    m_random_texture.unbind();         glDisable(GL_TEXTURE_2D);

    m_vbo.unbind();
    m_ibo.unbind();
}

} // end of namespace kvs
