/*****************************************************************************/
/**
 *  @file   Global.h
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
#if 0


#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <string>
#include <kvs/glut/GlobalBase>
#include "Parameter.h"
#include "Argument.h"


/*===========================================================================*/
/**
 *  @brief  Global class.
 */
/*===========================================================================*/
class Global : public kvs::glut::GlobalBase
{
public:

    static Parameter parameter; ///< global parameter set

public:

    Global( int count, char** values );

private:

    const bool read_arguments( Argument& arg );

    const bool read_from_file( const std::string& name );

    const bool read_from_directory( const std::string& name, const bool extension_check );
};

#endif // __GLOBAL_H__

#endif
