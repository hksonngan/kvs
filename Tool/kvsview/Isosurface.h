/*****************************************************************************/
/**
 *  @file   Isosurface.h
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
#ifndef KVSVIEW__ISOSURFACE_H_INCLUDE
#define KVSVIEW__ISOSURFACE_H_INCLUDE

#include <string>
#include <kvs/Type>
#include <kvs/CommandLine>
#include <kvs/PolygonObject>
#include <kvs/VolumeObjectBase>
#include <kvs/TransferFunction>
#include <kvs/glut/Slider>
#include "Argument.h"


namespace kvsview
{

namespace Isosurface
{

const std::string CommandName("Isosurface");
const std::string Description("Extract surfaces using Isosurface. (optional)");

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

    const kvs::Real64 isolevel( const kvs::VolumeObjectBase* volume, const kvs::TransferFunction& transfer_function );

    const kvs::PolygonObject::NormalType normalType( void );

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

} // end of namespace Isosurface

} // end of namespace kvsview

#endif // KVSVIEW__ISOSURFACE_H_INCLUDE
