/****************************************************************************/
/**
 *  @file Directory.h
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
#ifndef KVS_CORE_DIRECTORY_H_INCLUDE
#define KVS_CORE_DIRECTORY_H_INCLUDE

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

#include "FileList.h"
#include "ClassName.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Directory class
 */
/*==========================================================================*/
class Directory
{
    kvsClassName( Direcotry );

private:

    std::string   m_directory_path; ///< directory path (ex. "/tmp/abc/")
    std::string   m_directory_name; ///< directory name (ex. "abc")
    kvs::FileList m_file_list;      ///< filename list

public:

    Directory( void );

    explicit Directory( const std::string& directory_path );

    virtual ~Directory( void );

public:

    const std::string directoryPath( bool absolute = false ) const;

    const std::string directoryName( void ) const;

    kvs::FileList& fileList( void );

    const kvs::FileList& fileList( void ) const;

    const bool isDirectory( void ) const;

    const bool isExisted( void ) const;

    const bool parse( const std::string& direcotry_path );

    void sort( void );

    kvs::FileList::iterator find( const kvs::File& file );

    kvs::FileList::const_iterator find( const kvs::File& file ) const;

public:

    static const std::string Separator( void );

    static bool Make( const std::string& directory_path );

    static bool Remove( const std::string& directory_path );

    static bool Change( const std::string& directory_path );

    static Directory Current( void );
};

} // end of namespace kvs

#endif // KVS_CORE_DIRECTORY_H_INCLUDE
