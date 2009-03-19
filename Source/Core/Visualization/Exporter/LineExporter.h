/*****************************************************************************/
/**
 *  @file   LineExporter.h
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
#ifndef KVS__LINE_EXPORTER_H_INCLUDE
#define KVS__LINE_EXPORTER_H_INCLUDE

#include <kvs/LineObject>
#include <kvs/KVSMLObjectLine>
#include "ExporterBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  Line exporter class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class LineExporter : public kvs::ExporterBase<FileFormatType>
{
public:

    LineExporter( const kvs::LineObject* line_object );

    FileFormatType* exec( const kvs::ObjectBase* object_base );
};

template <typename FileFormatType>
LineExporter<FileFormatType>::LineExporter( const kvs::LineObject* line_object )
{
    this->exec( line_object );
}

template <typename FileFormatType>
FileFormatType* LineExporter<FileFormatType>::exec( const kvs::ObjectBase* object_base )
{
    return( NULL );
}

/*===========================================================================*/
/**
 *  Line exporter class as KVSMLObjectLine format.
 */
/*===========================================================================*/
template <>
class LineExporter<kvs::KVSMLObjectLine> : public kvs::ExporterBase<kvs::KVSMLObjectLine>
{
public:

    LineExporter( const kvs::LineObject* line_object );

    kvs::KVSMLObjectLine* exec( const kvs::ObjectBase* object_base );
};

} // end of namespace kvs

#endif // KVS__LINE_EXPORTER_H_INCLUDE
