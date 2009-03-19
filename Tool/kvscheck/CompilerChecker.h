/****************************************************************************/
/**
 *  @file CompilerChecker.h
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
#ifndef KVS_KVSCHECK_COMPILER_CHECKER_H_INCLUDE
#define KVS_KVSCHECK_COMPILER_CHECKER_H_INCLUDE

#include <string>
#include <iostream>


namespace kvscheck
{

/*==========================================================================*/
/**
 *  Compiler checker class.
 */
/*==========================================================================*/
class CompilerChecker
{
protected:

    std::string m_name;    ///< compiler name
    std::string m_version; ///< compiler version

public:

    CompilerChecker( void );

public:

    const std::string& name( void ) const;

    const std::string& version( void ) const;

    friend std::ostream& operator << ( std::ostream& os, const CompilerChecker& checker );
};

} // end of namespace kvscheck

#endif // KVS_KVSCHECK_COMPILER_CHECKER_H_INCLUDE
