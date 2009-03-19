/****************************************************************************/
/**
 *  @file LineImporter.h
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
#ifndef KVS_CORE_LINE_IMPORTER_H_INCLUDE
#define KVS_CORE_LINE_IMPORTER_H_INCLUDE

#include "ImporterBase.h"
#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/LineObject>
#include <kvs/KVSMLObjectLine>


namespace kvs
{

/*==========================================================================*/
/**
 *  Line object importer.
 */
/*==========================================================================*/
class LineImporter
    : public kvs::ImporterBase
    , public kvs::LineObject
{
    // Class name.
    kvsClassName( LineImporter );

    // Module information.
    kvsModuleCategory( Importer );
    kvsModuleBaseClass( kvs::ImporterBase );
    kvsModuleSuperClass( kvs::LineObject );

public:

    LineImporter( void );

    LineImporter( const std::string& filename );

    LineImporter( const kvs::FileFormatBase* file_format );

    virtual ~LineImporter( void );

public:

    kvs::ObjectBase* exec( const kvs::FileFormatBase* file_format );

private:

    void import( const kvs::KVSMLObjectLine* kvsml );

    void set_min_max_coord( void );
};

} // end of namespace kvs

#endif // KVS_CORE_LINE_IMPORTER_H_INCLUDE
