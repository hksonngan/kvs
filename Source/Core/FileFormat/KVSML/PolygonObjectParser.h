/****************************************************************************/
/**
 *  @file PolygonObjectParser.h
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
#ifndef KVS_CORE_KVSML_POLYGON_OBJECT_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_POLYGON_OBJECT_PARSER_H_INCLUDE

#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Polygon object node parser.
 */
/*==========================================================================*/
class PolygonObjectParser
{
protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< pointer to the KVSML tag
    kvs::kvsml::ObjectTag m_object_tag; ///< pointer to the Object tag

    std::string m_polygon_type;        ///< polygon type [triangle|quadrangle]
    std::string m_color_type;          ///< color type [vertex|polygon]
    std::string m_normal_type;         ///< normal type [vertex|polygon]
    size_t      m_nvertices;           ///< number of vertices
    size_t      m_npolygons;           ///< number of polygons (connections)
    TiXmlNode*  m_polygon_object_node; ///< pointer to the polygon object node
    TiXmlNode*  m_vertex_node;         ///< pointer to the vertex node
    TiXmlNode*  m_polygon_node;        ///< pointer to the polygon node

public:

    PolygonObjectParser( void );

    PolygonObjectParser( const kvs::XMLDocument& document );

    PolygonObjectParser( const kvs::XMLDocument* document );

public:

    const kvs::kvsml::KVSMLTag KVSMLTag( void ) const;

    const kvs::kvsml::ObjectTag objectTag( void ) const;

    const std::string& polygonType( void ) const;

    const std::string& colorType( void ) const;

    const std::string& normalType( void ) const;

    const size_t nvertices( void ) const;

    const size_t npolygons( void ) const;

public:

    bool parse( const kvs::XMLDocument& document );

    bool parse( const kvs::XMLDocument* document );

public:

    void setCoordsTo( kvs::ValueArray<kvs::Real32>* coords );

    void setConnectionsTo( kvs::ValueArray<kvs::UInt32>* connections );

    void setNormalsTo( kvs::ValueArray<kvs::Real32>* normals );

    void setColorsTo( kvs::ValueArray<kvs::UInt8>* colors );

    void setOpacitiesTo( kvs::ValueArray<kvs::UInt8>* opacities );

protected:

    bool parse_polygon_type( const TiXmlElement* element );

    bool parse_color_type( const TiXmlElement* element );

    bool parse_normal_type( const TiXmlElement* element );

    bool parse_nvertices( const TiXmlElement* element );

    bool parse_npolygons( const TiXmlElement* element );

public:

    static const bool Check( const kvs::XMLDocument& document );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_POLYGON_OBJECT_PARSER_H_INCLUDE
