/*****************************************************************************/
/**
 *  @file   uniform_grid.frag
 *  @author Naoya Maeda
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

vec3 estimateGradient( in sampler3D v, in vec3 p, in vec3 o )
{
    float s0 = texture3D( v, p + vec3( o.x, 0.0, 0.0 ) ).x;
    float s1 = texture3D( v, p + vec3( 0.0, o.y, 0.0 ) ).x;
    float s2 = texture3D( v, p + vec3( 0.0, 0.0, o.z ) ).x;
    float s3 = texture3D( v, p - vec3( o.x, 0.0, 0.0 ) ).x;
    float s4 = texture3D( v, p - vec3( 0.0, o.y, 0.0 ) ).x;
    float s5 = texture3D( v, p - vec3( 0.0, 0.0, o.z ) ).x;

    return( vec3( s3 - s0, s4 - s1, s5 - s2 ) );
}

varying vec3 position;

#if defined( ENABLE_EXACT_DEPTH_TESTING )
varying float depth;
#endif

uniform sampler2D random_texture;
uniform sampler3D volume_texture;
uniform sampler2D preintegration_texture;
uniform vec3 volume_resolution_inv;

uniform vec2 screen_scale; // not used
uniform vec2 screen_scale_inv; // not used

uniform float random_texture_size_inv;
uniform vec2 random_offset;

uniform Shading shading;
const float distance = 0.02;

void main()
{
    vec3 tex = gl_TexCoord[0].xyz;

    if ( tex.x < 0.0 || tex.x > 1.0 || tex.y < 0.0 || tex.y > 1.0 || tex.z < 0.0 || tex.z > 1.0 )
    { discard; return; }

    vec3 dis = position;
    dis = normalize( dis ) * distance;
    float scalar_back = texture3D( volume_texture, tex + dis ).r;
    float scalar_front = texture3D( volume_texture, tex - dis ).r;

    vec2 lutcoord = vec2( scalar_front, scalar_back );
    vec4 color = texture2D( preintegration_texture, lutcoord );
    color.a = 1.0 - exp( - 1.0 * color.a );
    color.rgb = 1.0 * color.rgb;

    // a(sf, sb, d) = 1 - exp( - d / ( sb - sf ) * ( A(sf) - A(sb) ) )
    // c(sf, sb, d) = d / ( sb - sf ) * ( C(sb) - C(sf) )

    if ( color.a == 0.0 ) { discard; return; }

    if ( color.a < 0.99999 )
    {
        vec2 random_position = ( random_offset + gl_FragCoord.xy ) * random_texture_size_inv;
        float randf = texture2D( random_texture, random_position ).r;
        if ( randf >= color.a ) { discard; return; }
    }

    vec3 frag_color = color.rgb / color.a;

    // Light position.
    vec3 light_position = gl_LightSource[0].position.xyz;

    // Light vector (L) and Normal vector (N)
    vec3 normal = gl_NormalMatrix * estimateGradient( volume_texture, tex, volume_resolution_inv );
    vec3 L = normalize( light_position - position );
    vec3 N = normalize( normal );

#if   defined( ENABLE_LAMBERT_SHADING )
    vec3 shaded_color = ShadingLambert( shading, frag_color, L, N );

#elif defined( ENABLE_PHONG_SHADING )
    vec3 V = normalize( -position );
    vec3 shaded_color = ShadingPhong( shading, frag_color, L, N, V );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
    vec3 V = normalize( -position );
    vec3 shaded_color = ShadingBlinnPhong( shading, frag_color, L, N, V );

#else // DISABLE SHADING
    vec3 shaded_color = ShadingNone( shading, frag_color );
#endif
    gl_FragColor = vec4( shaded_color, 1.0 );

#if defined( ENABLE_EXACT_DEPTH_TESTING )
    gl_FragDepth = depth;
#endif
}
