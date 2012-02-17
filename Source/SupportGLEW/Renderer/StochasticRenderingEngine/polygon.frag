/*****************************************************************************/
/**
 *  @file   polygon.frag
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

#if defined( ENABLE_EXACT_DEPTH_TESTING )
varying float depth;
#endif

uniform sampler2D random_texture;

uniform vec2 screen_scale;
uniform vec2 screen_scale_inv;

uniform float random_texture_size_inv;
uniform vec2 random_offset;

uniform Shading shading;

void main( void )
{
    if ( gl_Color.a == 0.0 ) { discard; return; }

    if ( gl_Color.a < 0.99999 )
    {
        vec2 random_position = ( vec2( float( int( id.x ) * 73 ), float( int( id.y ) * 31 ) ) 
                    + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;

        float randf = texture2D( random_texture, random_position ).a;
        if ( randf > gl_Color.a ) { discard; return; }
    }

    vec3 frag_color = gl_Color.rgb;

    // Light position.
    vec3 light_position = gl_LightSource[0].position.xyz;

    // Light vector (L) and Normal vector (N)
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
