/****************************************************************************/
/**
 *  @file ImporterBase.h
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
#ifndef KVS_CORE_IMPORTER_BASE_H_INCLUDE
#define KVS_CORE_IMPORTER_BASE_H_INCLUDE

#include <kvs/FileFormatBase>
#include <kvs/ObjectBase>
#include <kvs/ClassName>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Importer base class.
 */
/*==========================================================================*/
class ImporterBase
{
    kvsClassName( ImporterBase );

    kvsModuleBase;

protected:

    bool m_is_success; ///< check flag for importing

public:

    ImporterBase( void );

    virtual ~ImporterBase( void );

public:

    virtual kvs::ObjectBase* exec( const kvs::FileFormatBase* file_format ) = 0;

public:

    const bool isSuccess( void ) const;

    const bool isFailure( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_IMPORTER_BASE_H_INCLUDE
