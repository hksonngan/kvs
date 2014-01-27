/*****************************************************************************/
/**
 *  @file   GlyphBase.h
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
#ifndef KVS__GLYPH_BASE_H_INCLUDE
#define KVS__GLYPH_BASE_H_INCLUDE

#include <kvs/RendererBase>
#include <kvs/ValueArray>
#include <kvs/Vector3>
#include <kvs/TransferFunction>


namespace kvs
{

class VolumeObjectBase;
class StructuredVolumeObject;

/*===========================================================================*/
/**
 *  @brief  Glyph renderer base class.
 */
/*===========================================================================*/
class GlyphBase : public kvs::RendererBase
{
    kvsModule( Renderer, kvs::GlyphBase, kvs::RendererBase );

public:

    enum SizeMode
    {
        SizeByDefault = 0,
        SizeByMagnitude
    };

    enum DirectionMode
    {
        DirectionByDefault = 0,
        DirectionByNormal
    };

    enum ColorMode
    {
        ColorByDefault = 0,
        ColorByMagnitude
    };

    enum OpacityMode
    {
        OpacityByDefault = 0,
        OpacityByMagnitude
    };

private:

    SizeMode m_size_mode; ///< size mode
    DirectionMode m_direction_mode; ///< direction mode
    ColorMode m_color_mode; ///< color mode
    OpacityMode m_opacity_mode; ///< opacity mode
    kvs::ValueArray<kvs::Real32> m_coords; ///< coordinate value array
    kvs::ValueArray<kvs::Real32> m_sizes; ///< size value array
    kvs::ValueArray<kvs::Real32> m_directions; ///< direction vector array
    kvs::ValueArray<kvs::UInt8> m_colors; ///< color value array
    kvs::ValueArray<kvs::UInt8> m_opacities; ///< opacity value array
    kvs::Vector3f m_scale; ///< scaling vector
    kvs::TransferFunction m_tfunc; ///< transfer function

public:

    GlyphBase();
    virtual ~GlyphBase();

    virtual void exec( kvs::ObjectBase* object, kvs::Camera* camera = NULL, kvs::Light* light = NULL ) = 0;

    void setSizeMode( const SizeMode mode );
    void setDirectionMode( const DirectionMode mode );
    void setColorMode( const ColorMode mode );
    void setOpacityMode( const OpacityMode mode );
    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );
    void setSizes( const kvs::ValueArray<kvs::Real32>& sizes );
    void setDirections( const kvs::ValueArray<kvs::Real32>& directions );
    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );
    void setOpacities( const kvs::ValueArray<kvs::UInt8>& opacities );
    void setScale( const kvs::Real32 scale );
    void setScale( const kvs::Vector3f& scale );
    void setTransferFunction( const kvs::TransferFunction& tfunc );

    SizeMode sizeMode() const;
    DirectionMode directionMode() const;
    ColorMode colorMode() const;
    OpacityMode opacityMode() const;
    const kvs::ValueArray<kvs::Real32>& coords() const;
    const kvs::ValueArray<kvs::Real32>& sizes() const;
    const kvs::ValueArray<kvs::Real32>& directions() const;
    const kvs::ValueArray<kvs::UInt8>& colors() const;
    const kvs::ValueArray<kvs::UInt8>& opacities() const;
    const kvs::Vector3f& scale() const;
    const kvs::TransferFunction& transferFunction() const;

protected:

    void transform( const kvs::Vector3f& position, const kvs::Real32 size );
    void transform( const kvs::Vector3f& position, const kvs::Vector3f& direction, const kvs::Real32 size );
    void calculateCoords( const kvs::VolumeObjectBase* volume );
    void calculateCoords( const kvs::StructuredVolumeObject* volume );
    void calculateUniformCoords( const kvs::StructuredVolumeObject* volume );
    void calculateRectilinearCoords( const kvs::StructuredVolumeObject* volume );
    template <typename T> void calculateSizes( const kvs::VolumeObjectBase* volume );
    template <typename T> void calculateDirections( const kvs::VolumeObjectBase* volume );
    template <typename T> void calculateColors( const kvs::VolumeObjectBase* volume );
    template <typename T> void calculateOpacities( const kvs::VolumeObjectBase* volume );
};

} // end of namespace kvs

#endif // KVS__GLYPH_BASE_H_INCLUDE
