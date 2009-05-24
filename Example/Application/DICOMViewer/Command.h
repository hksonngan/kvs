/*****************************************************************************/
/**
 *  @file   Command.h
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
#ifndef __COMMAND_H__
#define __COMMAND_H__

namespace kvs { class MouseEvent; }

/*===========================================================================*/
/**
 *  @brief  Command set.
 */
/*===========================================================================*/
struct Command
{
    static void toggleInformationFlag( void );

    static void incrementIndex( const unsigned int value = 1 );

    static void decrementIndex( const unsigned int value = 1 );

    static void updateDicomImage( void );

    static void updateDicomWindow( void );

    static void resetDicomWindow( void );

    static void pressMouse( kvs::MouseEvent* event );

    static void moveMouse( kvs::MouseEvent* event );

    static void writeScreenImage( void );

    static void writeHeader( void );

    static void writeData( void );
};

#endif // __COMMAND_H__
