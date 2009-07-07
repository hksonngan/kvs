/*****************************************************************************/
/**
 *  @file   phong_shading.frag
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

    // Light vector (L), Normal vector (N) and Reflection vector (R).
    vec3 L = normalize( gl_LightSource[0].position.xyz - position );
    vec3 N = normalize( gl_NormalMatrix * normal );
    vec3 R = 2.0 * dot( N, L ) * N - L;
    float dd = max( dot( N, L ), 0.0 );
    float ds = pow( max( dot( N, R ), 0.0 ), S );
//    float ds = pow( max( dot( N, R ), 0.0 ), gl_FrontMaterial.shininess );

    // I = Ia + Id + Is
    vec3 Ia = vec3( Ka, Ka, Ka );
    vec3 Id = vec3( Kd, Kd, Kd ) * dd;
    vec3 Is = vec3( Ks, Ks, Ks ) * ds;
//    vec3 Ia = vec3( Ka, Ka, Ka ) * gl_LightSource[0].ambient.rgb;
//    vec3 Id = vec3( Kd, Kd, Kd ) * gl_LightSource[0].diffuse.rgb * dd;
//    vec3 Is = vec3( Ks, Ks, Ks ) * gl_LightSource[0].specular.rgb * ds;

    gl_FragColor.xyz = gl_Color.xyz * ( Ia + Id + Is );
    gl_FragColor.w = 1.0;
}
