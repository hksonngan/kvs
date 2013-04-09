/****************************************************************************/
/**
 *  @file Mouse.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS__MOUSE_H_INCLUDE
#define KVS__MOUSE_H_INCLUDE

#include <kvs/Trackball>
#if KVS_ENABLE_DEPRECATED
#include <kvs/OpenGL>
#endif
#include <kvs/Timer>
#include <kvs/Vector2>


namespace kvs
{

/*==========================================================================*/
/**
 *  Mouse class
 */
/*==========================================================================*/
class Mouse : public kvs::Trackball
{
    typedef kvs::Trackball BaseClass;

public:

    enum TransMode
    {
        Rotation    = 0, ///< rotation mode
        Translation = 1, ///< translation mode
        Scaling     = 2  ///< scaling mode
    };

    enum AutoMode
    {
        AutoOff = 0, ///< auto rotation mode off
        AutoOn  = 1  ///< auto rotation mode on
    };

    static int SpinTime; ///< spin time
    static float WheelUpValue;   ///< wheel up value
    static float WheelDownValue; ///< wheel down value

protected:

    TransMode m_mode; ///< transform mode
    ScalingType m_scaling_type; ///< scaling type
    kvs::Vector2i m_old; ///< old mouse position on the window coordinate (org: upper-left)
    kvs::Vector2i m_new; ///< new mouse position on the window coordinate (org: upper-left)
    kvs::Vector2i m_start; ///< position at start of rotation
    kvs::Vector2i m_stop; ///< position at stop of rotation
    kvs::Timer m_timer; ///< auto check timer
    bool m_is_auto; ///< auto flag (true: if auto mode)
    bool m_is_slow; ///< slow flag (true: if slow mode)
    bool m_is_use_auto; ///< auto use flag (true: if user use auto mode )

public:

    Mouse( AutoMode auto_flg = AutoOn );
    virtual ~Mouse();

    void reset();
    void press( const int x, const int y );
    void move( const int x, const int y );
    void wheel( const float value );
    void release( const int x, const int y );
    bool idle();

    void setMode( const TransMode mode );
    void setScalingType( const ScalingType type );
    void setScalingType( const bool x, const bool y, const bool z );
    TransMode mode() const;
    ScalingType scalingType() const;

    void setUseAuto( const bool flg );
    bool isUseAuto();
    bool isAuto();
    bool isSlow();
};

} // end of namespace kvs

#endif // KVS__MOUSE_H_INCLUDE
