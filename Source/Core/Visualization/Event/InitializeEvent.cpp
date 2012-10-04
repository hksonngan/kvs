/*****************************************************************************/
/**
 *  @file   InitializeEvent.cpp
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
#include "InitializeEvent.h"

namespace kvs
{

InitializeEvent::InitializeEvent()
{
}

InitializeEvent::~InitializeEvent()
{
}

int InitializeEvent::type() const
{
    return( EventBase::InitializeEvent );
}

} // end of namespace kvs
