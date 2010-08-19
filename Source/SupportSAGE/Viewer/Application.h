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
#ifndef KVS__SAGE__APPLICATION_H_INCLUDE
#define KVS__SAGE__APPLICATION_H_INCLUDE

#include <kvs/glut/Screen>


namespace kvs
{

namespace sage
{

/*===========================================================================*/
/**
 *  @brief  SAGE viewer application class.
 */
/*===========================================================================*/
class Application : public kvs::glut::Application
{
public:

    Application( int argc, char** argv );

    virtual ~Application( void );
};

} // end of namespace sage

} // end of namespace kvs

#endif // KVS__SAGE__APPLICATION_H_INCLUDE
