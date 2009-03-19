/*****************************************************************************/
/**
 *  @file   PointExporter.h
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
#ifndef KVS__POINT_EXPORTER_H_INCLUDE
#define KVS__POINT_EXPORTER_H_INCLUDE

#include <kvs/PointObject>
#include <kvs/KVSMLObjectPoint>
#include "ExporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  Point exporter class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class PointExporter : public kvs::ExporterBase<FileFormatType>
{
public:

    PointExporter( const kvs::PointObject* point_object );

    FileFormatType* exec( const kvs::ObjectBase* object_base );
};

template <typename FileFormatType>
PointExporter<FileFormatType>::PointExporter( const kvs::PointObject* point_object )
{
    this->exec( point_object );
}

template <typename FileFormatType>
FileFormatType* PointExporter<FileFormatType>::exec( const kvs::ObjectBase* object_base )
{
    return( NULL );
}

/*===========================================================================*/
/**
 *  Point exporter class as KVSMLObjectPoint format.
 */
/*===========================================================================*/
template <>
class PointExporter<kvs::KVSMLObjectPoint> : public kvs::ExporterBase<kvs::KVSMLObjectPoint>
{
public:

    PointExporter( const kvs::PointObject* point_object );

    kvs::KVSMLObjectPoint* exec( const kvs::ObjectBase* object_base );
};

} // end of namespace kvs

#endif // KVS__POINT_EXPORTER_H_INCLUDE
