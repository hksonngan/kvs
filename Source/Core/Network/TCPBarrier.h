/*****************************************************************************/
/**
 *  @file   TCPBarrier.h
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
#ifndef KVS__TCP_BARRIER_H_INCLUDE
#define KVS__TCP_BARRIER_H_INCLUDE

#include <kvs/Mutex>
#include <kvs/IPAddress>
#include <kvs/TCPSocket>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  TCPBarrier class.
 */
/*===========================================================================*/
class TCPBarrier
{
protected:

    kvs::TCPSocket* m_client; //< barrier client node
    kvs::Mutex m_mutex; //< mutex

public:

    TCPBarrier( const kvs::IPAddress& ip, int port );
    virtual ~TCPBarrier();

    void wait();
};

} // end of namespace kvs

#endif // KVS__TCP_BARRIER_H_INCLUDE
