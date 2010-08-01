/*****************************************************************************/
/**
 *  @file   Trackpad.h
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
#ifndef KVS__OPENCABIN__TRACKPAD_H_INCLUDE
#define KVS__OPENCABIN__TRACKPAD_H_INCLUDE

#include <kvs/glut/Screen>
#include <kvs/opencabin/Application>


namespace kvs
{

namespace opencabin
{

class Trackpad : public kvs::glut::Screen
{
public:

    typedef kvs::glut::Screen BaseClass;

public:

    Trackpad( kvs::opencabin::Application* application );

public:

    int show( void );

    void updateXform( void );
};

} // end of namespace opencabin

} // end of namespace kvs

#endif // KVS__OPENCABIN__TRACKPAD_H_INCLUDE
