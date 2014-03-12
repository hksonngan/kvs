/*****************************************************************************/
/**
 *  @file   GeometryObjectBase.h
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
#ifndef KVS__GEOMETRY_OBJECT_BASE_H_INCLUDE
#define KVS__GEOMETRY_OBJECT_BASE_H_INCLUDE

#include <ostream>
#include <kvs/Module>
#include <kvs/ObjectBase>
#include <kvs/ValueArray>
#include <kvs/Type>
#include <kvs/Vector3>
#include <kvs/RGBColor>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Geometric object class.
 */
/*===========================================================================*/
class GeometryObjectBase : public kvs::ObjectBase
{
    kvsModule( kvs::GeometryObjectBase, Object );

public:

    typedef kvs::ObjectBase BaseClass;

    enum GeometryType
    {
        Point, ///< point object
        Line, ///< line object
        Polygon, ///< polygon object
    };

private:

    kvs::ValueArray<kvs::Real32> m_coords; ///< vertex array
    kvs::ValueArray<kvs::UInt8> m_colors; ///< color(r,g,b) array
    kvs::ValueArray<kvs::Real32> m_normals; ///< normal array

public:

    GeometryObjectBase();

    void shallowCopy( const GeometryObjectBase& object );
    void deepCopy( const GeometryObjectBase& object );
    void clear();
    virtual void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    void setCoords( const kvs::ValueArray<kvs::Real32>& coords );
    void setColors( const kvs::ValueArray<kvs::UInt8>& colors );
    void setColor( const kvs::RGBColor& color );
    void setNormals( const kvs::ValueArray<kvs::Real32>& normals );

    ObjectType objectType() const;
    virtual GeometryType geometryType() const = 0;
    size_t numberOfVertices() const;
    size_t numberOfColors() const;
    size_t numberOfNormals() const;

    const kvs::Vector3f coord( const size_t index = 0 ) const;
    const kvs::RGBColor color( const size_t index = 0 ) const;
    const kvs::Vector3f normal( const size_t index = 0 ) const;
    const kvs::ValueArray<kvs::Real32>& coords() const;
    const kvs::ValueArray<kvs::UInt8>& colors() const;
    const kvs::ValueArray<kvs::Real32>& normals() const;

    void updateMinMaxCoords();

private:

    void calculate_min_max_coords();

public:
    KVS_DEPRECATED( GeometryObjectBase(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors,
                        const kvs::ValueArray<kvs::Real32>& normals ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
        this->setNormals( normals );
    }

    KVS_DEPRECATED( GeometryObjectBase(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::RGBColor& color,
                        const kvs::ValueArray<kvs::Real32>& normals ) )
    {
        this->setCoords( coords );
        this->setColor( color );
        this->setNormals( normals );
    }

    KVS_DEPRECATED( GeometryObjectBase(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::Real32>& normals ) )
    {
        this->setCoords( coords );
        this->setNormals( normals );
    }

    KVS_DEPRECATED( GeometryObjectBase(
                        const kvs::ValueArray<kvs::Real32>& coords,
                        const kvs::ValueArray<kvs::UInt8>& colors ) )
    {
        this->setCoords( coords );
        this->setColors( colors );
    }

    KVS_DEPRECATED( GeometryObjectBase(
                        const kvs::ValueArray<kvs::Real32>& coords, const kvs::RGBColor& color ) )
    {
        this->setCoords( coords );
        this->setColor( color );
    }

    KVS_DEPRECATED( GeometryObjectBase(
                        const kvs::ValueArray<kvs::Real32>& coords ) )
    {
        this->setCoords( coords );
        this->setColor( kvs::RGBColor( 255, 255, 255 ) );
    }

    KVS_DEPRECATED( size_t nvertices() const ) { return this->numberOfVertices(); }
    KVS_DEPRECATED( size_t ncolors() const ) { return this->numberOfColors(); }
    KVS_DEPRECATED( size_t nnormals() const ) { return this->numberOfNormals(); }
    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const GeometryObjectBase& object ) );
};

} // end of namespace kvs

#endif // KVS__GEOMETRY_OBJECT_BASE_H_INCLUDE
