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
#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <kvs/glut/Screen>


/*===========================================================================*/
/**
 *  @brief  Screen class.
 */
/*===========================================================================*/
class Screen : public kvs::glut::ScreenBase
{
public:

    Screen( void );

public:

    static void mouse_press_event( kvs::MouseEvent* event );

    static void mouse_move_event( kvs::MouseEvent* event );

    static void additional_initialize_func( void );

    static void additional_paint_event( void );

    static void additional_key_press_event( kvs::KeyEvent* event );

private:

    static void show_information( void );
};

#endif // __SCREEN_H__
