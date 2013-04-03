/*****************************************************************************/
/**
 *  @file   ParticleBasedRendererGLSL.h
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
#ifndef KVS__GLSL__PARTICLE_BASED_RENDERER_H_INCLUDE
#define KVS__GLSL__PARTICLE_BASED_RENDERER_H_INCLUDE

#include "ParticleBasedRendererKU.h"
#include "ParticleBasedRendererRITS.h"


namespace kvs
{

namespace glsl
{

//typedef ku::ParticleBasedRenderer ParticleBasedRenderer;
typedef rits::ParticleBasedRenderer ParticleBasedRenderer;

} // end of namespace glsl

} // end of namespace kvs

#endif // KVS__GLSL__PARTICLE_BASED_RENDERER_H_INCLUDE
