/*****************************************************************************/
/**
 *  @file   StructuredVolumeObjectTag.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__KVSML__STRUCTURED_VOLUME_OBJECT_H_INCLUDE
#define KVS__KVSML__STRUCTURED_VOLUME_OBJECT_H_INCLUDE

#include <string>
#include <kvs/XMLNode>
#include <kvs/Vector3>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <StructuredVolumeObject>
 */
/*===========================================================================*/
class StructuredVolumeObjectTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree
    bool m_has_grid_type; ///< flag to check whether 'grid_type' is specified or not
    std::string m_grid_type; ///< grid type
    bool m_has_resolution; ///< flag to check whether 'resolution' is specified or not
    kvs::Vector3ui m_resolution; ///< grid resolution

public:

    StructuredVolumeObjectTag( void );

    virtual ~StructuredVolumeObjectTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool hasGridType( void ) const;

    const std::string& gridType( void ) const;

    const bool hasResolution( void ) const;

    const kvs::Vector3ui& resolution( void ) const;

public:

    void setGridType( const std::string& grid_type );

    void setResolution( const kvs::Vector3ui& resolution );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__STRUCTURED_VOLUME_OBJECT_H_INCLUDE
