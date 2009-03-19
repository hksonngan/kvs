/****************************************************************************/
/**
 *  @file UnstructuredVolumeObjectParser.h
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
#ifndef KVS_CORE_KVSML_UNSTRUCTURED_VOLUME_OBJECT_PARSER_H_INCLUDE
#define KVS_CORE_KVSML_UNSTRUCTURED_VOLUME_OBJECT_PARSER_H_INCLUDE

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

class UnstructuredVolumeObjectParser
{
protected:

    kvs::kvsml::KVSMLTag m_kvsml_tag; ///< pointer to the KVSML tag
    kvs::kvsml::ObjectTag m_object_tag; ///< pointer to the Object tag

    std::string m_cell_type; ///< cell type [tetrahedra|hexahedra]
    size_t m_nnodes; ///< number of nodes
    size_t m_ncells; ///< number of cells

    TiXmlNode* m_volume_object_node; ///< pointer to the unstructured volume node
    TiXmlNode* m_node_node; ///< pointer to the node node
    TiXmlNode* m_cell_node; ///< pointer to the cell node

public:

    UnstructuredVolumeObjectParser( void );

    UnstructuredVolumeObjectParser( const kvs::XMLDocument& document );

    UnstructuredVolumeObjectParser( const kvs::XMLDocument* document );

public:

    const std::string& cellType( void ) const;

    const size_t nnodes( void ) const;

    const size_t ncells( void ) const;

    const size_t veclen( void ) const;

public:

    bool parse( const kvs::XMLDocument& document );

    bool parse( const kvs::XMLDocument* document );

public:

    void setValuesTo( kvs::AnyValueArray* values );

    void setCoordsTo( kvs::ValueArray<kvs::Real32>* coords );

    void setConnectionsTo( kvs::ValueArray<kvs::UInt32>* connections );

protected:

    bool parse_cell_type( const TiXmlElement* element );

    bool parse_nnodes( const TiXmlElement* element );

    bool parse_ncells( const TiXmlElement* element );

public:

    static const bool Check( const kvs::XMLDocument& document );
};

} // end of namespace kvs

#endif // KVS_CORE_KVSML_UNSTRUCTURED_VOLUME_OBJECT_PARSER_H_INCLUDE
