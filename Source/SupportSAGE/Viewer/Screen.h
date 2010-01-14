/*****************************************************************************/
/**
 *  @file   Screen.h
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
#include <kvs/TimerEventListener>
#include <kvs/PaintEventListener>
#include <kvs/glut/Screen>
#include <kvs/glut/Timer>
#include "Application.h"
#include "ApplicationInterface.h"


namespace kvs
{

namespace sage
{

/*===========================================================================*/
/**
 *  @brief  SAGE screen class.
 */
/*===========================================================================*/
class Screen : public kvs::glut::Screen
{
    typedef kvs::glut::Screen BaseClass;

    class MessageListener;
    class PixelStreamer;

    friend class pixel_streamer;

protected:

    kvs::sage::ApplicationInterface* m_sail; ///< SAGE application interface (SAIL)
    kvs::glut::Timer* m_timer;               ///< timer for the SAGE message
    MessageListener*  m_message_listener;    ///< SAGE message listener
    PixelStreamer*    m_pixel_streamer;      ///< Pixel streamer

public:

    Screen( kvs::sage::Application* application );

    virtual ~Screen( void );

public:

    kvs::sage::ApplicationInterface* sail( void );

protected:

    void paint_event( void );

    void setup_sail( void );

    void send_buffer( void );
};

/*===========================================================================*/
/**
 *  @brief  Message listener class from the SAGE.
 */
/*===========================================================================*/
class Screen::MessageListener : public kvs::TimerEventListener
{
    kvs::sage::ApplicationInterface* m_sail; ///< pointer to the SAIL.

public:

    MessageListener( kvs::sage::ApplicationInterface* sail );

    void update( kvs::TimeEvent* event );
};

/*===========================================================================*/
/**
 *  @brief  Pixel streaming class to the SAGE.
 */
/*===========================================================================*/
class Screen::PixelStreamer : public kvs::PaintEventListener
{
    void update( void );
};

} // end of namespace sage

} // end of namespace kvs
