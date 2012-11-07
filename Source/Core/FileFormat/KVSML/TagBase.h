/*****************************************************************************/
/**
 *  @file   TagBase.h
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
#ifndef KVS__KVSML__TAG_BASE_H_INCLUDE
#define KVS__KVSML__TAG_BASE_H_INCLUDE

#include <kvs/XMLNode>
#include <string>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Base class of the tag.
 */
/*===========================================================================*/
class TagBase
{
protected:

    std::string m_name; ///< tag name
    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree

protected:

    TagBase( const std::string& name );
    ~TagBase(){}

public:

    kvs::XMLNode::SuperClass* node();
    const kvs::XMLNode::SuperClass* node() const;
    const std::string& name() const;
    bool isExisted( const kvs::XMLNode::SuperClass* parent ) const;

public:

    bool read( const kvs::XMLNode::SuperClass* parent );
    bool write( kvs::XMLNode::SuperClass* parent );

private:

    TagBase();
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__TAG_BASE_H_INCLUDE
