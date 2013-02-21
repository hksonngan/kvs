/*****************************************************************************/
/**
 *  @file   ScatterPlotMatrixRenderer.h
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
#ifndef KVS__SCATTER_PLOT_MATRIX_RENDERER_H_INCLUDE
#define KVS__SCATTER_PLOT_MATRIX_RENDERER_H_INCLUDE

#include <kvs/RendererBase>
#include <kvs/Module>
#include <kvs/RGBColor>
#include <kvs/RGBAColor>
#include <kvs/ColorMap>


namespace kvs
{

class ObjectBase;
class Camera;
class Light;

/*===========================================================================*/
/**
 *  @brief  ScatterPlotMatrixRenderer class.
 */
/*===========================================================================*/
class ScatterPlotMatrixRenderer : public kvs::RendererBase
{
    kvsModuleName( kvs::ScatterPlotMatrixRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::RendererBase );

protected:

    int m_top_margin; ///< top margin
    int m_bottom_margin; ///< bottom margin
    int m_left_margin; ///< left margin
    int m_right_margin; ///< right margin
    int m_margin; ///< margin
    int m_active_axis; ///< active axis
    kvs::RGBColor m_point_color; ///< point color
    kvs::UInt8 m_point_opacity; ///< point opacity
    kvs::Real32 m_point_size; ///< point size
    kvs::ColorMap m_color_map; ///< color map
    kvs::RGBAColor m_background_color; ///< background color

public:

    ScatterPlotMatrixRenderer();

    void setTopMargin( const int top_margin );
    void setBottomMargin( const int bottom_margin );
    void setLeftMargin( const int left_margin );
    void setRightMargin( const int right_margin );
    void setMargin( const int margin );
    void setPointColor( const kvs::RGBColor point_color );
    void setPointOpacity( const kvs::UInt8 point_opacity );
    void setPointSize( const kvs::Real32 point_size );
    void setColorMap( const kvs::ColorMap& color_map );
    void setBackgroundColor( const kvs::RGBAColor background_color );
    void selectAxis( const int index );

    const int topMargin() const;
    const int bottomMargin() const;
    const int leftMargin() const;
    const int rightMargin() const;
    const int margin() const;
    const int activeAxis() const;
    const kvs::UInt8 pointOpacity() const;
    const kvs::Real32 pointSize() const;
    const kvs::ColorMap& colorMap() const;
    const kvs::RGBAColor backgroundColor() const;

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );
};

} // end of namespace kvs

#endif // KVS__SCATTER_PLOT_MATRIX_RENDERER_H_INCLUDE
