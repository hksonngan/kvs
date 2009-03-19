/*****************************************************************************/
/**
 *  @file   CellTag.h
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
#ifndef KVS__KVSML__CELL_TAG_H_INCLUDE
#define KVS__KVSML__CELL_TAG_H_INCLUDE

#include <kvs/XMLNode>


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Node>
 */
/*===========================================================================*/
class CellTag
{
protected:

    kvs::XMLNode::SuperClass* m_node; ///< pointer to the node of the XML tree
    bool m_has_ncells; ///< flag to check whether 'ncells' is specified or not
    size_t m_ncells; ///< number of cells

public:

    CellTag( void );

    virtual ~CellTag( void );

public:

    kvs::XMLNode::SuperClass* node( void );

    const kvs::XMLNode::SuperClass* node( void ) const;

public:

    const bool hasNCells( void ) const;

    const size_t ncells( void ) const;

public:

    void setNCells( const size_t ncells );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__CELL_TAG_H_INCLUDE
