/****************************************************************************/
/**
 *  @file ValueTagParser.h
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
#ifndef KVS_CORE_KVSML_VALUE_TAG_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_VALUE_TAG_PARSER_H_INCLUDE

#include "TagParser.h"
#include <kvs/AnyValueArray>
#include <kvs/XMLDocument>
#include <kvs/Vector3>


namespace kvs
{

/*==========================================================================*/
/**
 *  Value tag parser class.
 */
/*==========================================================================*/
class ValueTagParser
{
protected:

    size_t m_nnodes; ///< number of nodes

public:

    ValueTagParser( const size_t nnodes );

    bool parse( const TiXmlNode* parent_node, kvs::AnyValueArray* values );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_VALUE_TAG_PARSER_H_INCLUDE
