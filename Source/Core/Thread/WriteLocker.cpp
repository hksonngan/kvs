/****************************************************************************/
/**
 *  @file WriteLocker.cpp
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
#include "WriteLocker.h"
#include "ReadWriteLock.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param rwlock [in] pointer to read/write lock
 */
/*==========================================================================*/
WriteLocker::WriteLocker( kvs::ReadWriteLock* rwlock )
    : m_rwlock( rwlock )
{
    this->relock();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
WriteLocker::~WriteLocker()
{
    this->unlock();
}

/*==========================================================================*/
/**
 *  Relock.
 */
/*==========================================================================*/
void WriteLocker::relock()
{
    if ( m_rwlock ) { m_rwlock->lockWrite(); }
}

/*==========================================================================*/
/**
 *  Unlock.
 */
/*==========================================================================*/
void WriteLocker::unlock()
{
    if ( m_rwlock ) { m_rwlock->unlock(); }
}

/*==========================================================================*/
/**
 *  Get pointer to the read/write lock.
 *  @return pointer to the read/write lock
 */
/*==========================================================================*/
kvs::ReadWriteLock* WriteLocker::readWriteLock()
{
    return( m_rwlock );
}

} // end of namespace kvs
