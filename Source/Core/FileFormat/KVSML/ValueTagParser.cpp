/****************************************************************************/
/**
 *  @file ValueTagParser.cpp
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
#include "ValueTagParser.h"
#include "TagParser.h"
#include <kvs/Message>
#include <kvs/AnyValueArray>
#include <kvs/XMLDocument>
#include <kvs/Vector3>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param nnodes [in] number of nodes
 */
/*==========================================================================*/
ValueTagParser::ValueTagParser( const size_t nnodes ):
    m_nnodes( nnodes )
{
}

/*==========================================================================*/
/**
 *  Parse the node tag.
 *  @param parent_node [in] pointer to the parent node
 *  @param  values      [out] value array
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool ValueTagParser::parse(
    const TiXmlNode*    parent_node,
    kvs::AnyValueArray* values )
{
    // <Value>
    TiXmlNode* value_node = kvs::TagParser::FindChildNode( parent_node, "Value" );
    if( !value_node )
    {
        kvsMessageError("Cannot find <Value>.");
        return( false );
    }

    // <Value veclen="xxx">
    TiXmlElement* value_element = kvs::TagParser::NodeToElement( value_node );
    std::string veclen = kvs::TagParser::GetAttributeValue( value_element, "veclen" );
    if( veclen == "" )
    {
        kvsMessageError("Cannot find 'veclen' in <Value>.");
        return( false );
    }

    // <DataArray>
    TiXmlNode* data_array_node = kvs::TagParser::FindChildNode( value_node, "DataArray" );
    if( !data_array_node )
    {
        kvsMessageError("Cannot find <DataArray>");
        return( false );
    }

    // <DataArray type="xxx">
    TiXmlElement* data_array_element = kvs::TagParser::NodeToElement( data_array_node );
    std::string type = kvs::TagParser::GetAttributeValue( data_array_element, "type" );
    if( type == "" )
    {
        kvsMessageError("Cannot find 'type' in <DataArray>.");
        return( false );
    }

    const size_t nvalues = m_nnodes * atoi( veclen.c_str() );
    if( type == "char" )
    {
        values->allocate<char>( nvalues );
        return( kvs::TagParser::ParseArray<char>( data_array_node, values ) );
    }
    else if( type == "unsigned char" || type == "uchar" )
    {
        values->allocate<unsigned char>( nvalues );
        return( kvs::TagParser::ParseArray<unsigned char>( data_array_node, values ) );
    }
    else if( type == "short" )
    {
        values->allocate<short>( nvalues );
        return( kvs::TagParser::ParseArray<short>( data_array_node, values ) );
    }
    else if( type == "unsigned short" || type == "ushort" )
    {
        values->allocate<unsigned short>( nvalues );
        return( kvs::TagParser::ParseArray<unsigned short>( data_array_node, values ) );
    }
    else if( type == "int" )
    {
        values->allocate<int>( nvalues );
        return( kvs::TagParser::ParseArray<int>( data_array_node, values ) );
    }
    else if( type == "unsigned int" || type == "uint" )
    {
        values->allocate<unsigned int>( nvalues );
        return( kvs::TagParser::ParseArray<unsigned int>( data_array_node, values ) );
    }
    else if( type == "float" )
    {
        values->allocate<float>( nvalues );
        return( kvs::TagParser::ParseArray<float>( data_array_node, values ) );
    }
    else if( type == "double" )
    {
        values->allocate<double>( nvalues );
        return( kvs::TagParser::ParseArray<double>( data_array_node, values ) );
    }
    else
    {
        kvsMessageError("Unknown 'type' in <DataArray>.");
        return( false );
    }
}

} // end of namespace kvs
