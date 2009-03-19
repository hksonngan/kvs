/****************************************************************************/
/**
 *  @file ConnectionTagParser.cpp
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
#include "ConnectionTagParser.h"
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
 *  @param nindices [in] number of indices
 */
/*==========================================================================*/
ConnectionTagParser::ConnectionTagParser( const size_t nindices ):
    m_nindices( nindices )
{
}

/*==========================================================================*/
/**
 *  Parse the connection array.
 *  @param parent_node [in] pointer to the parent node
 *  @param  connections [out] connection array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool ConnectionTagParser::parse(
    const TiXmlNode*              parent_node,
    kvs::ValueArray<kvs::UInt32>* connections )
{
    // <Connection>
    TiXmlNode* connection_node = kvs::TagParser::FindChildNode( parent_node, "Connection" );
    if( !connection_node ) return( true );

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( connection_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");
        return( false );
    }

    connections->allocate( m_nindices );

    return( kvs::TagParser::ParseArray<kvs::UInt32>( data_array_node, connections ) );
}

} // end of namespace kvs
