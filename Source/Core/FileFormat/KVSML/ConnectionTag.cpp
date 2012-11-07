/*****************************************************************************/
/**
 *  @file   ConnectionTag.cpp
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
#include "ConnectionTag.h"


namespace kvs
{

namespace kvsml
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new coord tag class.
 */
/*===========================================================================*/
ConnectionTag::ConnectionTag():
    kvs::kvsml::TagBase( "Connection" )
{
}

} // end of namespace kvsml

} // end of namespace kvs
