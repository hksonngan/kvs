/****************************************************************************/
/**
 *  @file PolygonImporter.h
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
#ifndef KVS_CORE_POLYGON_IMPORTER_H_INCLUDE
#define KVS_CORE_POLYGON_IMPORTER_H_INCLUDE

#include "ImporterBase.h"
#include <kvs/ClassName>
#include <kvs/Module>
#include <kvs/PolygonObject>
#include <kvs/KVSMLObjectPolygon>
#include <kvs/Stl>


namespace kvs
{

/*==========================================================================*/
/**
 *  Polygon importer class.
 */
/*==========================================================================*/
class PolygonImporter
    : public kvs::ImporterBase
    , public kvs::PolygonObject
{
    // Class name.
    kvsClassName( PolygonImporter );

    // Module information.
    kvsModuleCategory( Importer );
    kvsModuleBaseClass( kvs::ImporterBase );
    kvsModuleSuperClass( kvs::PolygonObject );

public:

    PolygonImporter( void );

    PolygonImporter( const std::string& filename );

    PolygonImporter( const kvs::FileFormatBase* file_format );

    virtual ~PolygonImporter( void );

public:

    kvs::ObjectBase* exec( const kvs::FileFormatBase* file_format );

private:

    void import( const kvs::KVSMLObjectPolygon* kvsml );

    void import( const kvs::Stl* stl );

    void set_min_max_coord( void );
};

} // end of namespace kvs

#endif // KVS_CORE_POLYGON_IMPORTER_H_INCLUDE
