/*****************************************************************************/
/**
 *  @file   unstructured_volume.frag
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
#include "../Shader/shading.h"

varying vec3 position;
varying vec3 normal;
varying vec2 id;

varying float scalar_front;
varying float scalar_back;
varying float distance;

uniform sampler3D preintegration_texture;
uniform sampler2D random_texture;

uniform vec2 screen_scale;
uniform vec2 screen_scale_inv;
uniform vec2 preintegration_scale_offset;

uniform float random_texture_size_inv;
uniform vec2 random_offset;

uniform Shading shading;

void main( void )
{
    vec3 lutcoord = vec3( scalar_front, scalar_back, distance );
    vec4 lutdata = texture3D( preintegration_texture, lutcoord );
    if ( lutdata.a == 0.0 ) { discard; return; }

    vec2 random_position = ( vec2( float( int( id.x ) * 73 ), float( int( id.y ) * 31 ) ) 
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
}
