/*****************************************************************************/
/**
 *  @file   ValueTag.h
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
#ifndef KVS__KVSML__VALUE_TAG_H_INCLUDE
#define KVS__KVSML__VALUE_TAG_H_INCLUDE

#include <kvs/XMLNode>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Value>
 */
/*===========================================================================*/
class ValueTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

protected:

    bool m_has_veclen; ///< flag to check whether 'veclen' is specified or not
    size_t m_veclen; ///< vector length

public:

    ValueTag( void );

    virtual ~ValueTag( void );

public:

    const bool hasVeclen( void ) const;

    const size_t veclen( void ) const;

public:

    void setVeclen( const size_t veclen );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__VALUE_TAG_H_INCLUDE
