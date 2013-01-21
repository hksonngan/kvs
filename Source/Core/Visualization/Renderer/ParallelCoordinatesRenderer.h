/*****************************************************************************/
/**
 *  @file   ParallelCoordinatesRenderer.h
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
/*****************************************************************************/
#ifndef KVS__PARALLEL_COORDINATES_RENDERER_H_INCLUDE
#define KVS__PARALLEL_COORDINATES_RENDERER_H_INCLUDE

#include <kvs/RendererBase>
#include <kvs/Module>
#include <kvs/ColorMap>


namespace kvs
{

class ObjectBase;
class Camera;
class Light;

/*===========================================================================*/
/**
 *  @brief  Parallel coordinates renderer class.
 */
/*===========================================================================*/
class ParallelCoordinatesRenderer : public kvs::RendererBase
{
    kvsModuleName( kvs::ParallelCoordinatesRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::RendererBase );

private:

    int m_top_margin; ///< top margin
    int m_bottom_margin; ///< bottom margin
    int m_left_margin; ///< left margin
    int m_right_margin; ///< right margin
    mutable bool m_enable_anti_aliasing; ///< flag for anti-aliasing (AA)
    mutable bool m_enable_multisample_anti_aliasing; ///< flag for multisample anti-aliasing (MSAA)
    size_t m_active_axis; ///< index of active axis
    kvs::UInt8 m_line_opacity; ///< line opacity
    kvs::Real32 m_line_width; ///< line width
    kvs::ColorMap m_color_map; ///< color map

public:

    ParallelCoordinatesRenderer();

    void setTopMargin( const int top_margin );
    void setBottomMargin( const int bottom_margin );
    void setLeftMargin( const int left_margin );
    void setRightMargin( const int right_margin );
    void enableAntiAliasing( const bool multisample = false ) const;
    void disableAntiAliasing() const;
    void setLineOpacity( const kvs::UInt8 opacity );
    void setLineWidth( const kvs::Real32 width );
    void setColorMap( const kvs::ColorMap& color_map );
    void selectAxis( const size_t index );

    int topMargin() const;
    int bottomMargin() const;
    int leftMargin() const;
    int rightMargin() const;
    size_t activeAxis() const;
    kvs::UInt8 lineOpacity() const;
    kvs::Real32 lineWidth() const;

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
};

} // end of namespace kvs

#endif // KVS__PARALLEL_COORDINATES_RENDERER_H_INCLUDE
