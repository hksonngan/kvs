/*****************************************************************************/
/**
 *  @file   FrustumMatrix44.h
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
#ifndef KVS__FRUSTUM_MATRIX44_H_INCLUDE
#define KVS__FRUSTUM_MATRIX44_H_INCLUDE

#include <cmath>
#include <kvs/Matrix44>
#include <kvs/Math>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Return view-frustum matrix.
 *  @param  left [in] Left position.
 *  @param  right [in] Right position.
 *  @param  bottom [in] Bottom position.
 *  @param  top [in] Top position.
 *  @param  near [in] Near position.
 *  @param  far [in] Far position.
 *  @return View-frustum matrix.
 */
/*===========================================================================*/
template <typename T>
inline kvs::Matrix44<T> FrustumMatrix44(
    const T left,
    const T right,
    const T bottom,
    const T top,
    const T near,
    const T far )
{
    const T width  = right - left;
    const T height = top - bottom;
    const T depth  = far - near;

    KVS_ASSERT( !( kvs::Math::IsZero( width  ) ) );
    KVS_ASSERT( !( kvs::Math::IsZero( height ) ) );
    KVS_ASSERT( !( kvs::Math::IsZero( depth  ) ) );

    const T elements[16] =
    {
           ( near * 2 ) / width,                         0,                           0,  0,
                              0,     ( near * 2 ) / height,                           0,  0,
        ( right+ left ) / width, ( top + bottom ) / height,     -( far + near ) / depth, -1,
                              0,                         0, -( far * near * 2 ) / depth,  0
    };

    return( kvs::Matrix44<T>( elements ) );
};

} // end of namespace kvs

#endif // KVS__FRUSTUM_MATRIX44_H_INCLUDE
