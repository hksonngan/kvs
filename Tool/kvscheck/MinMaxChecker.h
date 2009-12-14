/*****************************************************************************/
/**
 *  @file   MinMaxChecker.h
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
#ifndef KVSCHECK__MINMAX_CHECKER_H_INCLUDE
#define KVSCHECK__MINMAX_CHECKER_H_INCLUDE

#include <iostream>
#include <kvs/Value>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Min/Max value checker class.
 */
/*==========================================================================*/
class MinMaxChecker
{
public:

    MinMaxChecker( void );

public:

    template <typename T>
    const T minValue( void ) const;

    template <typename T>
    const T maxValue( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const MinMaxChecker& checker );
};

template <typename T>
inline const T MinMaxChecker::minValue( void ) const
{
    return( kvs::Value<T>::Min() );
}

template <typename T>
inline const T MinMaxChecker::maxValue( void ) const
{
    return( kvs::Value<T>::Max() );
}

} // end of namespace kvscheck

#endif // KVSCHECK__MINMAX_CHECKER_H_INCLUDE
