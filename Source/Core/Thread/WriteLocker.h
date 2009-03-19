/****************************************************************************/
/**
 *  @file WriteLocker.h
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
#ifndef KVS_CORE_WRITE_LOCKER_H_INCLUDE
#define KVS_CORE_WRITE_LOCKER_H_INCLUDE

#include <kvs/ClassName>


namespace kvs
{

class ReadWriteLock;

/*==========================================================================*/
/**
 *  Write locker class.
 */
/*==========================================================================*/
class WriteLocker
{
    kvsClassName( WriteLocker );

protected:

    kvs::ReadWriteLock* m_rwlock; ///< pointer to read-write lock

public:

    WriteLocker( kvs::ReadWriteLock* rwlock );

    virtual ~WriteLocker( void );

public:

    void relock( void );

    void unlock( void );

    kvs::ReadWriteLock* readWriteLock( void );
};

} // end of namespace kvs

#endif // KVS_CORE_WRITE_LOCKER_H_INCLUDE
