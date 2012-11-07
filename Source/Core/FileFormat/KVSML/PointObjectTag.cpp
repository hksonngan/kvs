/*****************************************************************************/
/**
 *  @file   PointObjectTag.cpp
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
#include "PointObjectTag.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new structured volume object tag class.
 */
/*===========================================================================*/
PointObjectTag::PointObjectTag():
    kvs::kvsml::TagBase( "PointObject" )
{
}

} // end of namespace kvsml

} // end of namespace kvs
