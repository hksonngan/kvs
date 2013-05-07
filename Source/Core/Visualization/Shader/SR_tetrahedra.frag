/*****************************************************************************/
/**
 *  @file   tetrahedra.frag
 *  @author Jun Nishimura
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
#include "shading.h"

// Input parameters from geometry shader
varying vec3 position;
varying vec3 normal;
varying vec2 random_index;
#if defined( ENABLE_EXACT_DEPTH_TESTING )
varying float depth_front;
varying float depth_back;
#endif
varying float scalar_front;
varying float scalar_back;
varying float distance;

// Uniform parameters.
uniform sampler3D preintegration_texture;
uniform sampler2D random_texture;
#if defined( ENABLE_EXACT_DEPTH_TESTING )
uniform sampler2D depth_texture;
#endif
uniform vec2 screen_scale;
uniform vec2 screen_scale_inv;
uniform vec2 preintegration_scale_offset;
uniform float random_texture_size_inv;
uniform vec2 random_offset;
uniform Shading shading;


/*===========================================================================*/
/**
 *  @brief  Main function of fragment shader.
 */
/*===========================================================================*/
void main()
{
#if defined( ENABLE_EXACT_DEPTH_TESTING )
    vec4 lutdata;
    vec2 screen_coord = gl_FragCoord.xy * screen_scale_inv;
    float geom_d = texture2D( depth_texture, screen_coord ).x;
    if ( geom_d < 1.0 && depth_front <= geom_d && geom_d <= depth_back )
    {
        float ratio = ( geom_d - depth_front ) / ( depth_back - depth_front );
        vec3 lutcoord = vec3( scalar_front, ( 1.0 - ratio ) * scalar_front + ratio * scalar_back, ratio * distance );
        lutdata = texture3D( preintegration_texture, lutcoord );
    }
    else
    {
        vec3 lutcoord = vec3( scalar_front, scalar_back, distance );
        lutdata = texture3D( preintegration_texture, lutcoord );
    }
#else
    vec3 lutcoord = vec3( scalar_front, scalar_back, distance );
    vec4 lutdata = texture3D( preintegration_texture, lutcoord );
#endif
    if ( lutdata.a == 0.0 ) { discard; return; }

    vec2 random_position = ( vec2( float( int( random_index.x ) * 73 ), float( int( random_index.y ) * 31 ) ) 
                + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;

    float randf = texture2D( random_texture, random_position ).x;
    if ( randf > lutdata.a ) { discard; return; }

    vec3 frag_color = lutdata.xyz / lutdata.a;

    // Light position.
    vec3 light_position = gl_LightSource[0].position.xyz;

    // Light vector (L) and Normal vector (N)
    vec3 L = normalize( light_position - position );
    vec3 N = normalize( normal );

#if   defined( ENABLE_LAMBERT_SHADING )
    vec3 shaded_color = ShadingLambert( shading, frag_color, L, N );

#elif defined( ENABLE_PHONG_SHADING )
    vec3 V = normalize( - position );
    vec3 shaded_color = ShadingPhong( shading, frag_color, L, N, V );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
    vec3 V = normalize( - position );
    vec3 shaded_color = ShadingBlinnPhong( shading, frag_color, L, N, V );

#else // DISABLE SHADING
    vec3 shaded_color = ShadingNone( shading, frag_color );
#endif

    gl_FragColor = vec4( shaded_color, 1.0 );
#if defined( ENABLE_EXACT_DEPTH_TESTING )
    gl_FragDepth = depth_front;
#endif
}
