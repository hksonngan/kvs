/****************************************************************************/
/**
 *  @file CoordTagParser.cpp
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
#include "CoordTagParser.h"
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
CoordTagParser::CoordTagParser( const size_t nvertices ):
    m_nvertices( nvertices )
{
}

/*==========================================================================*/
/**
 *  Parse.
 *  @param parent_node [in] pointer to the parent node
 *  @param  coords      [out] pointer to the coordinate array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool CoordTagParser::parse(
    const TiXmlNode*              parent_node,
    kvs::ValueArray<kvs::Real32>* coords )
{
    // <Coord>
    TiXmlNode* coord_node = kvs::TagParser::FindChildNode( parent_node, "Coord" );
    if( !coord_node )
    {
        kvsMessageError("Cannot find <Coord>.");
        return( false );
    }

    // <DataValue>
    TiXmlNode* data_value_node = kvs::TagParser::FindChildNode( coord_node, "DataValue" );
    if( data_value_node )
    {
        if( m_nvertices == 1 )
        {
            const size_t dimension = 3;
            coords->allocate( dimension );
            return( kvs::TagParser::ParseValue<kvs::Real32>( data_value_node, coords ) );
        }

        kvsMessageError("Incorrect the number of vertices.");

        return( false );
    }

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( coord_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");
        return( false );
    }

    const size_t dimension = 3;
    coords->allocate( m_nvertices * dimension );

    return( kvs::TagParser::ParseArray<kvs::Real32>( data_array_node, coords ) );
}

} // end of namespace kvs
