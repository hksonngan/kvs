/****************************************************************************/
/**
 *  @file Tag.h
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
#ifndef KVS_CORE_TIFF_TAG_H_INCLUDE
#define KVS_CORE_TIFF_TAG_H_INCLUDE

#include <kvs/Type>
#include <string>


namespace kvs
{

namespace tiff
{

class Tag
{
private:

    kvs::UInt16 m_id;   ///< tag id
    std::string m_name; ///< tag name

public:

    Tag( void );

    Tag( const kvs::UInt16 id, const std::string& name );

    Tag( const Tag& tag );

public:

    Tag& operator = ( const Tag& tag );

    kvs::UInt16 id( void ) const;

    const std::string& name( void ) const;
};

} // end of namesapce tiff

} // end of namespace kvs

#endif // KVS_CORE_TIFF_TAG_H_INCLUDE
