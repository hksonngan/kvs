/****************************************************************************/
/**
 *  @file NormalTagParser.cpp
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
#include "NormalTagParser.h"
#include "TagParser.h"
#include <kvs/Message>
#include <kvs/ValueArray>
#include <kvs/XMLDocument>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param nvertice [in] number of vertices
 */
/*==========================================================================*/
NormalTagParser::NormalTagParser( const size_t nvertices ):
    m_nvertices( nvertices )
{
}

/*==========================================================================*/
/**
 *  Parse the normal tag.
 *  @param parent_node [in] pointer to the parent node
 *  @param  normals     [out] normal array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool NormalTagParser::parse(
    const TiXmlNode*              parent_node,
    kvs::ValueArray<kvs::Real32>* normals )
{
    // <Normal>
    // Set the nothing, if the normal node is not existed.
    TiXmlNode* normal_node = kvs::TagParser::FindChildNode( parent_node, "Normal" );
    if( !normal_node ) return( true );

    // <DataValue>
    TiXmlNode* data_value_node = kvs::TagParser::FindChildNode( normal_node, "DataValue" );
    if( data_value_node )
    {
        if( m_nvertices == 1 )
        {
            const size_t dimension = 3;
            normals->allocate( dimension );
            return( kvs::TagParser::ParseValue<kvs::Real32>( data_value_node, normals ) );
        }

        kvsMessageError("Incorrect the number of vertices.");

        return( false );
    }

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( normal_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");

        return( false );
    }

    const size_t dimension = 3;
    normals->allocate( m_nvertices * dimension );

    return( kvs::TagParser::ParseArray<kvs::Real32>( data_array_node, normals ) );
}

} // end of namespace kvs
