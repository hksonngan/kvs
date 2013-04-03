/*****************************************************************************/
/**
 *  @file   ParticleBasedRendererGPU.h
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
#ifndef KVS__GPU__PARTICLE_BASED_RENDERER_H_INCLUDE
#define KVS__GPU__PARTICLE_BASED_RENDERER_H_INCLUDE

#include "ParticleBasedRendererKU.h"
#include "ParticleBasedRendererRITS.h"


namespace kvs
{

namespace gpu
{


typedef ku::ParticleBasedRenderer ParticleBasedRenderer;
//typedef rits::ParticleBasedRenderer ParticleBasedRenderer;

} // end of namespace gpu

} // end of namespace kvs

#endif // KVS__GPU__PARTICLE_BASED_RENDERER_H_INCLUDE
