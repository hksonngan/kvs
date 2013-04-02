/*****************************************************************************/
/**
 *  @file   EnsembleAverageBuffer.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: EnsembleAverageBuffer.h 1457 2013-03-24 06:32:17Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#ifndef KVS__ENSEMBLE_AVERAGE_BUFFER_H_INCLUDE
#define KVS__ENSEMBLE_AVERAGE_BUFFER_H_INCLUDE

#include <kvs/Texture2D>
#include <kvs/FrameBufferObject>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Ensemble average buffer class.
 */
/*===========================================================================*/
class EnsembleAverageBuffer
{
protected:

    bool m_enable_accum; ///< check flag for the accumulation buffer
    size_t m_width; ///< buffer width
    size_t m_height; ///< buffer height
    size_t m_count; ///< number of accumulations
    kvs::Texture2D m_texture; ///< texture for the repetition
    kvs::FrameBufferObject m_framebuffer; ///< Frame Buffer Object
    float m_accum_scale; ///< accumulation scale

public:

    EnsembleAverageBuffer( const bool use_accum = false );

    void create( const size_t width, const size_t height );
    void clear();
    void bind();
    void unbind();
    void add();
    void draw();
    void enableAccumulationBuffer();
    void disableAccumulationBuffer();
    bool isEnabledAccumulationBuffer();
    size_t count() const;
    float opacity() const;

protected:

    void draw_quad( const float r, const float g, const float b, const float a );
};

} // end of namespace kvs

#endif // KVS__ENSEMBLE_AVERAGE_BUFFER_H_INCLUDE
