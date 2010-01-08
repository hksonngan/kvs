/****************************************************************************/
/**
 *  @file StructuredVolumeImporter.h
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
#ifndef KVS__STRUCTURED_VOLUME_IMPORTER_H_INCLUDE
#define KVS__STRUCTURED_VOLUME_IMPORTER_H_INCLUDE

#include "ImporterBase.h"
#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/StructuredVolumeObject>
#include <kvs/KVSMLObjectStructuredVolume>
#include <kvs/AVSField>


namespace kvs
{

/*==========================================================================*/
/**
 *  Structured volume object importer class.
 */
/*==========================================================================*/
class StructuredVolumeImporter
    : public kvs::ImporterBase
    , public kvs::StructuredVolumeObject
{
    // Class name.
    kvsClassName( StructuredVolumeImporter );

    // Module information.
    kvsModuleCategory( Importer );
    kvsModuleBaseClass( kvs::ImporterBase );
    kvsModuleSuperClass( kvs::StructuredVolumeObject );

public:

    StructuredVolumeImporter( void );

    StructuredVolumeImporter( const std::string& filename );

    StructuredVolumeImporter( const kvs::FileFormatBase* file_format );

    virtual ~StructuredVolumeImporter( void );

public:

    SuperClass* exec( const kvs::FileFormatBase* file_format );

private:

    void import( const kvs::KVSMLObjectStructuredVolume* kvsml );

    void import( const kvs::AVSField* field );
};

} // end of namespace kvs

#endif // KVS__STRUCTURED_VOLUME_IMPORTER_H_INCLUDE
