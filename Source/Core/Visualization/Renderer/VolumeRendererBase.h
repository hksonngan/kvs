/****************************************************************************/
/**
 *  @file   VolumeRendererBase.h
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
#ifndef KVS__VOLUME_RENDERER_BASE_H_INCLUDE
#define KVS__VOLUME_RENDERER_BASE_H_INCLUDE

#include <kvs/DebugNew>
#include <kvs/RendererBase>
#include <kvs/TransferFunction>
#include <kvs/FrameBuffer>
#include <kvs/ValueArray>
#include <kvs/Shader>


namespace kvs
{

/*==========================================================================*/
/**
 *  Volume renderer base class.
 */
/*==========================================================================*/
class VolumeRendererBase : public kvs::RendererBase
{
    kvsModuleName( kvs::VolumeRendererBase );

protected:

    size_t m_width; ///< width of rendering image
    size_t m_height; ///< height of rendering image
    kvs::FrameBuffer m_depth_buffer; ///< depth buffer
    kvs::ValueArray<kvs::Real32> m_depth_data; ///< depth data as float type
    kvs::FrameBuffer m_color_buffer; ///< color (RGBA) buffer
    kvs::ValueArray<kvs::UInt8> m_color_data; ///< color (RGBA) data as uchar type
    bool m_enable_shading; ///< shading flag
    kvs::TransferFunction m_tfunc; ///< transfer function
    kvs::Shader::ShadingModel* m_shader; ///< shading method

public:

    VolumeRendererBase();
    virtual ~VolumeRendererBase();

public:

    virtual void exec(
        kvs::ObjectBase* object,
        kvs::Camera* camera = NULL,
        kvs::Light* light  = NULL ) = 0;

    size_t windowWidth() const;
    size_t windowHeight() const;

    template <typename ShadingType>
    void setShader( const ShadingType shader );
    void setTransferFunction( const kvs::TransferFunction& tfunc );

    void enableShading();
    void disableShading();

    const bool isEnabledShading() const;
    const kvs::TransferFunction& transferFunction() const;

    void initialize();
    void clear();

protected:

    kvs::TransferFunction& transferFunction();
    void setWindowSize( const size_t width, const size_t height );
    void allocateDepthData( const size_t size );
    void allocateColorData( const size_t size );
    void fillDepthData( const kvs::Real32 value );
    void fillColorData( const kvs::UInt8 value );
    void drawImage();
//    void drawDepthBuffer( const int* viewport );
//    void drawColorBuffer( const int* viewport );
};

template <typename ShadingType>
inline void VolumeRendererBase::setShader( const ShadingType shader )
{
    if ( m_shader )
    {
        delete m_shader;
        m_shader = NULL;
    }

    m_shader = new ShadingType( shader );
    if ( !m_shader )
    {
        kvsMessageError("Cannot create a specified shader.");
    }
};

} // end of namespace kvs

#endif // KVS__VOLUME_RENDERER_BASE_H_INCLUDE
