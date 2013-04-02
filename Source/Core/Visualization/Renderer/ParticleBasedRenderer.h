/*****************************************************************************/
/**
 *  @file   ParticleBasedRenderer.h
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
#ifndef KVS__PARTICLE_BASED_RENDERER_H_INCLUDE
#define KVS__PARTICLE_BASED_RENDERER_H_INCLUDE

#include "ParticleBasedRendererCPU.h"
//#include "ParticleBasedRendererGPU.h"

namespace kvs
{

typedef cpu::ParticleBasedRenderer ParticleBasedRenderer;
//typedef gpu::ParticleBasedRenderer ParticleBasedRenderer;

} // end of namespace kvs

#endif // KVS__PARTICLE_BASED_RENDERER_H_INCLUDE
