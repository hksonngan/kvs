/*****************************************************************************/
/**
 *  @file   LineExporter.cpp
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
#include "LineExporter.h"
#include <kvs/Message>


namespace
{

const kvs::LineObject* CastToLineObject( const kvs::ObjectBase* object_base )
{
    if ( object_base->objectType() != kvs::ObjectBase::Geometry )
    {
        kvsMessageError("Input object is not a geometry object.");
        return( NULL );
    }

    const kvs::GeometryObjectBase* geometry =
        reinterpret_cast<const kvs::GeometryObjectBase*>( object_base );
    if ( geometry->geometryType() != kvs::GeometryObjectBase::Line )
    {
        kvsMessageError("Input object is not a line object.");
        return( NULL );
    }

    return( reinterpret_cast<const kvs::LineObject*>( geometry ) );
}

} // end of namespace

namespace kvs
{

LineExporter<kvs::KVSMLObjectLine>::LineExporter( const kvs::LineObject* line_object )
{
    this->exec( line_object );
}

kvs::KVSMLObjectLine* LineExporter<kvs::KVSMLObjectLine>::exec( const kvs::ObjectBase* object_base )
{
    const kvs::LineObject* line_object = ::CastToLineObject( object_base );
    if ( !line_object )
    {
        kvsMessageError("Cannot cast to a line object from the given object.");
        return( NULL );
    }

    switch ( line_object->lineType() )
    {
    case kvs::LineObject::Strip: this->setLineType( "strip" ); break;
    case kvs::LineObject::Uniline: this->setLineType( "uniline" ); break;
    case kvs::LineObject::Polyline: this->setLineType( "polyline" ); break;
    case kvs::LineObject::Segment:this->setLineType( "segment" ); break;
    default: break;
    }

    switch ( line_object->colorType() )
    {
    case kvs::LineObject::VertexColor: this->setColorType( "vertex" ); break;
    case kvs::LineObject::LineColor: this->setColorType( "line" ); break;
    default: break;
    }

    this->setCoords( line_object->coords() );
    this->setColors( line_object->colors() );
    this->setConnections( line_object->connections() );
    this->setSizes( line_object->sizes() );

    return( this );
}

} // end of namespace kvs
