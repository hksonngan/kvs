/*****************************************************************************/
/**
 *  @file   TagBase.cpp
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
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new TagBase class.
 *  @param  name [in] tag name
 */
/*===========================================================================*/
TagBase::TagBase( const std::string& name ):
    m_name( name ),
    m_node( NULL )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the TagBase class.
 */
/*===========================================================================*/
TagBase::~TagBase()
{
}

/*===========================================================================*/
/**
 *  @brief  Returns a tag name.
 *  @return tag name
 */
/*===========================================================================*/
const std::string& TagBase::name() const
{
    return m_name;
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node without 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
kvs::XMLNode::SuperClass* TagBase::node()
{
    return m_node;
}

/*===========================================================================*/
/**
 *  @brief  Returns a pointer to the node with 'const'.
 *  @return pointer to the node
 */
/*===========================================================================*/
const kvs::XMLNode::SuperClass* TagBase::node() const
{
    return m_node;
}

/*===========================================================================*/
/**
 *  @brief  Check whether this node is existed or not in the parent node.
 *  @param  parent [in] pointer to the parent node
 *  @return true, if the node is existed
 */
/*===========================================================================*/
bool TagBase::isExisted( const kvs::XMLNode::SuperClass* parent ) const
{
    const std::string tag_name = this->name();
    return kvs::XMLNode::FindChildNode( parent, tag_name ) != NULL;
}

} // end of namespace kvsml

} // end of namespace kvs
