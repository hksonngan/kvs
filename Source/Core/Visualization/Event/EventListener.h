/*****************************************************************************/
/**
 *  @file   EventListener.h
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
#ifndef KVS__EVENT_LISTENER_H_INCLUDE
#define KVS__EVENT_LISTENER_H_INCLUDE

#include <string>


namespace kvs
{

class ScreenBase;
class EventBase;
class MouseEvent;
class KeyEvent;
class WheelEvent;
class TimeEvent;

/*===========================================================================*/
/**
 *  @brief  Event listener class.
 */
/*===========================================================================*/
class EventListener
{
private:

    int m_event_type; ///< event type
    std::string m_name; ///< name
    kvs::ScreenBase* m_screen; ///< pointer to the screen

public:

    EventListener();
    virtual ~EventListener();

    virtual void onEvent( kvs::EventBase* event );

    int eventType() const;
    const std::string& name() const;
    kvs::ScreenBase* screen();

    void setEventType( const int event_type );
    void setName( const std::string& name );
    void setScreen( kvs::ScreenBase* screen );

    virtual void initializeEvent();
    virtual void paintEvent();
    virtual void resizeEvent( int width, int height );
    virtual void mousePressEvent( kvs::MouseEvent* event );
    virtual void mouseMoveEvent( kvs::MouseEvent* event );
    virtual void mouseReleaseEvent( kvs::MouseEvent* event );
    virtual void mouseDoubleClickEvent( kvs::MouseEvent* event );
    virtual void wheelEvent( kvs::WheelEvent* event );
    virtual void keyPressEvent( kvs::KeyEvent* event );
    virtual void timerEvent( kvs::TimeEvent* event );
};

} // end of namespace kvs

#endif // KVS__EVENT_LISTENER_H_INCLUDE
