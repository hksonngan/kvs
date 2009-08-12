/*****************************************************************************/
/**
 *  @file   WheelEvent.h
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
#ifndef KVS__WHEEL_EVENT_H_INCLUDE
#define KVS__WHEEL_EVENT_H_INCLUDE

#include <kvs/EventBase>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  WheelEvent class.
 */
/*===========================================================================*/
class WheelEvent : public kvs::EventBase
{
protected:

    int m_x;         ///< x coordinate value of mouse cursor position
    int m_y;         ///< y coordinate value of mouse cursor position
    int m_direction; ///< scroll direction

public:

    WheelEvent( void );

    virtual ~WheelEvent( void );

public:

    void setPosition( int x, int y );

    void setDirection( int direction );

    const int x( void ) const;

    const int y( void ) const;

    const int direction( void ) const;

    virtual const int type( void ) const;
};

} // end of namespace kvs

#endif // KVS__WHEEL_EVENT_H_INCLUDE
