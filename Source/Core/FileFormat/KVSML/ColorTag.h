/*****************************************************************************/
/**
 *  @file   ColorTag.h
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
#ifndef KVS__KVSML__COLOR_TAG_H_INCLUDE
#define KVS__KVSML__COLOR_TAG_H_INCLUDE

#include "TagBase.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Tag class for <Color>
 */
/*===========================================================================*/
class ColorTag : public kvs::kvsml::TagBase
{
public:

    typedef kvs::kvsml::TagBase BaseClass;

public:

    ColorTag();
};

} // end of namespace kvsml

} // end of namespace kvs

#endif // KVS__KVSML__COLOR_TAG_H_INCLUDE
