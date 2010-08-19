/****************************************************************************/
/**
 *  @file TagDictionary.h
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
#ifndef KVS_CORE_TIFF_TAG_DICTIONARY_H_INCLUDE
#define KVS_CORE_TIFF_TAG_DICTIONARY_H_INCLUDE

#include <kvs/Type>
#include <map>
#include "Tag.h"


namespace kvs
{

namespace tiff
{

class TagDictionary
{
public:

    typedef std::map<kvs::UInt16,std::string> Container;

protected:

    Container m_container;

public:

    TagDictionary( void );

public:

    kvs::tiff::Tag find( const kvs::UInt16 tag_id ) const;

private:

    void create_dictionary( void );
};

} // end of namespace tiff

} // end of namespace kvs

#endif // KVS_CORE_TIFF_TAG_DICTIONARY_H_INCLUDE
