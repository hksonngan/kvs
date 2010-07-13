/*****************************************************************************/
/**
 *  @file   Camera.h
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
#ifndef KVS__OPENCABIN__CAMERA_H_INCLUDE
#define KVS__OPENCABIN__CAMERA_H_INCLUDE

#include <kvs/Camera>


namespace kvs
{

namespace opencabin
{

/*===========================================================================*/
/**
 *  @brief  Camera class for OpenCABIN.
 */
/*===========================================================================*/
class Camera : public kvs::Camera
{
public:

    virtual void update( void );
};

} // end of namespace opencabin

} // end of namespace kvs

#endif // KVS__OPENCABIN__CAMERA_H_INCLUDE
