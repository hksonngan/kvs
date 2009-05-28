/*****************************************************************************/
/**
 *  @file   LookAtMatrix44.cpp
 *  @author Naohisa Sakamoto
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
#include "LookAtMatrix44.h"


namespace kvs
{

template kvs::Matrix44<float> LookAtMatrix44<float>(
    const kvs::Vector3<float>& eye,
    const kvs::Vector3<float>& up,
    const kvs::Vector3<float>& target );

template kvs::Matrix44<double> LookAtMatrix44<double>(
    const kvs::Vector3<double>& eye,
    const kvs::Vector3<double>& up,
    const kvs::Vector3<double>& target );

} // end of namespace kvs
