/*****************************************************************************/
/**
 *  @file   blinn_phong_shading.frag
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
uniform sampler2D randomTexture;
uniform float randomTextureSizeInv;
uniform float Ka;
uniform float Kd;
uniform float Ks;
uniform float S;

varying vec3 position;
varying vec3 normal;

varying vec2 centerCoord;
varying float radius;


/*===========================================================================*/
/**
 *  @brief  Calculates a shaded color of the particle with Phong shading.
 */
/*===========================================================================*/
void main( void )
{
    // Discard a pixel outside circle.
    if ( radius > 0.0 )
    {
        if( distance( gl_FragCoord.xy, centerCoord ) > radius ) discard;
    }

    // Light vector (L), Normal vector (N) and Halfway vector (H).
    vec3 C = normalize( position );
    vec3 L = normalize( gl_LightSource[0].position.xyz - position );
    vec3 N = normalize( gl_NormalMatrix * normal );
    vec3 H = normalize( L + C );
    float dd = max( dot( L, N ), 0.0 );
    float ds = pow( max( dot( H, N ), 0.0 ), S );

    // I = Ia + Id + Is
    float Ia = Ka;
    float Id = Kd * dd;
    float Is = Ks * ds;

    gl_FragColor.xyz = gl_Color.xyz * ( Ia + Id + Is );
    gl_FragColor.w = 1.0;
}
