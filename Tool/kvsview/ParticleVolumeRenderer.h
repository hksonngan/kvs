/*****************************************************************************/
/**
 *  @file   ParticleVolumeRenderer.h
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
#ifndef KVSVIEW__PARTICLE_VOLUME_RENDERER_H_INCLUDE
#define KVSVIEW__PARTICLE_VOLUME_RENDERER_H_INCLUDE

#include <string>
#include <kvs/Type>
#include <kvs/CommandLine>
#include <kvs/TransferFunction>
#include "Argument.h"


namespace kvsview
{

namespace ParticleVolumeRenderer
{

const std::string CommandName("ParticleVolumeRenderer");
const std::string Description("Rendering a volume object. (optional)");

/*===========================================================================*/
/**
 *  Argument class for the ParticleVolumeRenderer.
 */
/*===========================================================================*/
class Argument : public kvsview::Argument::Common
{
public:

    Argument( int argc, char** argv );

public:

    const int shader( void ) const;

    const bool noShading( void ) const;

    const bool noLOD( void ) const;

    const bool noGPU( void ) const;

    const float ambient( void ) const;

    const float diffuse( void ) const;

    const float specular( void ) const;

    const float shininess( void ) const;

    const size_t subpixelLevel( void ) const;

    const size_t repetitionLevel( void ) const;

    const kvs::TransferFunction transferFunction( void ) const;
};

/*===========================================================================*/
/**
 *  Main class for the ParticleVolumeRenderer.
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

} // end of namespace ParticleVolumeRenderer

} // end of namespace kvsview

#endif // KVSVIEW__PARTICLE_VOLUME_RENDERER_H_INCLUDE
