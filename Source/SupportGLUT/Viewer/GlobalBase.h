/****************************************************************************/
/**
 *  @file GlobalBase.h
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
#ifndef KVS__GLUT__GLOBAL_BASE_H_INCLUDE
#define KVS__GLUT__GLOBAL_BASE_H_INCLUDE

#include <kvs/GlobalCore>


namespace kvs
{

namespace glut
{

/*==========================================================================*/
/**
*  Global base class for GLUT.
*/
/*==========================================================================*/
class GlobalBase : public kvs::GlobalCore
{
    friend class ScreenBase;

public:

    GlobalBase( int count, char** values );

    virtual ~GlobalBase( void );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS_SUPPORT_GLUT_GLOBAL_BASE_H_INCLUDE
