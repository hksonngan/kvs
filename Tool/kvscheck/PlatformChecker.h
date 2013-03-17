/****************************************************************************/
/**
 *  @file PlatformChecker.h
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
#ifndef KVSCHECK__PLATFORM_CHECKER_H_INCLUDE
#define KVSCHECK__PLATFORM_CHECKER_H_INCLUDE

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
    std::string m_cpu; ///< CPU name

public:

    PlatformChecker();

    const std::string& name() const;
    const std::string& cpu() const;
    friend std::ostream& operator << ( std::ostream& os, const PlatformChecker& checker );
};

} // end of namespace kvscheck

#endif // KVSCHECK__PLATFORM_CHECKER_H_INCLUDE
