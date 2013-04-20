/****************************************************************************/
/**
 *  @file   VolumeRendererBase.cpp
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
/****************************************************************************/
#include "VolumeRendererBase.h"
#include <kvs/Camera>
#include <kvs/Math>
#include <kvs/OpenGL>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
VolumeRendererBase::VolumeRendererBase():
    m_width( 0 ),
    m_height( 0 ),
    m_enable_shading( true ),
    m_shader( NULL )
{
    m_depth_buffer.setFormat( GL_DEPTH_COMPONENT );
    m_depth_buffer.setType( GL_FLOAT );

    m_color_buffer.setFormat( GL_RGBA );
    m_color_buffer.setType( GL_UNSIGNED_BYTE );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
VolumeRendererBase::~VolumeRendererBase()
{
    if ( m_shader ) { delete m_shader; }
}

size_t VolumeRendererBase::windowWidth() const
{
    return m_width;
}

size_t VolumeRendererBase::windowHeight() const
{
    return m_height;
}

/*==========================================================================*/
/**
 *  Set the transder function.
 *  @param tfunc [in] transfer function
 */
/*==========================================================================*/
void VolumeRendererBase::setTransferFunction( const kvs::TransferFunction& tfunc )
{
    m_tfunc = tfunc;
}

/*==========================================================================*/
/**
 *  Enable shading function.
 */
/*==========================================================================*/
void VolumeRendererBase::enableShading()
{
    m_enable_shading = true;
}

/*==========================================================================*/
/**
 *  Disable shading function.
 */
/*==========================================================================*/
void VolumeRendererBase::disableShading()
{
    m_enable_shading = false;
}

/*==========================================================================*/
/**
 *  Test whether the shading is enable or disable.
 *  @return true, if the shading is enable.
 */
/*==========================================================================*/
bool VolumeRendererBase::isEnabledShading() const
{
    return m_enable_shading;
}

/*==========================================================================*/
/**
 *  Get the trunsfer function.
 *  @return transfer function
 */
/*==========================================================================*/
const kvs::TransferFunction& VolumeRendererBase::transferFunction() const
{
    return m_tfunc;
}

kvs::Shader::ShadingModel& VolumeRendererBase::shader()
{
    return *m_shader;
}

/*==========================================================================*/
/**
 *  Get the trunsfer function.
 *  @return transfer function
 */
/*==========================================================================*/
kvs::TransferFunction& VolumeRendererBase::transferFunction()
{
    return m_tfunc;
}

void VolumeRendererBase::setWindowSize( const size_t width, const size_t height )
{
    m_width = width;
    m_height = height;
}

void VolumeRendererBase::allocateDepthData( const size_t size )
{
    m_depth_data.allocate( size );
}

void VolumeRendererBase::allocateColorData( const size_t size )
{
    m_color_data.allocate( size );
}

void VolumeRendererBase::fillDepthData( const kvs::Real32 value )
{
    m_depth_data.fill( value );
}

void VolumeRendererBase::fillColorData( const kvs::UInt8 value )
{
    m_color_data.fill( value );
}

/*==========================================================================*/
/**
 *  Draw the rendering image.
 */
/*==========================================================================*/
void VolumeRendererBase::drawImage()
{
    GLint viewport[4];
    kvs::OpenGL::GetViewport( viewport );

    kvs::OpenGL::SetDepthFunc( GL_LEQUAL );
    kvs::OpenGL::SetDepthMask( GL_TRUE );
    kvs::OpenGL::SetColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE );
    {
        kvs::OpenGL::WithEnabled e( GL_DEPTH_TEST );
        m_depth_buffer.draw( m_width, m_height, viewport, m_depth_data.data() );
    }

    kvs::OpenGL::SetBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
    kvs::OpenGL::SetColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
    {
        kvs::OpenGL::WithEnabled e( GL_BLEND );
        kvs::OpenGL::WithDisabled d( GL_DEPTH_TEST );
        m_color_buffer.draw( m_width, m_height, viewport, m_color_data.data() );
    }
}

} // end of namespace kvs
