/****************************************************************************/
/**
 *  @file UnstructuredVolumeImporter.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_UNSTRUCTURED_VOLUME_IMPORTER_H_INCLUDE
#define KVS_CORE_UNSTRUCTURED_VOLUME_IMPORTER_H_INCLUDE

#include "ImporterBase.h"
#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/KVSMLObjectUnstructuredVolume>
#include <kvs/AVSUcd>
#include <kvs/AVSField>


namespace kvs
{

/*==========================================================================*/
/**
 *  Unstructured volume object importer class.
 */
/*==========================================================================*/
class UnstructuredVolumeImporter
    : public kvs::ImporterBase
    , public kvs::UnstructuredVolumeObject
{
    // Class name.
    kvsClassName( UnstructuredVolumeImporter );

    // Module information.
    kvsModuleCategory( Importer );
    kvsModuleBaseClass( kvs::ImporterBase );
    kvsModuleSuperClass( kvs::UnstructuredVolumeObject );

public:

    UnstructuredVolumeImporter( void );

    UnstructuredVolumeImporter( const std::string& filename );

    UnstructuredVolumeImporter( const kvs::FileFormatBase* file_format );

    virtual ~UnstructuredVolumeImporter( void );

public:

    kvs::ObjectBase* exec( const kvs::FileFormatBase* file_format );

private:

    void import( const kvs::KVSMLObjectUnstructuredVolume* const kvsml );

    void import( const kvs::AVSUcd* const ucd );

    void import( const kvs::AVSField* const field );

};

} // end of namespace kvs

#endif // KVS_CORE_UNSTRUCTURED_VOLUME_IMPORTER_H_INCLUDE
