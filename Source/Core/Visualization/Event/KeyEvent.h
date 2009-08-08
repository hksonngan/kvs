/****************************************************************************/
/**
 *  @file KeyEvent.h
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
#ifndef KVS_CORE_KEY_EVENT_H_INCLUDE
#define KVS_CORE_KEY_EVENT_H_INCLUDE

#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Key event class.
 */
/*==========================================================================*/
class KeyEvent
{
    kvsClassName( KeyEvent );

protected:

    int m_key; ///< key code
    int m_x;   ///< mouse cursol position x
    int m_y;   ///< mouse cursol position y

public:

    KeyEvent( void );

    KeyEvent( const KeyEvent& event );

    KeyEvent( int key, int x, int y );

    virtual ~KeyEvent( void );

public:

    void set( int key, int x, int y );

public:

    const int key( void ) const;

    const int x( void ) const;

    const int y( void ) const;
};

} // end of namespace kvs

#endif // KVS_CORE_KEY_EVENT_H_INCLUDE
