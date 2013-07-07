/*****************************************************************************/
/**
 *  @file   tetrahedra.frag
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
#include "shading.h"

// Input parameters from geometry shader
varying vec3 position; // vertex position in camera coordinate
varying vec3 normal; // normal vector in camera coordinate
varying vec2 random_index; // index for accessing to the random texture
varying float scalar_front; // scalar value on the front face
varying float scalar_back; // scalar value on the back face
varying float distance; // distance between the front and back face
#if defined( ENABLE_EXACT_DEPTH_TESTING )
varying float depth_front; // depth value at the front face
varying float depth_back; // depth value at the back face
#endif
varying float wc_inv_front; // reciprocal value of the w-component at the front face in clip coordinate
varying float wc_inv_back; // reciprocal value of the w-component at the back face in clip coordinate

// Uniform parameters.
uniform sampler3D preintegration_texture; // pre-integration texture
uniform sampler2D random_texture; // random number texture
#if defined( ENABLE_EXACT_DEPTH_TESTING )
uniform sampler2D depth_texture; // depth texture
#endif
uniform vec2 screen_scale; // not used...
uniform vec2 screen_scale_inv; // reciprocal values of width and height of screen
uniform vec2 preintegration_scale_offset; // offset values for pre-integration table
uniform float random_texture_size_inv; // reciprocal value of random texture size
uniform vec2 random_offset; // offset values for accessing to the random texture
uniform ShadingParameter shading; // shading parameters


/*===========================================================================*/
/**
 *  @brief  Returns a random number.
 *  @return random number
 */
/*===========================================================================*/
float RandomNumber()
{
    vec2 index =
        ( vec2( float( int( random_index.x ) * 73 ), float( int( random_index.y ) * 31 ) )
          + random_offset + gl_FragCoord.xy ) * random_texture_size_inv;
    return texture2D( random_texture, index ).x;
}

/*===========================================================================*/
/**
 *  @brief  Returns pre-integrated values.
 *  @return pre-integrated values
 */
/*===========================================================================*/
vec4 LookupPreIntegration()
{
#if defined( ENABLE_EXACT_DEPTH_TESTING )
    vec2 index = gl_FragCoord.xy * screen_scale_inv;
    float depth = texture2D( depth_texture, index ).x;
    if ( depth < 1.0 && depth_front <= depth && depth <= depth_back )
    {
        float ratio = ( depth - depth_front ) / ( depth_back - depth_front );
        float Sf = scalar_front;
        float Sb = ( 1.0 - ratio ) * scalar_front + ratio * scalar_back;
        float d = ratio * distance;

        Sf /= wc_inv_front;
        Sb /= wc_inv_back;

        return texture3D( preintegration_texture, vec3( Sf, Sb, d ) );
    }
#endif

    float Sf = scalar_front;
    float Sb = scalar_back;
    float d = distance;

    Sf /= wc_inv_front;
    Sb /= wc_inv_back;

    return texture3D( preintegration_texture, vec3( Sf, Sb, d ) );
}

/*===========================================================================*/
/**
 *  @brief  Main function of fragment shader.
 */
/*===========================================================================*/
void main()
{
    vec4 preintegrated = LookupPreIntegration();
    if ( preintegrated.a == 0.0 ) { discard; return; }

    float R = RandomNumber();
    if ( R > preintegrated.a ) { discard; return; }

    vec3 color = preintegrated.xyz / preintegrated.a;

    // Light position in camera coordinate.
    vec3 light_position = gl_LightSource[0].position.xyz;

    // Light vector (L) and Normal vector (N) in camera coordinate.
    vec3 L = normalize( light_position - position );
    vec3 N = normalize( normal );

#if   defined( ENABLE_LAMBERT_SHADING )
    vec3 shaded_color = ShadingLambert( shading, color, L, N );

#elif defined( ENABLE_PHONG_SHADING )
    vec3 V = normalize( - position );
    vec3 shaded_color = ShadingPhong( shading, color, L, N, V );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
    vec3 V = normalize( - position );
    vec3 shaded_color = ShadingBlinnPhong( shading, color, L, N, V );

#else // DISABLE SHADING
    vec3 shaded_color = ShadingNone( shading, color );
#endif

    gl_FragColor = vec4( shaded_color, 1.0 );
#if defined( ENABLE_EXACT_DEPTH_TESTING )
    gl_FragDepth = depth_front;
#endif
}
