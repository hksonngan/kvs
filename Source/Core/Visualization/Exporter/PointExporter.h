/*****************************************************************************/
/**
 *  @file   PointExporter.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__POINT_EXPORTER_H_INCLUDE
#define KVS__POINT_EXPORTER_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/PointObject>
#include <kvs/KVSMLObjectPoint>
#include "ExporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Point exporter class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class PointExporter : public kvs::ExporterBase<FileFormatType>
{
    kvsClassName( kvs::PointExporter );

public:

    PointExporter( const kvs::PointObject* object );

    FileFormatType* exec( const kvs::ObjectBase* object );
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new PointExporter class.
 *  @param  object [in] pointer to a point object
 */
/*===========================================================================*/
template <typename FileFormatType>
PointExporter<FileFormatType>::PointExporter( const kvs::PointObject* object )
{
    this->exec( object );
}

/*===========================================================================*/
/**
 *  @brief  Executes the export process.
 *  @param  base [in] pointer to a object
 */
/*===========================================================================*/
template <typename FileFormatType>
FileFormatType* PointExporter<FileFormatType>::exec( const kvs::ObjectBase* object )
{
    // This method will be specialized for each file format.
    return NULL;
}

/*===========================================================================*/
/**
 *  @brief  Point exporter class as KVSMLObjectPoint format.
 */
/*===========================================================================*/
template <>
class PointExporter<kvs::KVSMLObjectPoint> : public kvs::ExporterBase<kvs::KVSMLObjectPoint>
{
public:

    PointExporter( const kvs::PointObject* object );

    kvs::KVSMLObjectPoint* exec( const kvs::ObjectBase* object );
};

} // end of namespace kvs

#endif // KVS__POINT_EXPORTER_H_INCLUDE
