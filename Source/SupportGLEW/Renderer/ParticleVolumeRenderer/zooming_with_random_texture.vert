/*****************************************************************************/
/**
 *  @file   zooming_with_random_texture.vert
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
uniform float densityFactor;
uniform sampler2D randomTexture;
uniform float randomTextureSizeInv;
uniform int circleThreshold;
uniform vec2 screenScale;

const float circleScale = 0.564189583547756; // 1.0 / sqrt(PI)

attribute vec2 identifier;

varying vec3 position;
varying vec3 normal;

varying vec2 centerCoord;
varying float radius;


/*===========================================================================*/
/**
 *  @brief  Calculates a size of the particle.
 */
/*===========================================================================*/
void main(void)
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();

    normal = gl_Normal.xyz;
    position = gl_Position.xyz;

    // Get a random number.
    vec2 randomPos = identifier * randomTextureSizeInv;
    float random = texture2D( randomTexture, randomPos ).x;

    float distance = gl_Position.z;
    if ( distance < 1.0 ) distance = 1.0; // to avoid front-clip
    float point_size = densityFactor / distance;
    float point_size_floor = floor( point_size );
    float point_size_ceil = ceil ( point_size );
    float point_size_fraction = fract( point_size );
    float probability_ceil = point_size_fraction * (2.0 * point_size_floor + point_size_fraction) / (2.0 * point_size_floor + 1.0);
    if ( circleThreshold <= 0 || point_size <= float( circleThreshold ) )
    {
        // Draw a particle as square.
        gl_PointSize = ((random < probability_ceil) ? point_size_ceil : point_size_floor) ;
        radius = 0.0;
    }
    else
    {
        // Draw a particle as circle.
        // Convert position to screen coordinates.
        centerCoord = screenScale + ( ( gl_Position.xy / gl_Position.w ) * screenScale );
        radius = ( ( random < probability_ceil ) ? point_size_ceil : point_size_floor ) * circleScale;
        gl_PointSize = ceil( point_size * circleScale * 2.0 ) + 1.0;
    }
}
