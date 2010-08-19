/****************************************************************************/
/**
 *  @file ScreenBase.h
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
#ifndef KVS_SUPPORT_SAGE_SCREEN_BASE_H_INCLUDE
#define KVS_SUPPORT_SAGE_SCREEN_BASE_H_INCLUDE

#include <kvs/glut/ScreenBase>


namespace kvs
{

namespace sage
{

class ScreenBase : public kvs::glut::ScreenBase
{
public:

    ScreenBase( void );

    virtual ~ScreenBase( void );

protected:

    static void sage_paint_event( void );

    static void sage_check_message( int val );

    static void sage_setup( void );

    static void sage_send_buffer( void );
};

} // end of namespace sage

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_SCREEN_BASE_H_INCLUDE
