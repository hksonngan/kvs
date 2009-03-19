/****************************************************************************/
/**
 *  @file ConnectionTagParser.h
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
#ifndef KVS_CORE_KVSML_CONNECTION_TAG_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_CONNECTION_TAG_PARSER_H_INCLUDE

#include "TagParser.h"
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>


namespace kvs
{

/*==========================================================================*/
/**
 *  Connection tag parser class.
 */
/*==========================================================================*/
class ConnectionTagParser
{
protected:

    size_t m_nindices; ///< number of indices

public:

    ConnectionTagParser( const size_t nindices );

    bool parse( const TiXmlNode* parent_node, kvs::ValueArray<kvs::UInt32>* connections );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_CONNECTION_TAG_PARSER_H_INCLUDE
