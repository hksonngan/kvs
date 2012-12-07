/*****************************************************************************/
/**
 *  @file   PolygonExporter.h
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
#ifndef KVS__POLYGON_EXPORTER_H_INCLUDE
#define KVS__POLYGON_EXPORTER_H_INCLUDE

#include <kvs/PolygonObject>
#include <kvs/KVSMLObjectPolygon>
#include <kvs/Stl>
#include <kvs/Ply>
#include "ExporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Polygon exporter class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class PolygonExporter : public kvs::ExporterBase<FileFormatType>
{
    kvsModuleName( kvs::PolygonExporter );
    kvsModuleBaseClass( kvs::ExporterBase<FileFormatType> );

public:

    PolygonExporter( const kvs::PolygonObject* object );

    FileFormatType* exec( const kvs::ObjectBase* object );
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new PolygonExporter class.
 *  @param  object [in] pointer to a polygon object
 */
/*===========================================================================*/
template <typename FileFormatType>
PolygonExporter<FileFormatType>::PolygonExporter( const kvs::PolygonObject* object )
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
FileFormatType* PolygonExporter<FileFormatType>::exec( const kvs::ObjectBase* object )
{
    // This method will be specialized for each file format.
    return NULL;
}

/*===========================================================================*/
/**
 *  @brief  Polygon exporter class as KVSMLObjectPoint format.
 */
/*===========================================================================*/
template <>
class PolygonExporter<kvs::KVSMLObjectPolygon> : public kvs::ExporterBase<kvs::KVSMLObjectPolygon>
{
public:

    PolygonExporter( const kvs::PolygonObject* object );

    kvs::KVSMLObjectPolygon* exec( const kvs::ObjectBase* object );
};

/*===========================================================================*/
/**
 *  @brief  Polygon exporter class as STL format.
 */
/*===========================================================================*/
template <>
class PolygonExporter<kvs::Stl> : public kvs::ExporterBase<kvs::Stl>
{
public:

    PolygonExporter( const kvs::PolygonObject* object );

    kvs::Stl* exec( const kvs::ObjectBase* object );
};

/*===========================================================================*/
/**
 *  @brief  Polygon exporter class as PLY format.
 */
/*===========================================================================*/
template <>
class PolygonExporter<kvs::Ply> : public kvs::ExporterBase<kvs::Ply>
{
public:

    PolygonExporter( const kvs::PolygonObject* object );

    kvs::Ply* exec( const kvs::ObjectBase* object );
};

} // end of namespace kvs

#endif // KVS__POLYGON_EXPORTER_H_INCLUDE
