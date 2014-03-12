/*****************************************************************************/
/**
 *  @file   Application.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__GLUT__APPLICATION_H_INCLUDE
#define KVS__GLUT__APPLICATION_H_INCLUDE

#include <kvs/ApplicationBase>


namespace kvs
{

namespace glut
{

/*===========================================================================*/
/**
 *  @brief  GLUT viewer application class.
 */
/*===========================================================================*/
class Application : public kvs::ApplicationBase
{
public:

    Application( int argc, char** argv );
    virtual ~Application();

    virtual int run();
    virtual void quit();
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__APPLICATION_H_INCLUDE
