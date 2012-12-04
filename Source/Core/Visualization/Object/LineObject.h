/*****************************************************************************/
/**
 *  @file   LineObject.h
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
#ifndef KVS__LINE_OBJECT_H_INCLUDE
#define KVS__LINE_OBJECT_H_INCLUDE

#include <kvs/GeometryObjectBase>
#include <kvs/ClassName>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/RGBColor>
#include <kvs/Module>
#include <kvs/Deprecated>


namespace kvs
{

class PolygonObject;

/*===========================================================================*/
/**
 *  @brief  Line object class.
 */
/*===========================================================================*/
class LineObject : public kvs::GeometryObjectBase
{
    kvsClassName( kvs::LineObject );
    kvsModuleCategory( Object );
    kvsModuleBaseClass( kvs::GeometryObjectBase );

public:

    enum LineType
    {
        Strip,
        Uniline,
        Polyline,
        Segment,
        UnknownLineType
    };

    enum ColorType
    {
        VertexColor,
        LineColor,
        UnknownColorType
    };

protected:

    LineType m_line_type; ///< line type
    ColorType m_color_type; ///< line color type
    kvs::ValueArray<kvs::UInt32> m_connections; ///< connection array
    kvs::ValueArray<kvs::Real32> m_sizes; ///< size array

public:

    static kvs::LineObject* DownCast( kvs::ObjectBase* object );
    static const kvs::LineObject* DownCast( const kvs::ObjectBase* object );

public:

    LineObject();
    explicit LineObject( const kvs::PolygonObject& polygon );

    friend std::ostream& operator << ( std::ostream& os, const LineObject& object );

    void shallowCopy( const LineObject& object );
    void deepCopy( const LineObject& object );
    void clear();

    void setLineType( const LineType line_type );
    void setColorType( const ColorType color_type );
    void setConnections( const kvs::ValueArray<kvs::UInt32>& connections );
    void setColor( const kvs::RGBColor& color );
    void setSizes( const kvs::ValueArray<kvs::Real32>& sizes );
    void setSize( const kvs::Real32 size );

    BaseClass::GeometryType geometryType() const;
    LineType lineType() const;
    ColorType colorType() const;
    size_t nconnections() const;
    size_t nsizes() const;

    const kvs::Vector2ui connection( const size_t index = 0 ) const;
    kvs::Real32 size( const size_t index = 0 ) const;

    const kvs::ValueArray<kvs::UInt32>& connections() const;
    const kvs::ValueArray<kvs::Real32>& sizes() const;

public:
    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::Real32>& sizes,
                        const LineType line_type,
                        const ColorType color_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setLineType( line_type );
        this->setColorType( color_type );
        this->setConnections( connections );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::Real32 size,
                        const LineType line_type,
                        const ColorType color_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setLineType( line_type );
        this->setColorType( color_type );
        this->setConnections( connections );
        this->setSize( size );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::Real32>& sizes,
                        const LineType line_type ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setLineType( line_type );
        this->setColorType( LineObject::LineColor );
        this->setConnections( connections );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt32>& connections,
                        const kvs::RGBColor& color,
                        const kvs::Real32 size,
                        const LineType line_type ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setLineType( line_type );
        this->setColorType( LineObject::LineColor );
        this->setConnections( connections );
        this->setSize( size );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::Real32>& sizes,
                        const ColorType color_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setLineType( LineObject::Strip );
        this->setColorType( color_type );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::Real32 size,
                        const ColorType color_type ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setLineType( LineObject::Strip );
        this->setColorType( color_type );
        this->setSize( size );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::Real32>& sizes ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setLineType( LineObject::Strip );
        this->setColorType( LineObject::LineColor );
        this->setSizes( sizes );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::Real32 size ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setLineType( LineObject::Strip );
        this->setColorType( LineObject::LineColor );
        this->setSize( size );
    }

    KVS_DEPRECATED( LineObject(
                        const kvs::ValueArray<kvs::Real32>& coords ) )
    {
        this->setCoords( coords );
        this->setColor( kvs::RGBColor( 255, 255, 255 ) );
        this->setLineType( LineObject::Strip );
        this->setColorType( LineObject::LineColor );
        this->setSize( 1.0f );
    }

};

} // end of namespace kvs

#endif // KVS__LINE_OBJECT_H_INCLUDE
