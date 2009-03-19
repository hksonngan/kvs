/*****************************************************************************/
/**
 *  @file   VertexTag.h
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
#ifndef KVS__KVSML__VERTEX_TAG_H_INCLUDE
#define KVS__KVSML__VERTEX_TAG_H_INCLUDE

#include <kvs/XMLNode>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Vertex>
 */
/*===========================================================================*/
class VertexTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree
    bool m_has_nvertices; ///< flag to check whether 'nvertices' is specified or not
    size_t m_nvertices; ///< number of vertices

public:

    VertexTag( void );

    virtual ~VertexTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool hasNVertices( void ) const;

    const size_t nvertices( void ) const;

public:

    void setNVertices( const size_t nvertices );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__VERTEX_TAG_H_INCLUDE
