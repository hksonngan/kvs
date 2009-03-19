/*****************************************************************************/
/**
 *  @file   SlicePlane.h
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
#ifndef KVSVIEW__SLICE_PLANE_H_INCLUDE
#define KVSVIEW__SLICE_PLANE_H_INCLUDE

#include <string>
#include <kvs/Type>
#include <kvs/CommandLine>
#include <kvs/PolygonObject>
#include <kvs/TransferFunction>
#include "Argument.h"


namespace kvsview
{

namespace SlicePlane
{

const std::string CommandName("SlicePlane");
const std::string Description("Extract a slice plane. (optional)");

/*===========================================================================*/
/**
 *  Argument class for a fld2kvsml.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );

public:

    const kvs::Vector4f coefficients( void );

    const kvs::Vector3f point( void );

    const kvs::Vector3f normal( void );

    const kvs::TransferFunction transferFunction( void );
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

} // end of namespace SlicePlane

} // end of namespace kvsview

#endif // KVSVIEW__SLICE_PLANE_H_INCLUDE
