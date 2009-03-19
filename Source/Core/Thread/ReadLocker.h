/****************************************************************************/
/**
 *  @file ReadLocker.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_READ_LOCKER_H_INCLUDE
#define KVS_CORE_READ_LOCKER_H_INCLUDE

#include <kvs/ClassName>


namespace kvs
{

class ReadWriteLock;

/*==========================================================================*/
/**
 *  Read locker class.
 */
/*==========================================================================*/
class ReadLocker
{
    kvsClassName( ReadLocker );

protected:

    kvs::ReadWriteLock* m_rwlock; ///< pointer to read-write lock

public:

    ReadLocker( kvs::ReadWriteLock* rwlock );

    virtual ~ReadLocker( void );

public:

    void relock( void );

    void unlock( void );

    kvs::ReadWriteLock* readWriteLock( void );
};

} // end of namespace kvs

#endif // KVS_CORE_READ_LOCKER_H_INCLUDE
