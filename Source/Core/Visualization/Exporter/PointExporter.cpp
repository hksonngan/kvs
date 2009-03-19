/*****************************************************************************/
/**
 *  @file   PointExporter.cpp
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
#include "PointExporter.h"
#include <kvs/Message>


namespace
{

const kvs::PointObject* CastToPointObject( const kvs::ObjectBase* object_base )
{
    if ( object_base->objectType() != kvs::ObjectBase::Geometry )
    {
        kvsMessageError("Input object is not a geometry object.");
        return( NULL );
    }

    const kvs::GeometryObjectBase* geometry =
        reinterpret_cast<const kvs::GeometryObjectBase*>( object_base );
    if ( geometry->geometryType() != kvs::GeometryObjectBase::Point )
    {
        kvsMessageError("Input object is not a point object.");
        return( NULL );
    }

    return( reinterpret_cast<const kvs::PointObject*>( geometry ) );
}

} // end of namespace

namespace kvs
{

PointExporter<kvs::KVSMLObjectPoint>::PointExporter( const kvs::PointObject* point_object )
{
    this->exec( point_object );
}

kvs::KVSMLObjectPoint* PointExporter<kvs::KVSMLObjectPoint>::exec( const kvs::ObjectBase* object_base )
{
    const kvs::PointObject* point_object = ::CastToPointObject( object_base );
    if ( !point_object )
    {
        kvsMessageError("Cannot cast to a point object from the given object.");
        return( NULL );
    }

    this->setCoords( point_object->coords() );
    this->setColors( point_object->colors() );
    this->setNormals( point_object->normals() );
    this->setSizes( point_object->sizes() );

    return( this );
}

} // end of namespace kvs
