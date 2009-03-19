/****************************************************************************/
/**
 *  @file OpacityTagParser.cpp
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
#include "OpacityTagParser.h"
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
OpacityTagParser::OpacityTagParser( const size_t nvertices ):
    m_nvertices( nvertices )
{
}

/*==========================================================================*/
/**
 *  Parse the opacity tag.
 *  @param parent_node [in] pointer to the parent node
 *  @param  opacities   [out] opacity array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool OpacityTagParser::parse(
    const TiXmlNode*             parent_node,
    kvs::ValueArray<kvs::UInt8>* opacities )
{
    // <Opacity>
    TiXmlNode* opacity_node = kvs::TagParser::FindChildNode( parent_node, "Opacity" );
    if( !opacity_node )
    {
        // Set default value.
        opacities->allocate(1);
        opacities->at(0) = 255;

        return( true );
    }

    // <DataValue>
    TiXmlNode* data_value_node = kvs::TagParser::FindChildNode( opacity_node, "DataValue" );
    if( data_value_node )
    {
        opacities->allocate(1);

        return( kvs::TagParser::ParseValue<kvs::UInt8>( data_value_node, opacities ) );
    }

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( opacity_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");

        return( false );
    }

    opacities->allocate( m_nvertices );

    return( kvs::TagParser::ParseArray<kvs::UInt8>( data_array_node, opacities ) );
}

} // end of namesapce kvs
