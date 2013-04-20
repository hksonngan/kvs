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
    bool m_enable_shading; ///< shading flag
    kvs::ValueArray<kvs::Real32> m_depth_data; ///< depth data as float type
    kvs::ValueArray<kvs::UInt8> m_color_data; ///< color (RGBA) data as uchar type
    kvs::FrameBuffer m_depth_buffer; ///< depth buffer
    kvs::FrameBuffer m_color_buffer; ///< color (RGBA) buffer
    kvs::TransferFunction m_tfunc; ///< transfer function
    kvs::Shader::ShadingModel* m_shader; ///< shading method

public:

    VolumeRendererBase();
    virtual ~VolumeRendererBase();

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
    bool isEnabledShading() const;
    const kvs::TransferFunction& transferFunction() const;

protected:

    kvs::Shader::ShadingModel& shader();
    kvs::TransferFunction& transferFunction();
    void setWindowSize( const size_t width, const size_t height );
    void allocateDepthData( const size_t size );
    void allocateColorData( const size_t size );
    void fillDepthData( const kvs::Real32 value );
    void fillColorData( const kvs::UInt8 value );
    void drawImage();
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
