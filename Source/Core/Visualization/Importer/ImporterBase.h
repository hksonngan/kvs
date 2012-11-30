/****************************************************************************/
/**
 *  @file ImporterBase.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS__IMPORTER_BASE_H_INCLUDE
#define KVS__IMPORTER_BASE_H_INCLUDE

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
    kvsClassName( kvs::ImporterBase );
    kvsModuleBase;

protected:

    bool m_is_success; ///< check flag for importing

public:

    ImporterBase();
    virtual ~ImporterBase();

    bool isSuccess() const;
    bool isFailure() const;

    virtual kvs::ObjectBase* exec( const kvs::FileFormatBase* file_format ) = 0;
};

} // end of namespace kvs

#endif // KVS__IMPORTER_BASE_H_INCLUDE
