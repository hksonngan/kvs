/****************************************************************************/
/**
 *  @file LineObjectParser.h
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
#ifndef KVS_CORE_KVSML_LINE_OBJECT_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_LINE_OBJECT_PARSER_H_INCLUDE

#include <string>
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Line object node parser class.
 */
/*==========================================================================*/
class LineObjectParser
{
protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< pointer to the KVSML tag
    kvs::kvsml::ObjectTag m_object_tag; ///< pointer to the Object tag

    std::string m_line_type;        ///< line type [strip|uniline|polyline|segment]
    std::string m_color_type;       ///< color type [vertex|line]
    size_t      m_nvertices;        ///< number of vertices
    size_t      m_nlines;           ///< number of lines (connections)
    TiXmlNode*  m_line_object_node; ///< pointer to the line object node
    TiXmlNode*  m_vertex_node;      ///< pointer to the vertex node
    TiXmlNode*  m_line_node;        ///< pointer to the line node

public:

    LineObjectParser( void );

    LineObjectParser( const kvs::XMLDocument& document );

    LineObjectParser( const kvs::XMLDocument* document );

public:

    const kvs::kvsml::KVSMLTag KVSMLTag( void ) const;

    const kvs::kvsml::ObjectTag objectTag( void ) const;

    const std::string& lineType( void ) const;

    const std::string& colorType( void ) const;

    const size_t nvertices( void ) const;

    const size_t nlines( void ) const;

public:

    bool parse( const kvs::XMLDocument* document );

    bool parse( const kvs::XMLDocument& document );

public:

    void setCoordsTo( kvs::ValueArray<kvs::Real32>* coords );

    void setConnectionsTo( kvs::ValueArray<kvs::UInt32>* connections );

    void setColorsTo( kvs::ValueArray<kvs::UInt8>* colors );

    void setSizesTo( kvs::ValueArray<kvs::Real32>* sizes );

protected:

    bool parse_line_type( const TiXmlElement* element );

    bool parse_color_type( const TiXmlElement* element );

    bool parse_nvertices( const TiXmlElement* element );

    bool parse_nlines( const TiXmlElement* element );

public:

    static const bool Check( const kvs::XMLDocument& document );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_LINE_OBJECT_PARSER_H_INCLUDE
