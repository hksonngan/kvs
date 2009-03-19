/****************************************************************************/
/**
 *  @file Screen.h
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
#ifndef KVS_SUPPORT_GLUT_SCREEN_H_INCLUDE
#define KVS_SUPPORT_GLUT_SCREEN_H_INCLUDE

#include <kvs/glut/ScreenBase>


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
 *  Screen class.
 */
/*==========================================================================*/
class Screen : public kvs::glut::ScreenBase
{
public:

    Screen( const size_t width, const size_t height );

    Screen( const size_t x, const size_t y, const size_t width, const size_t height );

    virtual ~Screen( void );
};

} // end of namesapce glut

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_SCREEN_H_INCLUDE
