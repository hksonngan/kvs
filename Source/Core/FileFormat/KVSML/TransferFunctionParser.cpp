/****************************************************************************/
/**
 *  @file TransferFunctionParser.cpp
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
#include "TransferFunctionParser.h"
#include "TagParser.h"
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Message>
#include <kvs/Type>
#include <iostream>
#include <fstream>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
TransferFunctionParser::TransferFunctionParser( void ):
    m_resolution( 0 ),
    m_transfer_function_node( 0 )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] reference to the XML document
 */
/*==========================================================================*/
TransferFunctionParser::TransferFunctionParser( const kvs::XMLDocument& document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param document [in] pointer to the XML document
 */
/*==========================================================================*/
TransferFunctionParser::TransferFunctionParser( const kvs::XMLDocument* document )
{
    this->parse( document );
}

/*==========================================================================*/
/**
 *  Return the resolution.
 *  @return resolution
 */
/*==========================================================================*/
const size_t TransferFunctionParser::resolution( void ) const
{
    return( m_resolution );
}

/*==========================================================================*/
/**
 *  Parse the transfer function node.
 *  @param document [in] reference to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool TransferFunctionParser::parse( const kvs::XMLDocument& document )
{
    return( this->parse( &document ) );
}

/*==========================================================================*/
/**
 *  Parse the transfer function node.
 *  @param document [in] pointer to the XML document
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool TransferFunctionParser::parse( const kvs::XMLDocument* document )
{
    // <KVSML>
    TiXmlNode* kvsml_node = kvs::TagParser::FindNode( document, "KVSML" );
    if( !kvsml_node )
    {
        kvsMessageError("Cannot find <KVSML>.");
        return( false );
    }

    // <TransferFunction>
    m_transfer_function_node = kvs::TagParser::FindChildNode( kvsml_node, "TransferFunction" );
    if( !m_transfer_function_node )
    {
        kvsMessageError("Cannot find <TransferFunction>.");
        return( false );
    }

    // <TransferFunction resolution="xxx">
    TiXmlElement* transfer_function_element = kvs::TagParser::NodeToElement( m_transfer_function_node );
    if( !this->parse_resolution( transfer_function_element ) ) return( false );

    return( true );
}

/*==========================================================================*/
/**
 *  Set the opacity array and the color array to the given arrays.
 *  @param  opacities [out] pointer to opacity array
 *  @param  colors    [out] pointer to color array
 */
/*==========================================================================*/
void TransferFunctionParser::setOpacitiesAndColorsTo(
    kvs::ValueArray<kvs::Real32>* opacities,
    kvs::ValueArray<kvs::UInt8>*  colors )
{
    TiXmlElement* transfer_function_element = kvs::TagParser::NodeToElement( m_transfer_function_node );
    std::string file = kvs::TagParser::GetAttributeValue( transfer_function_element, "file" );
    if ( file == "" )
    {
        /* <TransferFunction resolution="xxx">
         *     a r b g
         *     a r b g
         *     .......
         * </TransferFunction>
         */
        TiXmlText* transfer_function_text = kvs::TagParser::NodeToText( m_transfer_function_node );
        if ( !transfer_function_text )
        {
            kvsMessageError("No value in <TransferFunction>");
            return;
        }

        const std::string delim(" \n");
        kvs::Tokenizer t( transfer_function_text->Value(), delim );

        opacities->allocate( m_resolution );
        colors->allocate( m_resolution * 3 );

        const size_t nloops = m_resolution;
        for ( size_t i = 0; i < nloops; i++ )
        {
            opacities->at( i )      = static_cast<kvs::Real32>( atof( t.token().c_str() ) );
            colors->at( 3 * i )     = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
            colors->at( 3 * i + 1 ) = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
            colors->at( 3 * i + 2 ) = static_cast<kvs::UInt8>( atoi( t.token().c_str() ) );
        }
    }
    else
    {
        /* <TransferFunction resolution="xxx" file="filename.dat"/>
         *
         * 'filename.dat' is described as follows:
         *     a r b g
         *     a r b g
         *     .......
         */
        std::ifstream ifs( file.c_str() );
        if ( !ifs.is_open() )
        {
            kvsMessageError( "Cannot open %s.", file.c_str() );
            return;
        }

        opacities->allocate( m_resolution );
        colors->allocate( m_resolution * 3 );

        kvs::Real32 a = 0;
        kvs::UInt8  r = 0;
        kvs::UInt8  g = 0;
        kvs::UInt8  b = 0;
        for ( size_t i = 0; i < m_resolution; i++ )
        {
            ifs >> a >> r >> g >> b;
            opacities->at( i )      = a;
            colors->at( 3 * i )     = r;
            colors->at( 3 * i + 1 ) = g;
            colors->at( 3 * i + 2 ) = b;
        }

        ifs.close();
    }
}

/*==========================================================================*/
/**
 *  Parse the resolution.
 *  @param element [in] pointer to the element node
 *  @return true, if the parse process is done successfully
 */
/*==========================================================================*/
bool TransferFunctionParser::parse_resolution( const TiXmlElement* element )
{
    std::string resolution = kvs::TagParser::GetAttributeValue( element, "resolution" );
    if( resolution == "" )
    {
        kvsMessageError("Cannot find 'resolution' in <TransferFunction>.");
        return( false );
    }

    m_resolution = atoi( resolution.c_str() );

    return( true );
}

} // end of namespace kvs
