/*****************************************************************************/
/**
 *  @file   Argument.h
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
#ifndef KVSVIEW__ARGUMENT_H_INCLUDE
#define KVSVIEW__ARGUMENT_H_INCLUDE

#include <kvs/CommandLine>
#include <kvs/VisualizationPipeline>
#include <kvs/glut/Global>
#include <kvs/glut/Screen>
#include <string>


namespace kvsview
{

/*===========================================================================*/
/**
 *  Argument class.
 */
/*===========================================================================*/
class Argument : public kvs::CommandLine
{
public:

    class Common;

public:

    Argument( int argc, char** argv );
};

/*===========================================================================*/
/**
 *  @brief  Common argument class.
 */
/*===========================================================================*/
class Argument::Common : public kvs::CommandLine
{
public:

    Common( int argc, char** argv );

    Common( int argc, char** argv, const std::string& command );

    bool verboseMode( void );

    void applyTo( kvs::glut::Screen& screen );

    void applyTo( kvs::glut::Global& global, kvs::VisualizationPipeline& pipe );

private:

    void set_options( void );
};

} // end of namespace kvsview

#endif // KVSVIEW__ARGUMENT_H_INCLUDE
