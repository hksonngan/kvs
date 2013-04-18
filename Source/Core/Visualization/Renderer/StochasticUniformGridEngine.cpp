/*****************************************************************************/
/**
 *  @file   StochasticUniformGridEngine.cpp
 *  @author Naoya Maeda
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
#include "StochasticUniformGridEngine.h"
#include <kvs/TransferFunction>
#include <kvs/CellByCellParticleGenerator>
#include <kvs/Type>
#include <kvs/Exception>
#include <kvs/ShaderSource>
#include <cfloat>


namespace
{
    const int NumberOfSlices = 128;
    const float EdgeSize = 10.0;

double AlphaToRho( double alpha )
{
    //const double pi = 3.141592;
    //const double dt = 0.5;
    //const double r = 1;
    //return std::log( 1 - alpha ) / ( pi * r * r * dt );
    return alpha;
}

kvs::ValueArray<float> Make( const kvs::TransferFunction& tf )
{
    kvs::ColorMap cmap = tf.colorMap();
    kvs::OpacityMap omap = tf.opacityMap();

    KVS_ASSERT( cmap.resolution() == omap.resolution() );

    const int res = ( int )cmap.resolution();
    kvs::ValueArray<double> table( res * 4 );
    table[0] = table[1] = table[2] = table[3] = 0.0;

    const double L = 1.0 / ( res - 1 );
    double R = 0.0;
    double G = 0.0;
    double B = 0.0;
    double Rho = 0.0;
    kvs::RGBColor c0 = cmap[ 0 ];
    double r0 = c0.r() / 255.0;
    double g0 = c0.g() / 255.0;
    double b0 = c0.b() / 255.0;
    double rho0 = AlphaToRho( omap[ 0 ] );
    for ( int i = 1; i < res; ++i )
    {
        kvs::RGBColor c = cmap[ i ];
        double r1 = c.r() / 255.0;
        double g1 = c.g() / 255.0;
        double b1 = c.b() / 255.0;
        double rho1 = AlphaToRho( omap[ i ] );

        R += L / 6.0 * ( ( rho1 + rho0 ) * ( r1 + r0 ) + rho1 * r1 + rho0 * r0 );
        G += L / 6.0 * ( ( rho1 + rho0 ) * ( g1 + g0 ) + rho1 * g1 + rho0 * g0 );
        B += L / 6.0 * ( ( rho1 + rho0 ) * ( b1 + b0 ) + rho1 * b1 + rho0 * b0 );
        Rho += L / 2.0 * ( rho1 + rho0 );

        table[ i * 4 + 0 ] = R;
        table[ i * 4 + 1 ] = G;
        table[ i * 4 + 2 ] = B;
        table[ i * 4 + 3 ] = Rho;

        r0 = r1;
        g0 = g1;
        b0 = b1;
        rho0 = rho1;
    }

    kvs::ValueArray<float> table2d( res * res * 4 );
    for ( int i = 0; i < res; ++i )
    {
        for ( int j = 0; j < res; ++j )
        {
            const int index = 4 * ( res * i + j );
            if ( i == j )
            {
                kvs::RGBColor c = cmap[ i ];
                const float a = omap[ i ];
                table2d[ index + 0 ] = a * c.r() / 255.0f;
                table2d[ index + 1 ] = a * c.g() / 255.0f;
                table2d[ index + 2 ] = a * c.b() / 255.0f;
                table2d[ index + 3 ] = a;
            }
            else
            {
                const double sf = i / ( double )( res - 1 );
                const double sb = j / ( double )( res - 1 );
                const double factor = 1 / ( sb - sf );
                for ( int k = 0; k < 4; ++k )
                {
                    table2d[ index + k ] = ( float )( ( table[ j * 4 + k ] - table[ i * 4 + k ] ) * factor );
                }
            }
        }
    }

    // a( sf, sb, d ) = 1 - exp( - d / ( sb - sf ) * ( A( sf ) - A( sb ) ) )
    // c( sf, sb, d ) = d / ( sb - sf ) * ( C( sb ) - C( sf ) )
    return table2d;
}

GLenum ToGLType( kvs::Type::TypeID type )
{
    switch ( type )
    {
    case kvs::Type::TypeUInt8:  return GL_UNSIGNED_BYTE;
    case kvs::Type::TypeReal32: return GL_FLOAT;
    default: break;
    }
    KVS_THROW( kvs::NotSupportedException, "Not supported type" );
}

}

namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticUniformGridEngine class.
 */
/*===========================================================================*/
StochasticUniformGridEngine::StochasticUniformGridEngine()
{
    this->initialize();
    BaseClass::setShader( kvs::Shader::Lambert() );
}

StochasticUniformGridEngine::StochasticUniformGridEngine( const kvs::StructuredVolumeObject* volume )
{
    this->initialize();
    this->attachObject( volume );
    BaseClass::setShader( kvs::Shader::Lambert() );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the member parameters.
 */
/*===========================================================================*/
void StochasticUniformGridEngine::initialize()
{
    m_ref_volume = NULL;
    m_loc_identifier = 0;
    m_pre_table_name = 0;
}

/*===========================================================================*/
/**
 *  @brief  Returns the pointer to the polygon object.
 *  @return pointer to the polygon object
 */
/*===========================================================================*/
const kvs::ObjectBase* StochasticUniformGridEngine::object() const
{
    return m_ref_volume;
}

/*===========================================================================*/
/**
 *  @brief  Attaches a polygon object.
 *  @param  object [in] pointer to a polygon object
 */
/*===========================================================================*/
void StochasticUniformGridEngine::attachObject( const kvs::ObjectBase* object )
{
    const kvs::StructuredVolumeObject* volume = kvs::StructuredVolumeObject::DownCast( object );

    if ( volume->gridType() != kvs::StructuredVolumeObject::Uniform )
    {
        kvsMessageError( "Not supported." );
        exit( 1 );
    }

    m_ref_volume = volume;
}

/*===========================================================================*/
/**
 *  @brief  Returns the rendering engine type.
 *  @return rendering engine type
 */
/*===========================================================================*/
const StochasticUniformGridEngine::EngineType StochasticUniformGridEngine::engineType() const
{
    return BaseClass::UniformGrid;
}

/*===========================================================================*/
/**
 *  @brief  Clears the ensemble buffer.
 */
/*===========================================================================*/
void StochasticUniformGridEngine::clearEnsembleBuffer()
{
    m_repetition_count = 0;
}

/*===========================================================================*/
/**
 *  @brief  Sets parameters to the shaders.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticUniformGridEngine::setup_shader( const float /*modelview_matrix*/[16] )
{
    const size_t random_texture_size = m_random_texture.width();
//    const float rp_x = ( float )( m_rng.randInteger() % random_texture_size );
//    const float rp_y = ( float )( m_rng.randInteger() % random_texture_size );
    const kvs::Vector2f random_offset(
        (float)( m_rng.randInteger() % random_texture_size ),
        (float)( m_rng.randInteger() % random_texture_size ) );
    const GLfloat random_texture_size_inv = 1.0f / random_texture_size;
//    const GLfloat screen_scale_x = m_width * 0.5f;
//    const GLfloat screen_scale_y = m_height * 0.5f;
    const kvs::Vector2f screen_scale( m_width * 0.5f, m_height * 0.5f );
    const kvs::Vector2f screen_scale_inv( 1.0 / m_width, 1.0 / m_height );
    const kvs::Vector3ui volume_resolution = m_ref_volume->resolution();
    const kvs::Vector3f volume_resolution_inv(
        1.0f / volume_resolution.x(),
        1.0f / volume_resolution.y(),
        1.0f / volume_resolution.z() );

    m_shader_program.setUniform( "random_texture_size_inv", random_texture_size_inv );
    m_shader_program.setUniform( "random_offset", random_offset );
    m_shader_program.setUniform( "screen_scale", screen_scale );
    m_shader_program.setUniform( "screen_scale_inv", screen_scale_inv );
    m_shader_program.setUniform( "volume_resolution_inv", volume_resolution_inv );
    m_shader_program.setUniform( "volume_texture", 0 );
    m_shader_program.setUniform( "random_texture", 1 );
    m_shader_program.setUniform( "preintegration_texture", 2 );
}

/*===========================================================================*/
/**
 *  @brief  Initializes the shaders.
 */
/*===========================================================================*/
void StochasticUniformGridEngine::initialize_shader()
{
    const std::string vert_code = "SR_uniform_grid.vert";
    const std::string frag_code = "SR_uniform_grid.frag";

    kvs::ShaderSource vert( vert_code );
    kvs::ShaderSource frag( frag_code );

    if ( BaseClass::isEnabledShading() )
    {
        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading: frag.define( "ENABLE_LAMBERT_SHADING" ); break;
        case kvs::Shader::PhongShading: frag.define( "ENABLE_PHONG_SHADING" ); break;
        case kvs::Shader::BlinnPhongShading: frag.define( "ENABLE_BLINN_PHONG_SHADING" ); break;
        default: /* NO SHADING */ break;
        }

        GLboolean status = 0; glGetBooleanv( GL_LIGHT_MODEL_TWO_SIDE, &status );
        if ( status == GL_TRUE ) { frag.define( "ENABLE_TWO_SIDE_LIGHTING" ); }
    }

    m_shader_program.create( vert, frag );
    m_loc_identifier = m_shader_program.attributeLocation( "identifier" );

    if ( BaseClass::isEnabledShading() )
    {
        m_shader_program.bind();
        switch ( BaseClass::m_shader->type() )
        {
        case kvs::Shader::LambertShading:
        {
            const GLfloat Ka = ( ( kvs::Shader::Lambert* )( BaseClass::m_shader ) )->Ka;
            const GLfloat Kd = ( ( kvs::Shader::Lambert* )( BaseClass::m_shader ) )->Kd;
            m_shader_program.setUniform( "shading.Ka", Ka );
            m_shader_program.setUniform( "shading.Kd", Kd );
            break;
        }
        case kvs::Shader::PhongShading:
        {
            const GLfloat Ka = ( ( kvs::Shader::Phong* )( BaseClass::m_shader ) )->Ka;
            const GLfloat Kd = ( ( kvs::Shader::Phong* )( BaseClass::m_shader ) )->Kd;
            const GLfloat Ks = ( ( kvs::Shader::Phong* )( BaseClass::m_shader ) )->Ks;
            const GLfloat S  = ( ( kvs::Shader::Phong* )( BaseClass::m_shader ) )->S;
            m_shader_program.setUniform( "shading.Ka", Ka );
            m_shader_program.setUniform( "shading.Kd", Kd );
            m_shader_program.setUniform( "shading.Ks", Ks );
            m_shader_program.setUniform( "shading.S",  S );
            break;
        }
        case kvs::Shader::BlinnPhongShading:
        {
            const GLfloat Ka = ( ( kvs::Shader::BlinnPhong* )( BaseClass::m_shader ) )->Ka;
            const GLfloat Kd = ( ( kvs::Shader::BlinnPhong* )( BaseClass::m_shader ) )->Kd;
            const GLfloat Ks = ( ( kvs::Shader::BlinnPhong* )( BaseClass::m_shader ) )->Ks;
            const GLfloat S  = ( ( kvs::Shader::BlinnPhong* )( BaseClass::m_shader ) )->S;
            m_shader_program.setUniform( "shading.Ka", Ka );
            m_shader_program.setUniform( "shading.Kd", Kd );
            m_shader_program.setUniform( "shading.Ks", Ks );
            m_shader_program.setUniform( "shading.S",  S );
            break;
        }
        default: /* NO SHADING */ break;
        }
        m_shader_program.unbind();
    }

    if ( glGetError() != GL_NO_ERROR ) throw "Error";

    kvs::Vector3ui res = m_ref_volume->resolution();

    // Setup volume texture
    glGenTextures( 1, &m_volume_texture_name );
    glBindTexture( GL_TEXTURE_3D, m_volume_texture_name );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexImage3D( GL_TEXTURE_3D, 
        0, 
        GL_RED, 
        ( int )res.x(), 
        ( int )res.y(), 
        ( int )res.z(), 
        0, 
        GL_RED, 
        ::ToGLType( m_ref_volume->values().typeID() ), 
        m_ref_volume->values().data() );
    glBindTexture( GL_TEXTURE_3D, 0 );

    // Setup preintegration table
    const kvs::TransferFunction& tf = m_transfer_function;
    const size_t tres = tf.resolution();
    kvs::ValueArray<float> pre_table = ::Make( tf );

    glGenTextures( 1, &m_pre_table_name );
    glBindTexture( GL_TEXTURE_2D, m_pre_table_name );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexImage2D( 
      GL_TEXTURE_2D,
      0,
      GL_RGBA,
      ( int )tres,
      ( int )tres,
      0,
      GL_RGBA,
      GL_FLOAT,
      pre_table.data() );
    glBindTexture( GL_TEXTURE_2D, 0 );

    if ( glGetError() != GL_NO_ERROR ) throw "Error";
}

/*===========================================================================*/
/**
 *  @brief  Draws the vertex buffer.
 *  @param  modelview_matrix [in] modelview matrix
 */
/*===========================================================================*/
void StochasticUniformGridEngine::draw_vertex_buffer( const float modelview_matrix[16] )
{
    //if ( !m_table.isTexture() )
    //{
    //    m_table.setTransferFunction( m_transfer_function, 0.0f, 1.0f );
    //    m_table.create( EdgeSize ); // edgesize
    //    m_table.download();
    //}

    glPushAttrib( GL_COLOR_BUFFER_BIT | 
                  GL_DEPTH_BUFFER_BIT | 
                  GL_ENABLE_BIT       | 
                  GL_LIGHTING_BIT     | 
                  GL_POLYGON_BIT      | 
                  GL_TEXTURE_BIT );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_3D, m_volume_texture_name );
    glActiveTexture( GL_TEXTURE1 );
    m_random_texture.bind();
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_2D, m_pre_table_name );

    m_shader_program.bind();
    this->setup_shader( modelview_matrix );

    // openGL setup
    glDisable( GL_LIGHTING );
    glDisable( GL_CULL_FACE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    //--------------------------------------------------//
    // gets the direction of the observer
    double  gl_model[16];
    double  gl_proj [16];
    int     gl_view [4];
    glGetDoublev( GL_MODELVIEW_MATRIX , gl_model );
    glGetDoublev( GL_PROJECTION_MATRIX, gl_proj );
    glGetIntegerv( GL_VIEWPORT        , gl_view );

    //--------------------------------------------------//
    // gets the bounding box of the grid in the screen coordinates
    kvs::Vector3ui res = m_ref_volume->resolution();
    double xmin=FLT_MAX, xmax=-FLT_MAX, ymin=FLT_MAX, ymax=-FLT_MAX, zmin=FLT_MAX, zmax=-FLT_MAX;
    for ( int i = 0; i < 8; ++i )
    {
        float bbx = ( i&1 ) ? ( float )res.x() : 0.0f;
        float bby = ( i&2 ) ? ( float )res.y() : 0.0f;
        float bbz = ( i&4 ) ? ( float )res.z() : 0.0f;

        double x,y,z;
//        kvs::detail::Project( bbx,bby,bbz, gl_model, gl_proj, gl_view, &x, &y, &z );
        gluProject( bbx,bby,bbz, gl_model, gl_proj, gl_view, &x, &y, &z );

        if ( x < xmin ) xmin = x;
        if ( x > xmax ) xmax = x;
        if ( y < ymin ) ymin = y;
        if ( y > ymax ) ymax = y;
        if ( z < zmin ) zmin = z;
        if ( z > zmax ) zmax = z;
    }

    //--------------------------------------------------//
    // world to tex coordinates
    double fx = 1.0 / res.x();
    double fy = 1.0 / res.y();
    double fz = 1.0 / res.z();

    //--------------------------------------------------//
    // draw each slice of the texture in the viewer coordinates
    int nslices = NumberOfSlices;
    float dz = ( float )( ( zmax-zmin ) / nslices );
    float z  = ( float )zmax - dz/2.0f;

    const size_t random_texture_size = m_random_texture.width();

    for( int n = nslices-1; n >= 0; --n, z -= dz )
    {
//        const float rp_x = ( float )( m_rng.randInteger() % random_texture_size );
//        const float rp_y = ( float )( m_rng.randInteger() % random_texture_size );
        const kvs::Vector2f random_offset(
            (float)( m_rng.randInteger() % random_texture_size ),
            (float)( m_rng.randInteger() % random_texture_size ) );
        m_shader_program.setUniform( "random_offset", random_offset );

        glBegin( GL_QUADS );
        GLdouble point[3];
//        kvs::detail::UnProject( xmin,ymin,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        gluUnProject( xmin,ymin,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
        glVertex3dv( point );

//        kvs::detail::UnProject( xmax,ymin,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        gluUnProject( xmax,ymin,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
        glVertex3dv( point );

//        kvs::detail::UnProject( xmax,ymax,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        gluUnProject( xmax,ymax,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
        glVertex3dv( point );

//        kvs::detail::UnProject( xmin,ymax,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        gluUnProject( xmin,ymax,z, gl_model, gl_proj, gl_view, point + 0, point + 1, point + 2 );
        glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
        glVertex3dv( point );
        glEnd(); // GL_QUADS
    }

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_3D, 0 );
    glActiveTexture( GL_TEXTURE1 );
    m_random_texture.unbind();
    glActiveTexture( GL_TEXTURE2 );
    glBindTexture( GL_TEXTURE_1D, 0 );
    glActiveTexture( GL_TEXTURE3 );
    glBindTexture( GL_TEXTURE_2D, 0 );
    glActiveTexture( GL_TEXTURE0 );

    m_shader_program.unbind();

    glPopAttrib();
    glFlush();
}

void StochasticUniformGridEngine::setTransferFunction( const kvs::TransferFunction& tf )
{
    m_transfer_function = tf;

    //if ( m_table.isDownloaded() )
    //{
    //    m_table.release();
    //}
}

} // end of namespace kvs
