/****************************************************************************/
/**
 *  @file OpacityTagParser.h
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
#ifndef KVS_CORE_KVSML_OPACITY_TAG_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_OPACITY_TAG_PARSER_H_INCLUDE

#include "TagParser.h"
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>


namespace kvs
{

/*==========================================================================*/
/**
 *  Opacity tag parser class.
 */
/*==========================================================================*/
class OpacityTagParser
{
protected:

    size_t m_nvertices; ///< number of vertices

public:

    OpacityTagParser( size_t nvertices );

    bool parse( const TiXmlNode* parent_node, kvs::ValueArray<kvs::UInt8>* opacities );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_OPACITY_TAG_PARSER_H_INCLUDE
