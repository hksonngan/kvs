/****************************************************************************/
/**
 *  @file CompilerChecker.cpp
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
#include "CompilerChecker.h"
#include <kvs/Compiler>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
CompilerChecker::CompilerChecker( void )
{
    m_name    = kvs::Compiler::Name();
    m_version = kvs::Compiler::Version();
}

/*==========================================================================*/
/**
 *  Get the compiler name.
 */
/*==========================================================================*/
const std::string& CompilerChecker::name( void ) const
{
    return( m_name );
}

/*==========================================================================*/
/**
 *  Get the compiler version.
 */
/*==========================================================================*/
const std::string& CompilerChecker::version( void ) const
{
    return( m_version );
}

/*==========================================================================*/
/**
 *  Output version information.
 *  @param os [in] output stream
 *  @param checker [in] compiler checker
 */
/*==========================================================================*/
std::ostream& operator << ( std::ostream& os, const CompilerChecker& checker )
{
    os << "Compiler: " << checker.name() << " (" << checker.version() << ")";

    return( os );
}

} // end of namespace kvscheck
