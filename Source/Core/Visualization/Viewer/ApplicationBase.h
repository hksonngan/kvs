/*****************************************************************************/
/**
 *  @file   ApplicationBase.h
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
#ifndef KVS__APPLICATION_BASE_H_INCLUDE
#define KVS__APPLICATION_BASE_H_INCLUDE

#include <kvs/ScreenBase>
#include <list>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  ApplicationBase class.
 */
/*===========================================================================*/
class ApplicationBase
{
protected:

    int m_argc;    ///< argument count
    char** m_argv; ///< argument values

    std::list<kvs::ScreenBase*> m_screens; ///< list of the pointer to the screen

public:

    ApplicationBase( int argc, char** argv );

    virtual ~ApplicationBase( void );

public:

    void attach( kvs::ScreenBase* screen );

    void detach( kvs::ScreenBase* screen );

    virtual int run( void ) = 0;

    virtual void quit( void ) = 0;
};

} // end of namespace kvs

#endif // KVS__APPLICATION_BASE_H_INCLUDE
