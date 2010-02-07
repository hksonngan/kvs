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

const float circleScale = 0.564189583547756; // 1.0 / sqrt(PI)

varying vec3 position;
varying vec3 normal;

varying vec2 centerCoord;
varying float radius;


/*===========================================================================*/
/**
 *  @brief  Calculates a size of the particle.
 */
/*===========================================================================*/
void main( void )
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();

    normal = gl_Normal.xyz;
    position = vec3( gl_ModelViewMatrix * gl_Vertex );

    float distance = gl_Position.z;
    if ( distance < 1.0 ) distance = 1.0; // to avoid front-clip

    // Calculate particle size.
    float point_size = densityFactor / distance;
    float point_size_floor = floor( point_size );
    float point_size_ceil = ceil( point_size );

    // Generate a random floating point using the vertex position.
    float myF = gl_Position.x + gl_Position.z * gl_Position.y;
    int randi = int( myF * float( 0x0000ffff ) ); // pick 4 bits using mask
    randi = randi & 0x000000f0;
    randi >>= 4;
    float randf = float( randi ) / 16.0;
    float rand_size = randf + point_size_floor;

    // Select the floor value or the ceiling value randomly as the particle size.
    if ( circleThreshold <= 0 || point_size <= float( circleThreshold ) )
    {
        // Draw a particle as square.
        gl_PointSize = ( point_size < rand_size ) ? point_size_floor : point_size_ceil;
        radius = 0.0;
    }
    else
    {
        // Draw a particle as circle.
        // Convert position to screen coordinates.
        centerCoord = screenScale + ( ( gl_Position.xy / gl_Position.w ) * screenScale );
        radius = ( ( point_size < rand_size ) ? point_size_floor : point_size_ceil ) * circleScale;
        gl_PointSize = ceil( point_size * circleScale * 2.0 ) + 1.0;
    }
}
