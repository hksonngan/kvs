/*****************************************************************************/
/**
 *  @file   NormalTag.h
 *  @author Naohisa Sakamoto
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
#ifndef KVS__KVSML__NORMAL_TAG_H_INCLUDE
#define KVS__KVSML__NORMAL_TAG_H_INCLUDE

#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Normal>
 */
/*===========================================================================*/
class NormalTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

public:

    NormalTag();

};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__NORMAL_TAG_H_INCLUDE
