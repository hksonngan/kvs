/*****************************************************************************/
/**
 *  @file   PointObjectTag.h
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
#ifndef KVS__KVSML__POINT_OBJECT_H_INCLUDE
#define KVS__KVSML__POINT_OBJECT_H_INCLUDE

#include <string>
#include <kvs/XMLNode>
#include <kvs/Vector3>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <PointObject>
 */
/*===========================================================================*/
class PointObjectTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree

public:

    PointObjectTag( void );

    virtual ~PointObjectTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__POINT_OBJECT_H_INCLUDE
