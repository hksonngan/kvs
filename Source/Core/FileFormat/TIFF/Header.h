/****************************************************************************/
/**
 *  @file Header.h
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
#ifndef KVS_CORE_TIFF_HEADER_H_INCLUDE
#define KVS_CORE_TIFF_HEADER_H_INCLUDE

#include <kvs/Type>
#include <iostream>
#include <fstream>


namespace kvs
{

namespace tiff
{

class Header
{
protected:

    kvs::UInt16 m_magic;   ///< magic number
    kvs::UInt16 m_version; ///< TIFF version
    kvs::UInt32 m_offset;  ///< byte offset to first IDF

public:

    Header( void );

    Header( std::ifstream& ifs );

public:

    friend std::ostream& operator << ( std::ostream& os, const Header& header );

public:

    kvs::UInt16 magic( void ) const;

    kvs::UInt16 version( void ) const;

    kvs::UInt32 offset( void ) const;

    bool read( std::ifstream& ifs );
};

} // end of namesapce tiff

} // end of namespace kvs

#endif // KVS_CORE_TIFF_HEADER_H_INCLUDE
