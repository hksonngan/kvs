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
#include <kvs/opencabin/Master>

/* In order to create the execution file (shared object file) for the OpenCABIN,
 * the name of the main function in the user program coded by using KVS rename
 * to 'kvsOpenCABINMainLoop'.
 */
#if !defined( KVS_DISABLE_OPENCABIN_MAIN_LOOP )
#define main kvsOpenCABINMainLoop
#endif


namespace kvs
{

namespace opencabin
{

/*===========================================================================*/
/**
 *  @brief  Application class for OpenCABIN.
 */
/*===========================================================================*/
class Application : public kvs::ApplicationBase
{
protected:

    kvs::opencabin::Master m_master;

public:

    Application( int argc, char** argv );

    virtual ~Application( void );

public:

    kvs::opencabin::Master& master( void );

    const kvs::opencabin::Master& master( void ) const;

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
