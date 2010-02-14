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
 *  $Id$
 */
/*****************************************************************************/
#include "../Shader/shading.h"
#include "../Shader/volume.h"
#include "../Shader/transfer_function.h"

uniform sampler2D        entry_points;      // entry points (front face)
uniform sampler2D        exit_points;       // exit points (back face)
uniform vec3             offset;            // offset width for the gradient
uniform float            dt;                // sampling step
uniform float            opaque;            // opaque value
uniform vec3             light_position;    // light position in the object coordinate
uniform vec3             camera_position;   // camera position in the object coordinate
uniform Volume           volume;            // volume data
uniform Shading          shading;            // shading parameter
uniform TransferFunction transfer_function; // 1D transfer function


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

void main( void )
{
    // Entry and exit point.
    vec3 entry_point = volume.ratio * texture2D( entry_points, gl_TexCoord[0].st ).xyz;
    vec3 exit_point = volume.ratio * texture2D( exit_points, gl_TexCoord[0].st ).xyz;
    if ( entry_point == exit_point ) { discard; } // out of cube

    // Ray direction.
    vec3 direction = dt * normalize( exit_point - entry_point );
    float segment = distance( exit_point, entry_point );
    int nsteps = int( floor( segment / dt ) );

    // Ray traversal.
    vec3 position = entry_point;
    vec4 dst = vec4( 0.0, 0.0, 0.0, 0.0 );

    // Transfer function scale.
    float tfunc_scale = 1.0 / ( volume.max_value - volume.min_value );

    for ( int i = 0; i < nsteps; i++ )
    {
        // Get the scalar value from the 3D texture.
        vec3 volume_index = vec3( position / volume.ratio );
        vec4 value = texture3D( volume.data, volume_index );
        float scalar = mix( volume.min_range, volume.max_range, value.w );

        // Get the source color from the transfer function.
        float tfunc_index = ( scalar - volume.min_value ) * tfunc_scale;
        vec4 src = texture1D( transfer_function.data, tfunc_index );
        if ( src.a != 0.0 )
        {
            // Get the normal vector.
            vec3 offset_index = vec3( offset / volume.ratio );
            vec3 normal = estimateGradient( volume.data, volume_index, offset_index );

            vec3 L = normalize( light_position - position );
            vec3 N = normalize( gl_NormalMatrix * normal );

#if   defined( ENABLE_LAMBERT_SHADING )
            src.rgb = ShadingLambert( shading, src.rgb, L, N );

#elif defined( ENABLE_PHONG_SHADING )
            src.rgb = ShadingPhong( shading, src.rgb, L, N );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
            vec3 C = normalize( camera_position - position );
            src.rgb = ShadingBlinnPhong( shading, src.rgb, L, N, C );

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
                i = nsteps; // break
            }
        }

        position += direction;
    }

    gl_FragColor = dst;
}
