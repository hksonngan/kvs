/*****************************************************************************/
/**
 *  @file   MainLoop.h
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
#ifndef KVS__OPENCABIN__MAIN_LOOP_H_INCLUDE
#define KVS__OPENCABIN__MAIN_LOOP_H_INCLUDE

#include <kvs/Thread>


namespace kvs
{

namespace opencabin
{

/*===========================================================================*/
/**
 *  @brief  Main loop class for OpenCABIN.
 */
/*===========================================================================*/
class MainLoop : public kvs::Thread
{
    typedef kvs::Thread BaseClass;

protected:

    int    m_argc; ///< argument count
    char** m_argv; ///< argument values

public:

    MainLoop( int argc, char** argv );

    void run( void );
};

} // end of namespace opencabin

} // end of namespace kvs

#endif // KVS__OPENCABIN__MAIN_LOOP_H_INCLUDE
