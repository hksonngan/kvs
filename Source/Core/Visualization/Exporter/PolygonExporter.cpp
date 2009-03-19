/*****************************************************************************/
/**
 *  @file   PolygonExporter.cpp
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
#include "PolygonExporter.h"
#include <kvs/Message>


namespace
{

const kvs::PolygonObject* CastToPolygonObject( const kvs::ObjectBase* object_base )
{
    if ( object_base->objectType() != kvs::ObjectBase::Geometry )
    {
        kvsMessageError("Input object is not a geometry object.");
        return( NULL );
    }

    const kvs::GeometryObjectBase* geometry =
        reinterpret_cast<const kvs::GeometryObjectBase*>( object_base );
    if ( geometry->geometryType() != kvs::GeometryObjectBase::Polygon )
    {
        kvsMessageError("Input object is not a polygon object.");
        return( NULL );
    }

    return( reinterpret_cast<const kvs::PolygonObject*>( geometry ) );
}

} // end of namespace

namespace kvs
{

PolygonExporter<kvs::KVSMLObjectPolygon>::PolygonExporter( const kvs::PolygonObject* polygon_object )
{
    this->exec( polygon_object );
}

kvs::KVSMLObjectPolygon* PolygonExporter<kvs::KVSMLObjectPolygon>::exec( const kvs::ObjectBase* object_base )
{
    const kvs::PolygonObject* polygon_object = ::CastToPolygonObject( object_base );
    if ( !polygon_object )
    {
        kvsMessageError("Cannot cast to a polygon object from the given object.");
        return( NULL );
    }

    switch ( polygon_object->polygonType() )
    {
    case kvs::PolygonObject::Triangle: this->setPolygonType( "triangle" ); break;
    case kvs::PolygonObject::Quadrangle: this->setPolygonType( "quadrangle" ); break;
    default: break;
    }

    switch ( polygon_object->colorType() )
    {
    case kvs::PolygonObject::VertexColor: this->setColorType( "vertex" ); break;
    case kvs::PolygonObject::PolygonColor: this->setColorType( "polygon" ); break;
    default: break;
    }

    switch ( polygon_object->normalType() )
    {
    case kvs::PolygonObject::VertexNormal: this->setNormalType( "vertex" ); break;
    case kvs::PolygonObject::PolygonNormal: this->setNormalType( "polygon" ); break;
    default: break;
    }

    this->setCoords( polygon_object->coords() );
    this->setColors( polygon_object->colors() );
    this->setConnections( polygon_object->connections() );
    this->setNormals( polygon_object->normals() );

    return( this );
}

} // end of namespace kvs
