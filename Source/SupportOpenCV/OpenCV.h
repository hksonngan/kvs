/*****************************************************************************/
/**
 *  @file   OpenCV.h
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
#ifndef KVS_SUPPORT_OPENCV_OPENCV_H_INCLUDE
#define KVS_SUPPORT_OPENCV_OPENCV_H_INCLUDE

#include <kvs/String>

#include <cv.h>
#include <highgui.h>


namespace kvs
{

namespace opencv
{

/*===========================================================================*/
/**
 *  @brief  Returns OpenCV description
 *  @return description
 */
/*===========================================================================*/
inline const std::string Description( void )
{
    const std::string description( "OpenCV - Intel Open Source Computer Vision Library" );
    return( description );
}

/*===========================================================================*/
/**
 *  @brief  Returns OpenCV version.
 *  @return OpenCV version
 */
/*===========================================================================*/
inline const std::string Version( void )
{
    const std::string version( kvs::String( CV_VERSION ).toStdString() );
    return( version );
}

} // end of namespace opencv

} // end of namespace kvs

#endif // KVS_SUPPORT_OPENCV_OPENCV_H_INCLUDE
