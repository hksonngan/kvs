/*****************************************************************************/
/**
 *  @file   NodeTag.h
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
#ifndef KVS__KVSML__NODE_TAG_H_INCLUDE
#define KVS__KVSML__NODE_TAG_H_INCLUDE

#include <kvs/XMLNode>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Node>
 */
/*===========================================================================*/
class NodeTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

protected:

    bool m_has_nnodes; ///< flag to check whether 'nnodes' is specified or not
    size_t m_nnodes; ///< number of nodes

public:

    NodeTag( void );

    virtual ~NodeTag( void );

public:

    const bool hasNNodes( void ) const;

    const size_t nnodes( void ) const;

public:

    void setNNodes( const size_t nnodes );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__NODE_TAG_H_INCLUDE
