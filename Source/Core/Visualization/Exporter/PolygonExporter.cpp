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


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new PolygonExporter class for KVSMLObjectPolygon format.
 *  @param  object [in] pointer to the input polygon object
 */
/*===========================================================================*/
PolygonExporter<kvs::KVSMLObjectPolygon>::PolygonExporter( const kvs::PolygonObject* object )
{
    this->exec( object );
}

/*===========================================================================*/
/**
 *  @brief  Executes the export process.
 *  @param  object [in] pointer to the input object
 *  @return pointer to the KVSMLObjectPolygon format
 */
/*===========================================================================*/
kvs::KVSMLObjectPolygon* PolygonExporter<kvs::KVSMLObjectPolygon>::exec( const kvs::ObjectBase* object )
{
    if ( !object )
    {
        m_is_success = false;
        kvsMessageError("Input object is NULL.");
        return( NULL );
    }

    const kvs::PolygonObject* polygon = kvs::PolygonObject::DownCast( object );
    if ( !polygon )
    {
        m_is_success = false;
        kvsMessageError("Input object is not polygon object.");
        return( NULL );
    }

    switch ( polygon->polygonType() )
    {
    case kvs::PolygonObject::Triangle: this->setPolygonType( "triangle" ); break;
    case kvs::PolygonObject::Quadrangle: this->setPolygonType( "quadrangle" ); break;
    default: break;
    }

    switch ( polygon->colorType() )
    {
    case kvs::PolygonObject::VertexColor: this->setColorType( "vertex" ); break;
    case kvs::PolygonObject::PolygonColor: this->setColorType( "polygon" ); break;
    default: break;
    }

    switch ( polygon->normalType() )
    {
    case kvs::PolygonObject::VertexNormal: this->setNormalType( "vertex" ); break;
    case kvs::PolygonObject::PolygonNormal: this->setNormalType( "polygon" ); break;
    default: break;
    }

    this->setCoords( polygon->coords() );
    this->setColors( polygon->colors() );
    this->setConnections( polygon->connections() );
    this->setNormals( polygon->normals() );
    this->setOpacities( polygon->opacities() );

    return( this );
}

} // end of namespace kvs
