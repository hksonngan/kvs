/*****************************************************************************/
/**
 *  @file   UnstructuredVolumeExporter.cpp
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "UnstructuredVolumeExporter.h"
#include <kvs/ObjectBase>
#include <kvs/VolumeObjectBase>
#include <kvs/UnstructuredVolumeObject>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Casts to a pointer to the unstructured volume object.
 *  @param  object [in] pointer to the object
 *  @return pointer to the unstructured volume object
 */
/*===========================================================================*/
const kvs::UnstructuredVolumeObject* CastToUnstructuredVolumeObject( const kvs::ObjectBase* object )
{
    if ( object->objectType() != kvs::ObjectBase::Volume )
    {
        kvsMessageError("Input object is not a volumetry object.");
        return( NULL );
    }

    const kvs::VolumeObjectBase* volume =
        reinterpret_cast<const kvs::VolumeObjectBase*>( object );
    if ( volume->volumeType() != kvs::VolumeObjectBase::Unstructured )
    {
        kvsMessageError("Input object is not a structured volume object.");
        return( NULL );
    }

    return( reinterpret_cast<const kvs::UnstructuredVolumeObject*>( volume ) );
}

} // end of namespace


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a KVSMLObjectUnstructuredVolume data from given object.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
UnstructuredVolumeExporter<kvs::KVSMLObjectUnstructuredVolume>::UnstructuredVolumeExporter(
    const kvs::UnstructuredVolumeObject* object )
{
    this->exec( object );
}

/*===========================================================================*/
/**
 *  @brief  Exports to a KVSMLObjectUnstructuredVolume data.
 *  @param  object [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
kvs::KVSMLObjectUnstructuredVolume* UnstructuredVolumeExporter<kvs::KVSMLObjectUnstructuredVolume>::exec(
    const kvs::ObjectBase* object )
{
    // Cast to the unstructured volume object.
    const kvs::UnstructuredVolumeObject* volume = ::CastToUnstructuredVolumeObject( object );
    if ( !volume )
    {
        kvsMessageError("Cannot cast to a unstructured volume object from the given object.");
        return( NULL );
    }

    // Check the cell type of the given unstructured volume object.
    switch ( volume->cellType() )
    {
    case kvs::UnstructuredVolumeObject::UnknownCellType:
    {
        kvsMessageError("Unknown cell type.");
        break;
    }
    case kvs::UnstructuredVolumeObject::Tetrahedra:
    {
        this->setCellType("tetrahedra");
        break;
    }
    case kvs::UnstructuredVolumeObject::QuadraticTetrahedra:
    {
        this->setCellType("quadratic tetrahedra");
        break;
    }
    case kvs::UnstructuredVolumeObject::Hexahedra:
    {
        this->setCellType("hexahedra");
        break;
    }
    case kvs::UnstructuredVolumeObject::QuadraticHexahedra:
    {
        this->setCellType("quadratic hexahedra");
        break;
    }
    default:
    {
        kvsMessageError("Not supported cell type.");
        break;
    }
    }

    this->setVeclen( volume->veclen() );
    this->setNNodes( volume->nnodes() );
    this->setNCells( volume->ncells() );
    this->setValues( volume->values() );
    this->setCoords( volume->coords() );
    this->setConnections( volume->connections() );

    return( this );
}

} // end of namespace kvs
