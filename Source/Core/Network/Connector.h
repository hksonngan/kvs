/*****************************************************************************/
/**
 *  @file   Connector.h
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
#ifndef KVS__CONNECTOR_H_INCLUDE
#define KVS__CONNECTOR_H_INCLUDE

#include <kvs/TCPSocket>
#include <kvs/IPAddress>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Connector class.
 */
/*===========================================================================*/
class Connector
{
private:

    kvs::TCPSocket*  m_handler; //< handler
    kvs::IPAddress   m_ip;      //< IP address
    int              m_port;    //< port number
    size_t           m_ntrials; //< number of trials

public:

    Connector( void );

    Connector( kvs::TCPSocket* handler );

    Connector( const kvs::IPAddress& ip, const int port, const size_t ntrials );

    ~Connector( void );

public:

    const bool open( void );

    void close( void );

    const bool connect( const kvs::IPAddress& ip, const int port, const size_t ntrials );

    const bool reconnect();

    void send( const kvs::MessageBlock& block );

private:

    const bool create_handler( void );

    void delete_handler( void );
};

} // end of namespace kvs

#endif // KVS__CONNECTOR_H_INCLUDE