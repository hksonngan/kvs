/*****************************************************************************/
/**
 *  @file   PointRenderer.h
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
#ifndef KVSVIEW__POINT_RENDERER_H_INCLUDE
#define KVSVIEW__POINT_RENDERER_H_INCLUDE

#include <string>
#include <kvs/CommandLine>
#include "Argument.h"


namespace kvsview
{

namespace PointRenderer
{

const std::string CommandName("PointRenderer");
const std::string Description("Rendering a point object. (optional)");

/*===========================================================================*/
/**
 *  Argument class for a fld2kvsml.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );
};

/*===========================================================================*/
/**
 *  Main class for a fld2kvsml.
 */
/*===========================================================================*/
class Main
{
protected:

    int         m_argc;         ///< argument count
    char**      m_argv;         ///< argument values
    std::string m_input_name;   ///< input filename
    std::string m_output_name;  ///< output filename

public:

    Main( int argc, char** argv );

public:

    const bool exec( void );
};

} // end of namespace PointRenderer

} // end of namespace kvsview

#endif // KVSVIEW__POINT_RENDERER_H_INCLUDE