/****************************************************************************/
/**
 *  @file StructuredVolumeObjectParser.h
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
#ifndef KVS_CORE_KVSML_STRUCTURED_VOLUME_OBJECT_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_STRUCTURED_VOLUME_OBJECT_PARSER_H_INCLUDE

#include <kvs/AnyValueArray>
#include <kvs/ValueArray>
#include <kvs/XMLDocument>
#include <kvs/Type>
#include <kvs/Vector3>
#include <string>
#include "KVSMLTag.h"
#include "ObjectTag.h"


namespace kvs
{

class StructuredVolumeObjectParser
{
protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< pointer to the KVSML tag
    kvs::kvsml::ObjectTag m_object_tag; ///< pointer to the Object tag

    std::string m_grid_type; ///< grid type [uniform|rectilinear|curvilinear]
    kvs::Vector3ui m_resolution; ///< resolution

    TiXmlNode* m_volume_object_node; ///< pointer to the structured volume node
    TiXmlNode* m_node_node; ///< pointer to the node node ("<Node></Node>")

public:

    StructuredVolumeObjectParser( void );

    StructuredVolumeObjectParser( const kvs::XMLDocument& document );

    StructuredVolumeObjectParser( const kvs::XMLDocument* document );

public:

    const kvs::kvsml::KVSMLTag KVSMLTag( void ) const;

    const kvs::kvsml::ObjectTag objectTag( void ) const;

    const std::string& gridType( void ) const;

    const kvs::Vector3ui& resolution( void ) const;

    const size_t veclen( void ) const;

public:

    bool parse( const kvs::XMLDocument& document );

    bool parse( const kvs::XMLDocument* document );

public:

    void setValuesTo( kvs::AnyValueArray* values );

    void setCoordsTo( kvs::ValueArray<kvs::Real32>* coords );

protected:

    bool parse_resolution( const TiXmlElement* element );

    bool parse_grid_type( const TiXmlElement* element );

public:

    static const bool Check( const kvs::XMLDocument& document );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_STRUCTURED_VOLUME_OBJECT_PARSER_H_INCLUDE
