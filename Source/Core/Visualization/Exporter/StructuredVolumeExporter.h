/*****************************************************************************/
/**
 *  @file   StructuredVolumeExporter.h
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
#ifndef KVS__STRUCTURED_VOLUME_EXPORTER_H_INCLUDE
#define KVS__STRUCTURED_VOLUME_EXPORTER_H_INCLUDE

#include <kvs/ObjectBase>
#include <kvs/StructuredVolumeObject>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/ExporterBase>


namespace kvs
{

/*===========================================================================*/
/**
 *  Structured volume exporter class.
 */
/*===========================================================================*/
template <typename FileFormatType>
class StructuredVolumeExporter : public kvs::ExporterBase<FileFormatType>
{
public:

    StructuredVolumeExporter( const kvs::StructuredVolumeObject* object );

    FileFormatType* exec( const kvs::ObjectBase* object );
};

/*===========================================================================*/
/**
 *  @brief  Constructs a FileFormat data from given structured volume object.
 *  @param  object [in] pointer to the structured volume object
 */
/*===========================================================================*/
template <typename FileFormatType>
StructuredVolumeExporter<FileFormatType>::StructuredVolumeExporter(
    const kvs::StructuredVolumeObject* object )
{
    this->exec( object );
}

/*===========================================================================*/
/**
 *  @brief  Exports to a spcified FileFormat data.
 *  @param  object [in] pointer to the structured volume object
 */
/*===========================================================================*/
template <typename FileFormatType>
FileFormatType* StructuredVolumeExporter<FileFormatType>::exec( const kvs::ObjectBase* object )
{
    return( NULL );
}

/*===========================================================================*/
/**
 *  Specialized structured volume exporter class for kvs::KVSMLObjectStructuredVolume.
 */
/*===========================================================================*/
template <>
class StructuredVolumeExporter<kvs::KVSMLObjectStructuredVolume> :
        public kvs::ExporterBase<kvs::KVSMLObjectStructuredVolume>
{
public:

    StructuredVolumeExporter( const kvs::StructuredVolumeObject* object );

    kvs::KVSMLObjectStructuredVolume* exec( const kvs::ObjectBase* object );
};

} // end of namespace kvs

#endif // KVS__STRUCTURED_VOLUME_EXPORTER_H_INCLUDE
