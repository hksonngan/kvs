/*****************************************************************************/
/**
 *  @file   ConnectionTag.h
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
#ifndef KVS__KVSML__CONNECTION_TAG_H_INCLUDE
#define KVS__KVSML__CONNECTION_TAG_H_INCLUDE

#include <kvs/XMLNode>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Connection>
 */
/*===========================================================================*/
class ConnectionTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree

public:

    ConnectionTag( void );

    virtual ~ConnectionTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__CONNECTION_TAG_H_INCLUDE
