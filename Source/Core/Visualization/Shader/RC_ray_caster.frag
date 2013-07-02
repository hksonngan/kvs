/*****************************************************************************/
/**
 *  @file   ray_caster.frag
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ray_caster.frag 1041 2012-03-14 15:28:49Z naohisa.sakamoto@gmail.com $
 */
/*****************************************************************************/
#include "shading.h"
#include "volume.h"
#include "transfer_function.h"

uniform sampler2D        entry_points;      // entry points (front face)
uniform sampler2D        exit_points;       // exit points (back face)
uniform vec3             offset;            // offset width for the gradient
uniform float            dt;                // sampling step
uniform float            opaque;            // opaque value
uniform vec3             light_position;    // light position in the object coordinate
uniform vec3             camera_position;   // camera position in the object coordinate
uniform Volume           volume;            // volume data
uniform Shading          shading;           // shading parameter
uniform TransferFunction transfer_function; // 1D transfer function
uniform sampler2D        jittering_texture; // texture for jittering
uniform float            width;             // screen width
uniform float            height;            // screen height
uniform sampler2D        depth_texture;     // depth texture for depth buffer
uniform sampler2D        color_texture;     // color texture for color buffer
uniform float            to_zw1;            // scaling parameter: (f*n)/(f-n)
uniform float            to_zw2;            // scaling parameter: 0.5*((f+n)/(f-n))+0.5
uniform float            to_ze1;            // scaling parameter: 0.5 + 0.5*((f+n)/(f-n))
uniform float            to_ze2;            // scaling parameter: (f-n)/(f*n)


vec3 estimateGradient( in sampler3D v, in vec3 p, in vec3 o )
{
    float s0 = texture3D( v, p + vec3( o.x, 0.0, 0.0 ) ).w;
    float s1 = texture3D( v, p + vec3( 0.0, o.y, 0.0 ) ).w;
    float s2 = texture3D( v, p + vec3( 0.0, 0.0, o.z ) ).w;
    float s3 = texture3D( v, p - vec3( o.x, 0.0, 0.0 ) ).w;
    float s4 = texture3D( v, p - vec3( 0.0, o.y, 0.0 ) ).w;
    float s5 = texture3D( v, p - vec3( 0.0, 0.0, o.z ) ).w;

    return( vec3( s3 - s0, s4 - s1, s5 - s2 ) );
}

vec3 estimateGradient8( in sampler3D v, in vec3 p, in vec3 o )
{
    vec3 g0 = estimateGradient( v, p, o );
    vec3 g1 = estimateGradient( v, p + vec3( -o.x, -o.y, -o.z ), o );
    vec3 g2 = estimateGradient( v, p + vec3(  o.x,  o.y,  o.z ), o );
    vec3 g3 = estimateGradient( v, p + vec3( -o.x,  o.y, -o.z ), o );
    vec3 g4 = estimateGradient( v, p + vec3(  o.x, -o.y,  o.z ), o );
    vec3 g5 = estimateGradient( v, p + vec3( -o.x, -o.y,  o.z ), o );
    vec3 g6 = estimateGradient( v, p + vec3(  o.x,  o.y, -o.z ), o );
    vec3 g7 = estimateGradient( v, p + vec3( -o.x,  o.y,  o.z ), o );
    vec3 g8 = estimateGradient( v, p + vec3(  o.x, -o.y, -o.z ), o );
    vec3 mix0 = mix( mix( g1, g2, 0.5 ), mix( g3, g4, 0.5 ), 0.5 );
    vec3 mix1 = mix( mix( g5, g6, 0.5 ), mix( g7, g8, 0.5 ), 0.5 );

    return( mix( g0, mix( mix0, mix1, 0.5 ), 0.75 ) );
}

float ray_depth( in float t, in float entry_depth, in float exit_depth )
{
    float zw_front = entry_depth;
    float ze_front = 1.0 / ((zw_front - to_ze1)*to_ze2);

    float zw_back = exit_depth;
    float ze_back = 1.0 / ((zw_back - to_ze1)*to_ze2);

    float ze_current = ze_front + t * (ze_back - ze_front);
    float zw_current = (1.0/ze_current)*to_zw1 + to_zw2;

    return zw_current;
}

void main()
{
    // Entry and exit point.
    vec2 index = vec2( gl_FragCoord.x / width, gl_FragCoord.y / height );
    vec3 entry_point = ( volume.resolution - vec3(1.0) ) * texture2D( entry_points, index ).xyz;
    vec3 exit_point = ( volume.resolution - vec3(1.0) ) * texture2D( exit_points, index ).xyz;
    if ( entry_point == exit_point ) { discard; } // out of volume

    // Ray direction.
    vec3 direction = dt * normalize( exit_point - entry_point );

    // Stochastic jittering.
#if defined( ENABLE_JITTERING )
    entry_point = entry_point + 0.1 * direction * texture2D( jittering_texture, gl_FragCoord.xy / 32.0 ).x;
#endif

    // Ray traversal.
    float segment = distance( exit_point, entry_point );
    int nsteps = int( floor( segment / dt ) );
    vec3 position = entry_point;
    vec4 dst = vec4( 0.0, 0.0, 0.0, 0.0 );

    // Transfer function scale.
    float tfunc_scale = 1.0 / ( transfer_function.max_value - transfer_function.min_value );

    float entry_depth = texture2D( entry_points, index ).w;
    float exit_depth = texture2D( exit_points, index ).w;
    float depth0 = texture2D( depth_texture, index ).x;
    vec3 color0 = texture2D( color_texture, index ).rgb;
    int i = 0;
    do
    {
        // Get the scalar value from the 3D texture.
        //     NOTE: The volume index which is a index to access the volume data
        //     represented as 3D texture can be calculate as follows:
        //
        //         vec3 A = ( R - vec3(1.0) ) / R; // ajusting parameter
        //         vec3 I = vec3( P + vec3(0.5) ) * A / ( R - vec3(1.0) );
        //                = vec3( P + vec3(0.5) ) / R;
        //
        //     where, I: volume index, P: position, R: volume resolution.
        vec3 volume_index = vec3( ( position + vec3(0.5) ) / volume.resolution );
        vec4 value = texture3D( volume.data, volume_index );
        float scalar = mix( volume.min_range, volume.max_range, value.w );

        // Get the source color from the transfer function.
        float tfunc_index = ( scalar - transfer_function.min_value ) * tfunc_scale;
        vec4 src = texture1D( transfer_function.data, tfunc_index );
        if ( src.a != 0.0 )
        {
            // Get the normal vector.
            vec3 offset_index = vec3( volume.resolution_reciprocal );
            vec3 normal = estimateGradient( volume.data, volume_index, offset_index );

            vec3 L = normalize( light_position - position );
            vec3 N = normalize( gl_NormalMatrix * normal );

#if   defined( ENABLE_LAMBERT_SHADING )
            src.rgb = ShadingLambert( shading, src.rgb, L, N );

#elif defined( ENABLE_PHONG_SHADING )
            vec3 V = normalize( camera_position - position );
            src.rgb = ShadingPhong( shading, src.rgb, L, N, V );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
            vec3 V = normalize( camera_position - position );
            src.rgb = ShadingBlinnPhong( shading, src.rgb, L, N, V );

#else // DISABLE SHADING
            src.rgb = ShadingNone( shading, src.rgb );
#endif

            // Front-to-back composition.
            dst.rgb += ( 1.0 - dst.a ) * src.a * src.rgb;
            dst.a += ( 1.0 - dst.a ) * src.a;

            // Early ray termination.
            if ( dst.a > opaque )
            {
                dst.a = 1.0;
                break; // break
            }
        }

        float t = float(i) / float( nsteps - 1 );
        float depth = ray_depth( t, entry_depth, exit_depth );
        if ( depth > depth0 )
        {
            dst.rgb += ( 1.0 - dst.a ) * color0.rgb;
            dst.a = 1.0;
            break;
        }

        position += direction;
    } while ( i++ < nsteps );

    gl_FragColor = dst;
}
