/****************************************************************************/
/**
 *  @file MouseEvent.h
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
#ifndef KVS_CORE_MOUSE_EVENT_H_INCLUDE
#define KVS_CORE_MOUSE_EVENT_H_INCLUDE

#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Mouse event class.
 */
/*==========================================================================*/
class MouseEvent
{
    kvsClassName( MouseEvent );

protected:

    int m_button;    ///< mouse button
    int m_state;     ///< mouse button state
    int m_x;         ///< mouse cursol position x
    int m_y;         ///< mouse cursol position y
    int m_modifiers; ///< modifier keys

public:

    MouseEvent( void );

    MouseEvent( const MouseEvent& event );

    MouseEvent( int button, int state, int x, int y, int modifiers = 0 );

    virtual ~MouseEvent( void );

public:

    void set( int button, int state, int x, int y, int modifiers = 0 );

    void set( int x, int y );

public:

    const int button( void ) const;

    const int state( void ) const;

    const int x( void ) const;

    const int y( void ) const;

    const int modifiers( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_MOUSE_EVENT_H_INCLUDE
