/****************************************************************************/
/**
 *  @file MutexLocker.h
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
#ifndef KVS__MUTEX_LOCKER_H_INCLUDE
#define KVS__MUTEX_LOCKER_H_INCLUDE


namespace kvs
{

class Mutex;

/*==========================================================================*/
/**
 *  Mutex locker class.
 */
/*==========================================================================*/
class MutexLocker
{
protected:

    kvs::Mutex* m_mutex; ///< pointer to mutex

public:

    MutexLocker( kvs::Mutex* mutex );
    virtual ~MutexLocker();

    void relock();
    void unlock();
    Mutex* mutex();
};

} // end of namespace kvs

#endif // KVS__MUTEX_LOCKER_H_INCLUDE
