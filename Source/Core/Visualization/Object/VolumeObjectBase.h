/****************************************************************************/
/**
 *  @file VolumeObjectBase.h
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
#include <kvs/ClassName>
#include <kvs/ObjectBase>
#include <kvs/Value>
#include <kvs/ValueArray>
#include <kvs/AnyValueArray>
#include <kvs/Math>
#include <kvs/Deprecated>


namespace kvs
{

/*==========================================================================*/
/**
 *  VolumeObjectBase.
 */
/*==========================================================================*/
class VolumeObjectBase : public kvs::ObjectBase
{
    kvsClassName( kvs::VolumeObjectBase );

public:

    typedef kvs::ObjectBase BaseClass;
    typedef kvs::ValueArray<float> Coords;
    typedef kvs::AnyValueArray Values;

public:

    enum VolumeType
    {
        Structured = 0, ///< Structured volume.
        Unstructured,   ///< Unstructured volume.
    };

    enum GridType
    {
        UnknownGridType = 0,
        Uniform,             ///< Uniform grid.
        Rectilinear,         ///< Rectilinear grid.
        Curvilinear,         ///< Curvilinear grid.
        Irregular,           ///< Irregular grid.
    };

    enum CellType
    {
        UnknownCellType     = 0,
        Tetrahedra          = 4,  ///< Tetrahedral cell.
        Hexahedra           = 8,  ///< Hexahedral cell.
        QuadraticTetrahedra = 10, ///< Quadratic tetrahedral cell.
        QuadraticHexahedra  = 20, ///< Quadratic Hexahedral cell.
        Pyramid             = 5,  ///< Pyramidal cell.
        Point               = 1   ///< Point.
    };

private:

    std::string m_label; ///< data label
    size_t m_veclen; ///< Vector length.
    Coords m_coords; ///< Coordinate array.
    Values m_values; ///< Value array.
    mutable bool m_has_min_max_values; ///< Whether includes min/max values or not.
    mutable kvs::Real64 m_min_value; ///< Minimum field value.
    mutable kvs::Real64 m_max_value; ///< Maximum field value.

public:

    static kvs::VolumeObjectBase* DownCast( kvs::ObjectBase* object );
    static const kvs::VolumeObjectBase* DownCast( const kvs::ObjectBase* object );

public:

    VolumeObjectBase();

    friend std::ostream& operator << ( std::ostream& os, const VolumeObjectBase& object );

    void setLabel( const std::string& label );
    void setVeclen( const size_t veclen );
    void setCoords( const Coords& values );
    void setValues( const Values& values );
    void setMinMaxValues( const kvs::Real64 min_value, const kvs::Real64 max_value ) const;

    const std::string& label() const;
    size_t veclen() const;
    const Coords& coords() const;
    const Values& values() const;
    bool hasMinMaxValues() const;
    kvs::Real64 minValue() const;
    kvs::Real64 maxValue() const;

    ObjectType objectType() const;
    virtual VolumeType volumeType() const = 0;
    virtual GridType gridType() const = 0;
    virtual CellType cellType() const = 0;
    virtual size_t numberOfNodes() const = 0;
    virtual size_t numberOfCells() const = 0;
    void updateMinMaxValues() const;

    void shallowCopy( const VolumeObjectBase& object );
    void deepCopy( const VolumeObjectBase& object );

private:

    template<typename T>
    void calculate_min_max_values() const;

public:
    KVS_DEPRECATED( VolumeObjectBase(
                        const size_t     veclen,
                        const Coords&    coords,
                        const Values&    values ) )
    {
        m_has_min_max_values = false;
        m_min_value = 0.0;
        m_max_value = 0.0;
        this->setVeclen( veclen );
        this->setCoords( coords );
        this->setValues( values );
    }
};

template<typename T>
void VolumeObjectBase::calculate_min_max_values() const
{
    KVS_ASSERT( m_values.size() != 0 );
    KVS_ASSERT( m_values.size() == this->veclen() * this->numberOfNodes() );

    const T*       value = reinterpret_cast<const T*>( m_values.data() );
    const T* const end   = value + this->numberOfNodes() * m_veclen;

    if ( m_veclen == 1 )
    {
        T min_value = *value;
        T max_value = *value;

        while ( value < end )
        {
            min_value = kvs::Math::Min( *value, min_value );
            max_value = kvs::Math::Max( *value, max_value );
            ++value;
        }

        this->setMinMaxValues(
            static_cast<kvs::Real64>( min_value ),
            static_cast<kvs::Real64>( max_value ) );
    }
    else
    {
        kvs::Real64 min_value = kvs::Value<kvs::Real64>::Max();
        kvs::Real64 max_value = kvs::Value<kvs::Real64>::Min();

        const size_t veclen = m_veclen;

        while ( value < end )
        {
            kvs::Real64 magnitude = 0.0;
            for ( size_t i = 0; i < veclen; ++i )
            {
                magnitude += static_cast<kvs::Real64>( ( *value ) * ( *value ) );
                ++value;
            }

            min_value = kvs::Math::Min( magnitude, min_value );
            max_value = kvs::Math::Max( magnitude, max_value );
        }

        this->setMinMaxValues( std::sqrt( min_value ), std::sqrt( max_value ) );
    }
}

} // end of namespace kvs

#endif // KVS__VOLUME_OBJECT_BASE_H_INCLUDE
