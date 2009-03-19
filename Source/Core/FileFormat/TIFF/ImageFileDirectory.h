/****************************************************************************/
/**
 *  @file ImageFileDirectory.h
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
#ifndef KVS_CORE_TIFF_IMAGE_FILE_DIRECTORY_H_INCLUDE
#define KVS_CORE_TIFF_IMAGE_FILE_DIRECTORY_H_INCLUDE

#include "Entry.h"
#include <kvs/Type>
#include <iostream>
#include <fstream>
#include <list>


namespace kvs
{

namespace tiff
{

class ImageFileDirectory
{
public:

    typedef std::list<kvs::tiff::Entry> EntryList;

protected:

    EntryList   m_entry_list; ///< entry list
    kvs::UInt32 m_offset;     ///< bytes offset

public:

    ImageFileDirectory( void );

    ImageFileDirectory( std::ifstream& ifs );

public:

    const std::list<tiff::Entry>& entryList( void ) const;

    kvs::UInt32 offset( void ) const;

    bool read( std::ifstream& ifs );
};

} // end of namespace tiff

} // end of namespace kvs

#endif // KVS_CORE_TIFF_IMAGE_FILE_DIRECTORY_H_INCLUDE
