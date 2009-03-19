/*****************************************************************************/
/**
 *  @file   OrthoSlice.h
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
#ifndef KVSVIEW__ORTHO_SLICE_H_INCLUDE
#define KVSVIEW__ORTHO_SLICE_H_INCLUDE

#include <string>
#include <kvs/Type>
#include <kvs/CommandLine>
#include <kvs/PolygonObject>
#include <kvs/TransferFunction>
#include <kvs/OrthoSlice>
#include "Argument.h"


namespace kvsview
{

namespace OrthoSlice
{

const std::string CommandName("OrthoSlice");
const std::string Description("Extract a orthogonal slice plane. (optional)");

/*===========================================================================*/
/**
 *  Argument class for the OrthoSlice.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );

public:

    const kvs::OrthoSlice::AlignedAxis axis( void );

    const float position( void );

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

} // end of namespace OrthoSlice

} // end of namespace kvsview

#endif // KVSVIEW__ORTHO_SLICE_H_INCLUDE
