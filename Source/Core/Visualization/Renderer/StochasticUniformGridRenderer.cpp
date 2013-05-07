/*****************************************************************************/
/**
 *  @file   StochasticUniformGridRenderer.cpp
 *  @author Naoya Maeda, Naohisa Sakamoto
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
#include "StochasticUniformGridRenderer.h"
#include <cmath>
#include <cfloat>
#include <kvs/OpenGL>
#include <kvs/StructuredVolumeObject>
#include <kvs/TransferFunction>
#include <kvs/ColorMap>
#include <kvs/OpacityMap>
#include <kvs/ValueArray>
#include <kvs/Camera>
#include <kvs/Light>
#include <kvs/Assert>
#include <kvs/Message>


namespace
{

double AlphaToRho( double alpha )
{
    //const double pi = 3.141592;
    //const double dt = 0.5;
    //const double r = 1;
    //return std::log( 1 - alpha ) / ( pi * r * r * dt );
    return alpha;
}

kvs::ValueArray<float> PreIntegrationTable( const kvs::TransferFunction& tf )
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

}


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new StochasticUniformGridRenderer class.
 */
/*===========================================================================*/
StochasticUniformGridRenderer::StochasticUniformGridRenderer():
    StochasticRendererBase( new Engine() )
{
}

/*===========================================================================*/
/**
 *  @brief  Sets a number of slices.
 *  @param  nslices [in] number of slices
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::setNumberOfSlices( const size_t nslices )
{
    static_cast<Engine&>( engine() ).setNumberOfSlices( nslices );
}

/*===========================================================================*/
/**
 *  @brief  Sets a transfer function.
 *  @param  transfer_function [in] transfer function
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::setTransferFunction( const kvs::TransferFunction& transfer_function )
{
    static_cast<Engine&>( engine() ).setTransferFunction( transfer_function );
}

/*===========================================================================*/
/**
 *  @brief  Constructs a new Engine class.
 */
/*===========================================================================*/
StochasticUniformGridRenderer::Engine::Engine():
    m_random_index( 0 ),
    m_nslices( 128 ),
    m_transfer_function_changed( true )
{
}

/*===========================================================================*/
/**
 *  @brief  Releases the GPU resources.
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::release()
{
    m_shader_program.release();
    m_volume_texture.release();
    m_preintegration_table.release();
    m_transfer_function_changed = true;
}

/*===========================================================================*/
/**
 *  @brief  Create.
 *  @param  object [in] pointer to the volume object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::create( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::StructuredVolumeObject* volume = kvs::StructuredVolumeObject::DownCast( object );

    attachObject( object );
    createRandomTexture();
    this->create_shader_program();
    this->create_texture_object( volume );
    this->create_preintegration_table();
}

/*===========================================================================*/
/**
 *  @brief  Update.
 *  @param  object [in] pointer to the object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::update( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
}

/*===========================================================================*/
/**
 *  @brief  Set up.
 *  @param  reset_count [in] flag for the repetition count
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::setup( const bool reset_count )
{
    if ( reset_count ) resetRepetitions();
    m_random_index = m_shader_program.attributeLocation("random_index");

    if ( m_transfer_function_changed )
    {
        // Re-create pre-integration table.
        m_preintegration_table.release();
        this->create_preintegration_table();
    }
}

/*===========================================================================*/
/**
 *  @brief  Draw an ensemble.
 *  @param  object [in] pointer to the line object
 *  @param  camera [in] pointer to the camera
 *  @param  light [in] pointer to the light
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::draw( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light )
{
    kvs::StructuredVolumeObject* volume = kvs::StructuredVolumeObject::DownCast( object );

    kvs::Texture::Binder bind1( m_volume_texture, 0 );
    kvs::Texture::Binder bind2( randomTexture(), 1 );
    kvs::Texture::Binder bind3( m_preintegration_table, 2 );
    kvs::ProgramObject::Binder bind4( m_shader_program );
    {
        const size_t size = randomTextureSize();
        const float offset_x = (float)( m_random.randInteger() % size );
        const float offset_y = (float)( m_random.randInteger() % size );
        const kvs::Vec2 random_offset( offset_x, offset_y );
        const float inv_x = 1.0f / volume->resolution().x();
        const float inv_y = 1.0f / volume->resolution().y();
        const float inv_z = 1.0f / volume->resolution().z();
        const kvs::Vec3 volume_resolution_inv( inv_x, inv_y, inv_z );

        m_shader_program.setUniform( "random_texture_size_inv", 1.0f / randomTextureSize() );
        m_shader_program.setUniform( "random_offset", random_offset );
        m_shader_program.setUniform( "volume_resolution_inv", volume_resolution_inv );
        m_shader_program.setUniform( "volume_texture", 0 );
        m_shader_program.setUniform( "random_texture", 1 );
        m_shader_program.setUniform( "preintegration_texture", 2 );
    }
    {
        kvs::OpenGL::Disable( GL_LIGHTING );
        kvs::OpenGL::Disable( GL_CULL_FACE );
        KVS_GL_CALL( glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ) );

        GLdouble m[16]; kvs::OpenGL::GetModelViewMatrix( m );
        GLdouble p[16]; kvs::OpenGL::GetProjectionMatrix( p );
        GLint v[4]; kvs::OpenGL::GetViewport( v );

        kvs::Vector3ui res = volume->resolution();
        double xmin=FLT_MAX, xmax=-FLT_MAX, ymin=FLT_MAX, ymax=-FLT_MAX, zmin=FLT_MAX, zmax=-FLT_MAX;
        for ( int i = 0; i < 8; ++i )
        {
            float bbx = ( i&1 ) ? ( float )res.x() : 0.0f;
            float bby = ( i&2 ) ? ( float )res.y() : 0.0f;
            float bbz = ( i&4 ) ? ( float )res.z() : 0.0f;

            double x,y,z;
            KVS_GL_CALL( gluProject( bbx,bby,bbz, m, p, v, &x, &y, &z ) );
            if ( x < xmin ) xmin = x;
            if ( x > xmax ) xmax = x;
            if ( y < ymin ) ymin = y;
            if ( y > ymax ) ymax = y;
            if ( z < zmin ) zmin = z;
            if ( z > zmax ) zmax = z;
        }

        double fx = 1.0 / res.x();
        double fy = 1.0 / res.y();
        double fz = 1.0 / res.z();

        int nslices = m_nslices;
        float dz = ( float )( ( zmax-zmin ) / nslices );
        float z  = ( float )zmax - dz/2.0f;

        const size_t random_texture_size = randomTexture().width();
        for ( int n = nslices-1; n >= 0; --n, z -= dz )
        {
            const kvs::Vector2f random_offset(
                (float)( m_random.randInteger() % random_texture_size ),
                (float)( m_random.randInteger() % random_texture_size ) );
            m_shader_program.setUniform( "random_offset", random_offset );

            glBegin( GL_QUADS );
            GLdouble point[3];
            gluUnProject( xmin,ymin,z, m, p, v, point + 0, point + 1, point + 2 );
            glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
            glVertex3dv( point );

            gluUnProject( xmax,ymin,z, m, p, v, point + 0, point + 1, point + 2 );
            glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
            glVertex3dv( point );

            gluUnProject( xmax,ymax,z, m, p, v, point + 0, point + 1, point + 2 );
            glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
            glVertex3dv( point );

            gluUnProject( xmin,ymax,z, m, p, v, point + 0, point + 1, point + 2 );
            glTexCoord3d( fx*point[0], fy*point[1], fz*point[2] );
            glVertex3dv( point );
            glEnd(); // GL_QUADS
        }
    }

    countRepetitions();
}

/*===========================================================================*/
/**
 *  @brief  Creates shader program.
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::create_shader_program()
{
    kvs::ShaderSource vert( "SR_uniform_grid.vert" );
    kvs::ShaderSource frag( "SR_uniform_grid.frag" );
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
 *  @brief  Create texture objects.
 *  @param  volume [in] pointer to the structured volume object
 */
/*===========================================================================*/
void StochasticUniformGridRenderer::Engine::create_texture_object( const kvs::StructuredVolumeObject* volume )
{
    if ( volume->gridType() != kvs::StructuredVolumeObject::Uniform )
    {
        kvsMessageError("Not supported grid type.");
        return;
    }

    if ( volume->veclen() != 1 )
    {
        kvsMessageError("Not scalar volume.");
        return;
    }

    GLenum data_type = 0;
    switch ( volume->values().typeID() )
    {
    case kvs::Type::TypeUInt8: data_type = GL_UNSIGNED_BYTE; break;
    case kvs::Type::TypeReal32: data_type = GL_FLOAT; break;
    default:
    {
        kvsMessageError("Not supported data type.");
        break;
    }
    }

    const size_t width = volume->resolution().x();
    const size_t height = volume->resolution().y();
    const size_t depth = volume->resolution().z();
    m_volume_texture.setPixelFormat( GL_RED, GL_RED, data_type );
    m_volume_texture.setWrapS( GL_CLAMP_TO_EDGE );
    m_volume_texture.setWrapT( GL_CLAMP_TO_EDGE );
    m_volume_texture.setWrapR( GL_CLAMP_TO_EDGE );
    m_volume_texture.setMagFilter( GL_LINEAR );
    m_volume_texture.setMinFilter( GL_LINEAR );
    m_volume_texture.create( width, height, depth, volume->values().data() );
}

void StochasticUniformGridRenderer::Engine::create_preintegration_table()
{
    const size_t resolution = m_transfer_function.resolution();
    kvs::ValueArray<float> preintegration = ::PreIntegrationTable( m_transfer_function );
    m_preintegration_table.setPixelFormat( GL_RGBA, GL_RGBA, GL_FLOAT );
    m_preintegration_table.setWrapS( GL_CLAMP_TO_EDGE );
    m_preintegration_table.setWrapT( GL_CLAMP_TO_EDGE );
    m_preintegration_table.setMagFilter( GL_LINEAR );
    m_preintegration_table.setMinFilter( GL_LINEAR );
    m_preintegration_table.create( resolution, resolution, preintegration.data() );
    m_transfer_function_changed = false;
}

} // end of namespace kvs
