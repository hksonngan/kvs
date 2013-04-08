/*****************************************************************************/
/**
 *  @file   WindowCoordinate.h
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
#ifndef KVS__WINDOW_COORDINATE_H_INCLUDE
#define KVS__WINDOW_COORDINATE_H_INCLUDE

#include <kvs/Vector3>


namespace kvs
{

class NormalizedDeviceCoordinate;

/*===========================================================================*/
/**
 *  @brief  Window coordinate class.
 */
/*===========================================================================*/
class WindowCoordinate
{
private:

    kvs::Vector3f m_position; ///< position in window coordinates
    int m_x; ///< window position x
    int m_y; ///< window position y
    size_t m_width; ///< widnow width
    size_t m_height; ///< window height
    static float m_front; ///< depth value of the front clipping plane
    static float m_back; ///< depth value of the back clipping plane

public:

    static void SetDepthRange( const float front, const float back );
    static float CalculateDepth( const float nd_depth );
    static float InvertDepth( const float depth );

public:

    WindowCoordinate( const kvs::Vector3f& position, const int x, const int y, const size_t width, const size_t height );

    const kvs::Vector3f& position() const;
    const NormalizedDeviceCoordinate toNormalizedDeviceCoordinate() const;
};

} // end of namespace kvs

#endif // KVS__WINDOW_COORDINATE_H_INCLUDE
