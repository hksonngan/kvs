/****************************************************************************/
/**
 *  @file VersionChecker.cpp
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
#include "VersionChecker.h"
#include <kvs/Version>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
VersionChecker::VersionChecker( void )
{
    m_name = kvs::Version::Name();
}

/*==========================================================================*/
/**
 *  Get the KVS version name.
 */
/*==========================================================================*/
const std::string& VersionChecker::name( void ) const
{
    return( m_name );
}

/*==========================================================================*/
/**
 *  Output version information.
 *  @param os [in] output stream
 *  @param checker [in] version checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const VersionChecker& checker )
{
    os << "KVS version: " << checker.name();

    return( os );
}

} // end of namespace kvscheck
