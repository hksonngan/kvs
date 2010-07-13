/*****************************************************************************/
/**
 *  @file   Application.h
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
#ifndef KVS__OPENCABIN__APPLICATION_H_INCLUDE
#define KVS__OPENCABIN__APPLICATION_H_INCLUDE

#include <kvs/ApplicationBase>


/* In order to create the execution file (shared object file) for the OpenCABIN,
 * the name of the main function in the user program coded by using KVS rename
 * to 'kvsOpenCABINMainFunction'.
 */
#if !defined( KVS_DISABLE_OPENCABIN_MAIN_FUNCTION )
#define main kvsOpenCABINMainFunction
#endif


namespace kvs
{

namespace opencabin
{

class Application : public kvs::ApplicationBase
{
public:

    Application( int argc, char** argv );

    virtual ~Application( void );

public:

    virtual int run( void );

    virtual void quit( void );

public:

    static const std::string Name( void );

    static const bool IsDone( void );

    static const bool IsMaster( void );

    static const bool IsRenderer( void );

    static void SetAsMaster( void );

    static void SetAsRenderer( void );
};

} // end of namespace opencabin

} // end of namespace kvs

#endif // KVS__OPENCABIN__APPLICATION_H_INCLUDE
