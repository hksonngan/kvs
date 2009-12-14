/*****************************************************************************/
/**
 *  @file   SizeofChecker.h
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
#ifndef KVSCHECK__SIZEOF_CHECKER_H_INCLUDE
#define KVSCHECK__SIZEOF_CHECKER_H_INCLUDE

#include <iostream>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  'sizeof' checker class.
 */
/*==========================================================================*/
class SizeofChecker
{
public:

    SizeofChecker( void );

public:

    template <typename T>
    const size_t sizeOf( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const SizeofChecker& checker );
};

template <typename T>
inline const size_t SizeofChecker::sizeOf( void ) const
{
    return( sizeof( T ) );
}

} // end of namespace kvscheck

#endif // KVSCHECK__SIZEOF_CHECKER_H_INCLUDE
