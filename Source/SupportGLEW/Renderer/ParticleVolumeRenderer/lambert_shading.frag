/*****************************************************************************/
/**
 *  @file   lambert_shading.frag
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

varying vec3 position;
varying vec3 normal;

varying vec2 centerCoord;
varying float radius;


/*===========================================================================*/
/**
 *  @brief  Calculates a shaded color of the particle with Lambert shading.
 */
/*===========================================================================*/
void main( void )
{
    // Discard a pixel outside circle.
    if ( radius > 0.0 )
    {
        if( distance( gl_FragCoord.xy, centerCoord ) > radius ) discard;
    }

    // Light position.
    vec3 light_position = gl_LightSource[0].position.xyz;

    // Light vector (L) and Normal vector (N)
    vec3 L = normalize( light_position - position );
    vec3 N = normalize( gl_NormalMatrix * normal );
    float dd = max( dot( N, L ), 0.0 );

    // I = Ia + Id
    float Ia = Ka;
    float Id = Kd * dd;

    gl_FragColor.xyz = gl_Color.xyz * ( Ia + Id );
    gl_FragColor.w = 1.0;
}
