/*****************************************************************************/
/**
 *  @file   PolygonExporter.h
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
#ifndef KVS__POLYGON_EXPORTER_H_INCLUDE
#define KVS__POLYGON_EXPORTER_H_INCLUDE

#include <kvs/PolygonObject>
#include <kvs/KVSMLObjectPolygon>
#include "ExporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  Polygon exporter class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class PolygonExporter : public kvs::ExporterBase<FileFormatType>
{
public:

    PolygonExporter( const kvs::PolygonObject* object );

    FileFormatType* exec( const kvs::ObjectBase* object );
};

template <typename FileFormatType>
PolygonExporter<FileFormatType>::PolygonExporter( const kvs::PolygonObject* object )
{
    this->exec( object );
}

template <typename FileFormatType>
FileFormatType* PolygonExporter<FileFormatType>::exec( const kvs::ObjectBase* object )
{
    return( NULL );
}

/*===========================================================================*/
/**
 *  Polygon exporter class as KVSMLObjectPoint format.
 */
/*===========================================================================*/
template <>
class PolygonExporter<kvs::KVSMLObjectPolygon> : public kvs::ExporterBase<kvs::KVSMLObjectPolygon>
{
public:

    PolygonExporter( const kvs::PolygonObject* object );

    kvs::KVSMLObjectPolygon* exec( const kvs::ObjectBase* object );
};

} // end of namespace kvs

#endif // KVS__POLYGON_EXPORTER_H_INCLUDE
