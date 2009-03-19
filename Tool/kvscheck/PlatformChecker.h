/****************************************************************************/
/**
 *  @file PlatformChecker.h
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
#ifndef KVS_KVSCHECK_PLATFORM_CHECKER_H_INCLUDE
#define KVS_KVSCHECK_PLATFORM_CHECKER_H_INCLUDE

#include <string>
#include <iostream>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Platform checker class.
 */
/*==========================================================================*/
class PlatformChecker
{
protected:

    std::string m_name; ///< platform name
    std::string m_cpu;  ///< CPU name

public:

    PlatformChecker( void );

public:

    const std::string& name( void ) const;

    const std::string& cpu( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const PlatformChecker& checker );
};

} // end of namespace kvscheck

#endif // KVS_KVSCHECK_PLATFORM_CHECKER_H_INCLUDE
