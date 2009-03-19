/****************************************************************************/
/**
 *  @file SizeTagParser.cpp
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
#include "SizeTagParser.h"
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
SizeTagParser::SizeTagParser( const size_t nvertices ):
    m_nvertices( nvertices )
{
}

/*==========================================================================*/
/**
 *  Parse the size tag.
 *  @param parent_node [in] pointer to the parent node
 *  @param  sizes       [out] size array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool SizeTagParser::parse(
    const TiXmlNode*              parent_node,
    kvs::ValueArray<kvs::Real32>* sizes )
{
    // <Size>
    TiXmlNode* size_node = kvs::TagParser::FindChildNode( parent_node, "Size" );
    if( !size_node ) return( true );

    // <DataValue>
    TiXmlNode* data_value_node = kvs::TagParser::FindChildNode( size_node, "DataValue" );
    if( data_value_node )
    {
        sizes->allocate( 1 );
        return( kvs::TagParser::ParseValue<kvs::Real32>( data_value_node, sizes ) );
    }

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( size_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");
        return( false );
    }

    sizes->allocate( m_nvertices );

    return( kvs::TagParser::ParseArray<kvs::Real32>( data_array_node, sizes ) );
}

} // end of namespace kvs
