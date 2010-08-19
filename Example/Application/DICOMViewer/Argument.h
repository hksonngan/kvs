/*****************************************************************************/
/**
 *  @file   Argument.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef __ARGUMENT_H__
#define __ARGUMENT_H__

#include <kvs/CommandLine>


/*===========================================================================*/
/**
 *  @brief  Argument class.
 */
/*===========================================================================*/
class Argument : public kvs::CommandLine
{
public:

    Argument( int argc, char** argv );
};

#endif // __ARGUMENT_H__
