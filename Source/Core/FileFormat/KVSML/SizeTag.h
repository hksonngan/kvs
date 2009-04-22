/*****************************************************************************/
/**
 *  @file   SizeTag.h
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
#ifndef KVS__KVSML__SIZE_TAG_H_INCLUDE
#define KVS__KVSML__SIZE_TAG_H_INCLUDE

#include <kvs/XMLNode>
#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Size>
 */
/*===========================================================================*/
class SizeTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

public:

    SizeTag( void );

    virtual ~SizeTag( void );

public:

    const bool read( const kvs::XMLNode::SuperClass* parent );

    const bool write( kvs::XMLNode::SuperClass* parent );
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__SIZE_TAG_H_INCLUDE
