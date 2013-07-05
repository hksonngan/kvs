/*****************************************************************************/
/**
 *  @file   SR_line.frag
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
// Input parameters from vertex shader.
varying vec3 position; // vertex position in camera coordinate
varying vec2 index; // index for accessing to the random texture
varying float depth; // depth value of the vertex in normalized device coordinate

// Uniform parameters.
uniform sampler2D random_texture; // random texture to generate random number
uniform float random_texture_size_inv; // reciprocal value of the random texture size
uniform vec2 random_offset; // offset values for accessing to the random texture
uniform float opacity; // opacity value


/*===========================================================================*/
/**
 *  @brief  Returns random index.
 *  @param  p [in] pixel coordinate value
 *  @return random index as 2d vector
 */
/*===========================================================================*/
vec2 RandomIndex( in vec2 p )
{
    float x = float( int( index.x ) * 73 );
    float y = float( int( index.y ) * 31 );
    return ( vec2( x, y ) + random_offset + p ) * random_texture_size_inv;
}

/*===========================================================================*/
/**
 *  @brief  Main function of fragment shader.
 */
/*===========================================================================*/
void main()
{
    if ( opacity == 0.0 ) { discard; return; }

    // Stochastic color assignment.
    float R = texture2D( random_texture, RandomIndex( gl_FragCoord.xy ) ).a;
    if ( R > opacity ) { discard; return; }

    gl_FragColor = vec4( gl_Color.rgb, 1.0 );
    gl_FragDepth = depth;
}
