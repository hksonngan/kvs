/*****************************************************************************/
/**
 *  @file   NodeTag.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
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

private:

    bool m_has_nnodes; ///< flag to check whether 'nnodes' is specified or not
    size_t m_nnodes; ///< number of nodes

public:

    NodeTag();

public:

    bool hasNNodes() const;
    size_t nnodes() const;

public:

    void setNNodes( const size_t nnodes );

public:

    bool read( const kvs::XMLNode::SuperClass* parent );
    bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__NODE_TAG_H_INCLUDE
