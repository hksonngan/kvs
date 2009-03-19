/*****************************************************************************/
/**
 *  @file   StructuredVolumeExporter.cpp
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
#include "StructuredVolumeExporter.h"
#include <kvs/ObjectBase>
#include <kvs/VolumeObjectBase>
#include <kvs/StructuredVolumeObject>


namespace
{

/*===========================================================================*/
/**
 *  @brief  Casts to a pointer to the structured volume object.
 *  @param  object [in] pointer to the object
 *  @return pointer to the structured volume object
 */
/*===========================================================================*/
const kvs::StructuredVolumeObject* CastToStructuredVolumeObject( const kvs::ObjectBase* object )
{
    if ( object->objectType() != kvs::ObjectBase::Volume )
    {
        kvsMessageError("Input object is not a volumetry object.");
        return( NULL );
    }

    const kvs::VolumeObjectBase* volume =
        reinterpret_cast<const kvs::VolumeObjectBase*>( object );
    if ( volume->volumeType() != kvs::VolumeObjectBase::Structured )
    {
        kvsMessageError("Input object is not a structured volume object.");
        return( NULL );
    }

    return( reinterpret_cast<const kvs::StructuredVolumeObject*>( volume ) );
}

} // end of namespace


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a KVSMLObjectStructuredVolume data from given object.
 *  @param  object [in] pointer to the structured volume object
 */
/*===========================================================================*/
StructuredVolumeExporter<kvs::KVSMLObjectStructuredVolume>::StructuredVolumeExporter(
    const kvs::StructuredVolumeObject* object )
{
    this->exec( object );
}

/*===========================================================================*/
/**
 *  @brief  Exports object to a KVSMLObjectStructuredVolume data.
 *  @param  object [in] pointer to the structured volume object
 */
/*===========================================================================*/
kvs::KVSMLObjectStructuredVolume* StructuredVolumeExporter<kvs::KVSMLObjectStructuredVolume>::exec(
    const kvs::ObjectBase* object )
{
    // Cast to the structured volume object.
    const kvs::StructuredVolumeObject* volume = ::CastToStructuredVolumeObject( object );
    if ( !volume )
    {
        kvsMessageError("Cannot cast to a structured volume object from the given object.");
        return( NULL );
    }

    // Check the grid type of the given structured volume object.
    switch ( volume->gridType() )
    {
    case kvs::StructuredVolumeObject::UnknownGridType:
    {
        kvsMessageError("Unknown grid type.");
        break;
    }
    case kvs::StructuredVolumeObject::Uniform:
    {
        this->setGridType("uniform");
        break;
    }
/*
    case kvs::StructuredVolumeObject::Rectilinear:
        this->setGridType("rectilinear");
        break;
    case kvs::StructuredVolumeObject::Curvilinear:
        this->setGridType("curvilinear");
        break;
*/
    default:
    {
        kvsMessageError("'uniform' grid type is only supported.");
        break;
    }
    }

    this->setVeclen( volume->veclen() );
    this->setResolution( volume->resolution() );
    this->setValues( volume->values() );

    return( this );
}

} // end of namespace kvs
