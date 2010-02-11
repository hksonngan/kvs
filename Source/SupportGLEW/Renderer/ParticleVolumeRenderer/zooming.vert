/*****************************************************************************/
/**
 *  @file   zooming.vert
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
uniform int circleThreshold;
uniform vec2 screenScale;
#if defined( ENABLE_RANDOM_TEXTURE )
uniform sampler2D randomTexture;
uniform float randomTextureSizeInv;
attribute vec2 identifier;
#endif

const float circleScale = 0.564189583547756; // 1.0 / sqrt(PI)

varying vec3 position;
varying vec3 normal;

varying vec2 centerCoord;
varying float radius;


#if defined( ENABLE_RANDOM_TEXTURE )
float zooming( in vec4 p )
{
    // Get a random number.
    vec2 randomPos = identifier * randomTextureSizeInv;
    float random = texture2D( randomTexture, randomPos ).x;

    float distance = p.z;
    if ( distance < 1.0 ) distance = 1.0; // to avoid front-clip

    float point_size = densityFactor / distance;
    float point_size_floor = floor( point_size );
    float point_size_ceil = ceil ( point_size );
    float point_size_fraction = fract( point_size );
    float probability_ceil = point_size_fraction * (2.0 * point_size_floor + point_size_fraction) / (2.0 * point_size_floor + 1.0);
    if ( circleThreshold <= 0 || point_size <= float( circleThreshold ) )
    {
        // Draw a particle as square.
        point_size = ((random < probability_ceil) ? point_size_ceil : point_size_floor) ;
        radius = 0.0;
    }
    else
    {
        // Draw a particle as circle.
        // Convert position to screen coordinates.
        centerCoord = screenScale + ( ( p.xy / p.w ) * screenScale );
        radius = ( ( random < probability_ceil ) ? point_size_ceil : point_size_floor ) * circleScale;
        point_size = ceil( point_size * circleScale * 2.0 ) + 1.0;
    }

    return( point_size );
}

#else
float zooming( in vec4 p )
{
    float distance = p.z;
    if ( distance < 1.0 ) distance = 1.0; // to avoid front-clip

    // Calculate particle size.
    float point_size = densityFactor / distance;
    float point_size_floor = floor( point_size );
    float point_size_ceil = ceil( point_size );

    // Generate a random floating point using the vertex position.
    float myF = p.x + p.z * p.y;
    int randi = int( myF * float( 0x0000ffff ) ); // pick 4 bits using mask
    randi = randi & 0x000000f0;
    randi >>= 4;
    float randf = float( randi ) / 16.0;
    float rand_size = randf + point_size_floor;

    // Select the floor value or the ceiling value randomly as the particle size.
    if ( circleThreshold <= 0 || point_size <= float( circleThreshold ) )
    {
        // Draw a particle as square.
        point_size = ( point_size < rand_size ) ? point_size_floor : point_size_ceil;
        radius = 0.0;
    }
    else
    {
        // Draw a particle as circle.
        // Convert position to screen coordinates.
        centerCoord = screenScale + ( ( p.xy / p.w ) * screenScale );
        radius = ( ( point_size < rand_size ) ? point_size_floor : point_size_ceil ) * circleScale;
        point_size = ceil( point_size * circleScale * 2.0 ) + 1.0;
    }

    return( point_size );
}
#endif

/*===========================================================================*/
/**
 *  @brief  Calculates a size of the particle in pixel.
 */
/*===========================================================================*/
void main( void )
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();

    normal = gl_Normal.xyz;
    position = vec3( gl_ModelViewMatrix * gl_Vertex );

    gl_PointSize = zooming( gl_Position );
}
