/*****************************************************************************/
/**
 *  @file   Screen.cpp
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
#include "Screen.h"
#include <kvs/Message>
#include <kvs/TimeEvent>

// Static parameters.
namespace { const size_t MaxNumberOfSAILs = 32; }
namespace { kvs::sage::ApplicationInterface* context[::MaxNumberOfSAILs]; }

namespace
{

/*===========================================================================*/
/**
 *  @brief  Function that is called when the application is terminated.
 */
/*===========================================================================*/
void ExitFunction( void )
{
    for ( size_t i = 0; i < ::MaxNumberOfSAILs; i++)
    {
        if ( ::context[i] ) ::context[i]->shutdown();
    }
}

} // end of namespace

namespace kvs
{

namespace sage
{

Screen::Screen( kvs::sage::Application* application )
{
    int argc = application->argc();
    char** argv = application->argv();
    m_sail = new kvs::sage::ApplicationInterface( argc, argv );
    if ( !m_sail )
    {
        kvsMessageError("Cannot allocate memory for the SAIL.");
        exit( EXIT_FAILURE );
    }

    // Set up paint event.
    m_pixel_streamer = new Screen::PixelStreamer();
    if ( !m_pixel_streamer )
    {
        kvsMessageError("Cannot allocate memory for the pixel stremaer.");
        exit( EXIT_FAILURE );
    }

    BaseClass::setPaintEvent( m_pixel_streamer );

    // Set up timer event.
    m_message_listener = new Screen::MessageListener( m_sail );
    if ( !m_message_listener )
    {
        kvsMessageError("Cannot allocate memory for the SAGE message listener.");
        exit( EXIT_FAILURE );
    }

    m_timer = new kvs::glut::Timer( m_message_listener );
    if ( !m_timer )
    {
        kvsMessageError("Cannot allocate memory for the timer.");
        exit( EXIT_FAILURE );
    }

    m_timer->start( 1000 );

    atexit( ::ExitFunction );
}

Screen::~Screen( void )
{
    if ( m_sail ) delete m_sail;
    if ( m_pixel_streamer ) delete m_pixel_streamer;
    if ( m_message_listener ) delete m_message_listener;
    if ( m_timer ) delete m_timer;
}

kvs::sage::ApplicationInterface* Screen::sail( void )
{
    return( m_sail );
}

void Screen::paint_event( void )
{
    // Initialize the SAGE application interface (SAIL).
    if ( !m_sail->isInitialized() )
    {
        this->setup_sail();
    }

    // Execute the paint function.
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPushMatrix();
    BaseClass::paintFunction();
    BaseClass::eventHandler()->notify();
    glPopMatrix();

    // Send the frame buffer to the tiled display.
    this->send_buffer();
    glutSwapBuffers();
}

void Screen::setup_sail( void )
{
    m_sail->setApplicationWidth( BaseClass::width() );
    m_sail->setApplicationHeight( BaseClass::height() );
    m_sail->initialize();
}

void Screen::send_buffer( void )
{
    GLubyte* pixels = static_cast<GLubyte*>( m_sail->getBuffer() );
    glReadPixels( 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, pixels );

    m_sail->swapBuffer();
}

Screen::MessageListener::MessageListener( kvs::sage::ApplicationInterface* sail ):
    m_sail( sail )
{
}

void Screen::MessageListener::update( kvs::TimeEvent* event )
{
    if ( m_sail->isInitialized() )
    {
        sageMessage message;
        if ( 0 < m_sail->checkMsg( message, false ) )
        {
            switch ( message.getCode() )
            {
            case APP_QUIT: exit( 0 );
            case APP_REFRESH_FRAME: glutPostRedisplay(); break;
            default: break;
            }
        }
    }
}

void Screen::PixelStreamer::update( void )
{
    static_cast<kvs::sage::Screen*>( screen() )->paint_event();
}

} // end of namespace sage

} // end of namespace kvs
