/****************************************************************************/
/**
 *  @file QtScreenSupport.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_SUPPORT_QT_QT_SCREEN_SUPPORT_H_INCLUDE
#define KVS_SUPPORT_QT_QT_SCREEN_SUPPORT_H_INCLUDE

#include "../Qt.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Screen support class.
 */
/*==========================================================================*/
class QtScreenSupport
{
protected:

    QGLWidget* m_ref_screen;

public:

    QtScreenSupport( QGLWidget* screen );

    virtual ~QtScreenSupport( void );

public:

    void attachScreen( QGLWidget* screen );

    const QPoint position( void );

    const QSize size( void );

    void redraw( void );

    void showFullScreen( void );

    void showNormal( void );

    void activateWindow( void );

    void clearFocus( void );

    void resize( int w, int h );

    void move( int x, int y );

//    void setCursor( const Qt::CursorShape& cursor );
};

inline QtScreenSupport::QtScreenSupport( QGLWidget* screen )
{
    attachScreen( screen );
}

inline QtScreenSupport::~QtScreenSupport( void )
{
}

inline void QtScreenSupport::attachScreen( QGLWidget* screen )
{
    m_ref_screen = screen;
}

inline const QPoint QtScreenSupport::position( void )
{
    return( m_ref_screen->pos() );
}

inline const QSize QtScreenSupport::size( void )
{
    return( m_ref_screen->size() );
}

inline void QtScreenSupport::redraw( void )
{
    m_ref_screen->updateGL();
}

inline void QtScreenSupport::showFullScreen( void )
{
    m_ref_screen->QWidget::showFullScreen();
}

inline void QtScreenSupport::showNormal( void )
{
    m_ref_screen->QWidget::showNormal();
}

inline void QtScreenSupport::activateWindow( void )
{
#if ( KVS_QT_VERSION >= 4 )
    m_ref_screen->QWidget::activateWindow();
#else
    m_ref_screen->QWidget::setActiveWindow();
#endif
}

inline void QtScreenSupport::clearFocus( void )
{
    m_ref_screen->QWidget::clearFocus();
}

inline void QtScreenSupport::resize( int w, int h )
{
    m_ref_screen->QWidget::resize( w, h );
}

inline void QtScreenSupport::move( int x, int y )
{
    m_ref_screen->QWidget::move( x, y );
}

/*
inline void QtScreenSupport::setCursor( const Qt::CursorShape& cursor )
{
    m_ref_screen->setCursor( cursor );
}
*/

} // end of namespace kvs

#endif // KVS_SUPPORT_QT_QT_SCREEN_SUPPORT_H_INCLUDE
