/****************************************************************************/
/**
 *  @file PointObjectParser.h
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
#ifndef KVS_CORE_KVSML_POINT_OBJECT_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_POINT_OBJECT_PARSER_H_INCLUDE

#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Point object parser.
 */
/*==========================================================================*/
class PointObjectParser
{
protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< pointer to the KVSML tag
    kvs::kvsml::ObjectTag m_object_tag; ///< pointer to the Object tag

    size_t     m_nvertices;         ///< number of vertices
    TiXmlNode* m_point_object_node; ///< pointer to the point object node
    TiXmlNode* m_vertex_node;       ///< pointer to the vertex node

public:

    PointObjectParser( void );

    PointObjectParser( const kvs::XMLDocument& document );

    PointObjectParser( const kvs::XMLDocument* document );

public:

    const kvs::kvsml::KVSMLTag KVSMLTag( void ) const;

    const kvs::kvsml::ObjectTag objectTag( void ) const;

    const size_t nvertices( void ) const;

public:

    bool parse( const kvs::XMLDocument& document );

    bool parse( const kvs::XMLDocument* document );

public:

    void setCoordsTo( kvs::ValueArray<kvs::Real32>* coords );

    void setColorsTo( kvs::ValueArray<kvs::UInt8>* colors );

    void setNormalsTo( kvs::ValueArray<kvs::Real32>* normals );

    void setSizesTo( kvs::ValueArray<kvs::Real32>* sizes );

protected:

    bool parse_nvertices( const TiXmlElement* element );

public:

    static const bool Check( const kvs::XMLDocument& document );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_POINT_OBJECT_PARSER_H_INCLUDE
