/*****************************************************************************/
/**
 *  @file   line.frag
 *  @author Jun Nishimura, Naohisa Sakamoto
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
// Input.
varying vec3 position;
varying vec2 index;
varying float depth;

// Uniform.
uniform sampler2D random_texture;
uniform float random_texture_size_inv;
uniform vec2 random_offset;
uniform float opacity;

vec2 RandomIndex( in vec2 p )
{
    float x = float( int( index.x ) * 73 );
    float y = float( int( index.y ) * 31 );
    return ( vec2( x, y ) + random_offset + p ) * random_texture_size_inv;
}

void main()
{
    if ( opacity == 0.0 ) { discard; return; }

    // Stochastic color assignment.
    float R = texture2D( random_texture, RandomIndex( gl_FragCoord.xy ) ).a;
    if ( R > opacity ) { discard; return; }

    gl_FragColor = vec4( gl_Color.rgb, 1.0 );
    gl_FragDepth = depth;
}
