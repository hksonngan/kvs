/*****************************************************************************/
/**
 *  @file   polygon.vert
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
// Input parameters.
attribute vec2 random_index; // index for accessing to the random texture
uniform float polygon_offset; // polygon offset in clip coordinate

// Output parameters to fragment shader.
varying vec3 position; // vertex position in camera coordinate
varying vec3 normal; // normal vector in camera coodinate
varying vec2 index; // index for accessing to the random texture
varying float depth; // depth value of the vertex in normalized device coordinate


/*===========================================================================*/
/**
 *  @brief  Main function of vertex shader.
 */
/*===========================================================================*/
void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    gl_Position.z -= polygon_offset;
    gl_FrontColor = gl_Color;

    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
    normal = gl_NormalMatrix * gl_Normal;
    index = random_index;
    depth = gl_Position.z / gl_Position.w;
}
