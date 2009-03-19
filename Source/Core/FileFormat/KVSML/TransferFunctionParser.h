/****************************************************************************/
/**
 *  @file TransferFunctionParser.h
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
#ifndef KVS_CORE_KVSML_TRANSFER_FUNCTION_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_TRANSFER_FUNCTION_PARSER_H_INCLUDE

#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>


namespace kvs
{

/*==========================================================================*/
/**
 *  Transfer function parser.
 */
/*==========================================================================*/
class TransferFunctionParser
{
protected:

    size_t     m_resolution;             ///< number of vertices
    TiXmlNode* m_transfer_function_node; ///< pointer to the transfer function node

public:

    TransferFunctionParser( void );

    TransferFunctionParser( const kvs::XMLDocument& document );

    TransferFunctionParser( const kvs::XMLDocument* document );

public:

    const size_t resolution( void ) const;

public:

    bool parse( const kvs::XMLDocument& document );

    bool parse( const kvs::XMLDocument* document );

public:

    void setOpacitiesAndColorsTo(
        kvs::ValueArray<kvs::Real32>* opacities,
        kvs::ValueArray<kvs::UInt8>*  colors );

protected:

    bool parse_resolution( const TiXmlElement* element );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_TRANSFER_FUNCTION_PARSER_H_INCLUDE
