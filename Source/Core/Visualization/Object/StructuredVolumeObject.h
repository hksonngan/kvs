/****************************************************************************/
/**
 *  @file StructuredVolumeObject.h
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
#ifndef KVS__STRUCTURED_VOLUME_OBJECT_H_INCLUDE
#define KVS__STRUCTURED_VOLUME_OBJECT_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/VolumeObjectBase>
#include <kvs/Deprecated>


namespace kvs
{

/*==========================================================================*/
/**
 *  StructuredVolumeObject.
 */
/*==========================================================================*/
class StructuredVolumeObject : public kvs::VolumeObjectBase
{
    kvsClassName( kvs::StructuredVolumeObject );
    kvsModuleCategory( Object );
    kvsModuleBaseClass( kvs::VolumeObjectBase );

private:

    GridType m_grid_type;  ///< Grid type.
    kvs::Vector3ui m_resolution; ///< Node resolution.

public:

    static kvs::StructuredVolumeObject* DownCast( kvs::ObjectBase* object );
    static const kvs::StructuredVolumeObject* DownCast( const kvs::ObjectBase* object );

public:

    StructuredVolumeObject();

    friend std::ostream& operator << ( std::ostream& os, const StructuredVolumeObject& object );

    void shallowCopy( const StructuredVolumeObject& object );
    void deepCopy( const StructuredVolumeObject& object );

    void setGridType( const GridType grid_type );
    void setResolution( const kvs::Vector3ui& resolution );

    VolumeType volumeType() const;
    GridType gridType() const;
    CellType cellType() const;
    const kvs::Vector3ui& resolution() const;
    size_t numberOfNodesPerLine() const;
    size_t numberOfNodesPerSlice() const;
    size_t numberOfNodes() const;
    size_t numberOfCells() const;

    void updateMinMaxCoords();

private:

    void calculate_min_max_coords();

public:
    KVS_DEPRECATED( StructuredVolumeObject(
                        const kvs::Vector3ui& resolution,
                        const size_t veclen,
                        const Values& values ) )
    {
        this->setVeclen( veclen );
        this->setValues( values );
        this->setGridType( Uniform );
        this->setResolution( resolution );
    }

    KVS_DEPRECATED( StructuredVolumeObject(
                        const GridType grid_type,
                        const kvs::Vector3ui& resolution,
                        const size_t veclen,
                        const Coords& coords,
                        const Values& values ) )
    {
        this->setVeclen( veclen );
        this->setCoords( coords );
        this->setValues( values );
        this->setGridType( grid_type );
        this->setResolution( resolution );
    }

    KVS_DEPRECATED( size_t nnodesPerLine() const ) { return this->numberOfNodesPerLine(); }
    KVS_DEPRECATED( size_t nnodesPerSlice() const ) { return this->numberOfNodesPerSlice(); }
    KVS_DEPRECATED( size_t nnodes() const ) { return this->numberOfNodes(); }
};

} // end of namespace kvs

#endif // KVS__STRUCTURED_VOLUME_OBJECT_H_INCLUDE
