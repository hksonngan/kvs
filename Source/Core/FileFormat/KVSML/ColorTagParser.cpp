/****************************************************************************/
/**
 *  @file ColorTagParser.cpp
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
#include "ColorTagParser.h"
#include "TagParser.h"
#include <kvs/Message>
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param nvertices [in] number of vertices
 */
/*==========================================================================*/
ColorTagParser::ColorTagParser( const size_t nvertices ):
    m_nvertices( nvertices )
{
}

/*==========================================================================*/
/**
 *  Parse the color tag.
 *  @param parent_node [in] pointer to the parent node
 *  @param  colors      [out] color array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool ColorTagParser::parse(
    const TiXmlNode*             parent_node,
    kvs::ValueArray<kvs::UInt8>* colors )
{
    // <Color>
    TiXmlNode* color_node = kvs::TagParser::FindChildNode( parent_node, "Color" );
    if( !color_node )
    {
        // Set default value (black).
        colors->allocate(3);
        colors->at(0) = 0;
        colors->at(1) = 0;
        colors->at(2) = 0;

        kvsMessageError("Cannot find <Color>.");

        return( false );
    }

    // <DataValue>
    TiXmlNode* data_value_node = kvs::TagParser::FindChildNode( color_node, "DataValue" );
    if( data_value_node )
    {
        colors->allocate( 3 );
        return( kvs::TagParser::ParseValue<kvs::UInt8>( data_value_node, colors ) );
    }

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( color_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");
        return( false );
    }

    colors->allocate( m_nvertices * 3 );

    return( kvs::TagParser::ParseArray<kvs::UInt8>( data_array_node, colors ) );
}

} // end of namespace kvs
