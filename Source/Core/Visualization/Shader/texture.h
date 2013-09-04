/*****************************************************************************/
/**
 *  @file   texture.h
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

vec4 LookupTexture( in sampler1D sampler, in float coord )
{
#if __VERSION__ >= 150
    return texture( sampler, coord );
#else
    return texture1D( sampler, coord );
#endif
}

vec4 LookupTexture( in sampler2D sampler, in vec2 coord )
{
#if __VERSION__ >= 150
    return texture( sampler, coord );
#else
    return texture2D( sampler, coord );
#endif
}

vec4 LookupTexture( in sampler3D sampler, in vec3 coord )
{
#if __VERSION__ >= 150
    return texture( sampler, coord );
#else
    return texture3D( sampler, coord );
#endif
}
