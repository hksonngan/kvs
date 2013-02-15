/****************************************************************************/
/**
 *  @file UnstructuredVolumeObject.h
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
#ifndef KVS__UNSTRUCTURED_VOLUME_OBJECT_H_INCLUDE
#define KVS__UNSTRUCTURED_VOLUME_OBJECT_H_INCLUDE

#include <ostream>
#include <kvs/Module>
#include <kvs/VolumeObjectBase>
#include <kvs/Indent>
#include <kvs/Deprecated>


namespace kvs
{

/*==========================================================================*/
/**
 *  Unstructured volume object class.
 */
/*==========================================================================*/
class UnstructuredVolumeObject : public kvs::VolumeObjectBase
{
    kvsModuleName( kvs::UnstructuredVolumeObject );
    kvsModuleCategory( Object );
    kvsModuleBaseClass( kvs::VolumeObjectBase );

public:

    typedef kvs::ValueArray<kvs::UInt32> Connections;

private:

    CellType m_cell_type; ///< Cell type.
    size_t m_nnodes; ///< Number of nodes.
    size_t m_ncells; ///< Number of cells.
    Connections m_connections; ///< Connection ( Node ID ) array.

public:

    static kvs::UnstructuredVolumeObject* DownCast( kvs::ObjectBase* object );
    static const kvs::UnstructuredVolumeObject* DownCast( const kvs::ObjectBase* object );

public:

    UnstructuredVolumeObject();

    void shallowCopy( const UnstructuredVolumeObject& object );
    void deepCopy( const UnstructuredVolumeObject& object );
    void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    void setCellType( const CellType cell_type );
    void setNumberOfNodes( const size_t nnodes );
    void setNumberOfCells( const size_t ncells );
    void setConnections( const Connections& connections );

    VolumeType volumeType() const;
    GridType gridType() const;
    CellType cellType() const;
    size_t numberOfNodes() const;
    size_t numberOfCells() const;
    const Connections& connections() const;

    void updateMinMaxCoords();

private:

    void calculate_min_max_coords();

public:
    KVS_DEPRECATED( UnstructuredVolumeObject(
                        const CellType cell_type,
                        const size_t nnodes,
                        const size_t ncells,
                        const size_t veclen,
                        const Coords& coords,
                        const Connections& connections,
                        const Values& values ) )
    {
        this->setVeclen( veclen );
        this->setCoords( coords );
        this->setValues( values );
        this->setCellType( cell_type );
        this->setNumberOfNodes( nnodes );
        this->setNumberOfCells( ncells );
        this->setConnections( connections );
    }

    KVS_DEPRECATED( void setNNodes( const size_t nnodes ) ) { this->setNumberOfNodes( nnodes ); }
    KVS_DEPRECATED( void setNCells( const size_t ncells ) ) { this->setNumberOfCells( ncells ); }
    KVS_DEPRECATED( size_t nnodes() const ) { return this->numberOfNodes(); }
    KVS_DEPRECATED( size_t ncells() const ) { return this->numberOfCells(); }
    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const UnstructuredVolumeObject& object ) );
};

} // end of namespace kvs

#endif // KVS__UNSTRUCTURED_VOLUME_OBJECT_H_INCLUDE
