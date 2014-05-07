/****************************************************************************/
/**
 *  @file   VolumeObjectBase.h
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
#ifndef KVS__VOLUME_OBJECT_BASE_H_INCLUDE
#define KVS__VOLUME_OBJECT_BASE_H_INCLUDE

#include <string>
#include <ostream>
#include <kvs/ObjectBase>
#include <kvs/Value>
#include <kvs/ValueArray>
#include <kvs/AnyValueArray>
#include <kvs/Math>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  VolumeObjectBase.
 */
/*==========================================================================*/
class VolumeObjectBase : public kvs::ObjectBase
{
    kvsModule( kvs::VolumeObjectBase, Object );

public:

    typedef kvs::ObjectBase BaseClass;
    typedef kvs::ValueArray<float> Coords;
    typedef kvs::AnyValueArray Values;

public:

    enum VolumeType
    {
        Structured = 0, ///< Structured volume.
        Unstructured,   ///< Unstructured volume.
        UnknownVolumeType ///< Unknow volume type.
    };

    enum GridType
    {
        UnknownGridType = 0, ///< Unknown grid type.
        Uniform,             ///< Uniform grid.
        Rectilinear,         ///< Rectilinear grid.
        Curvilinear,         ///< Curvilinear grid.
        Irregular,           ///< Irregular grid.
    };

    enum CellType
    {
        UnknownCellType     = 0,  ///< Unknown cell type.
        Tetrahedra          = 4,  ///< Tetrahedral cell.
        Hexahedra           = 8,  ///< Hexahedral cell.
        QuadraticTetrahedra = 10, ///< Quadratic tetrahedral cell.
        QuadraticHexahedra  = 20, ///< Quadratic Hexahedral cell.
        Pyramid             = 5,  ///< Pyramidal cell.
        Point               = 1   ///< Point.
    };

private:

    VolumeType m_volume_type; ///< volume type
    GridType m_grid_type; ///< grid type
    CellType m_cell_type; ///< cell type
    std::string m_label; ///< data label
    size_t m_veclen; ///< Vector length.
    Coords m_coords; ///< Coordinate array
    Values m_values; ///< Value array
    mutable bool m_has_min_max_values; ///< Whether includes min/max values or not
    mutable kvs::Real64 m_min_value; ///< Minimum field value
    mutable kvs::Real64 m_max_value; ///< Maximum field value

public:

    VolumeObjectBase();

    void shallowCopy( const VolumeObjectBase& object );
    void deepCopy( const VolumeObjectBase& object );
    virtual void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    void setLabel( const std::string& label ) { m_label = label; }
    void setVeclen( const size_t veclen ) { m_veclen = veclen; }
    void setCoords( const Coords& coords ) { m_coords = coords; }
    void setValues( const Values& values ) { m_values = values; }
    void setMinMaxValues( const kvs::Real64 min_value, const kvs::Real64 max_value ) const;

    const std::string& label() const { return m_label; }
    size_t veclen() const { return m_veclen; }
    const Coords& coords() const { return m_coords; }
    const Values& values() const { return m_values; }
    bool hasMinMaxValues() const { return m_has_min_max_values; }
    kvs::Real64 minValue() const { return m_min_value; }
    kvs::Real64 maxValue() const { return m_max_value; }

    VolumeType volumeType() const { return m_volume_type; }
    GridType gridType() const { return m_grid_type; }
    CellType cellType() const { return m_cell_type; }
    virtual size_t numberOfNodes() const = 0;
    virtual size_t numberOfCells() const = 0;
    void updateMinMaxValues() const;

protected:

    void setVolumeType( VolumeType volume_type ) { m_volume_type = volume_type; }
    void setGridType( GridType grid_type ) { m_grid_type = grid_type; }
    void setCellType( CellType cell_type ) { m_cell_type = cell_type; }

public:
    KVS_DEPRECATED( VolumeObjectBase(
                        const size_t veclen,
                        const Coords& coords,
                        const Values& values ) )
    {
        m_has_min_max_values = false;
        m_min_value = 0.0;
        m_max_value = 0.0;
        this->setVeclen( veclen );
        this->setCoords( coords );
        this->setValues( values );
    }

    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const VolumeObjectBase& object ) );
};

} // end of namespace kvs

#endif // KVS__VOLUME_OBJECT_BASE_H_INCLUDE
