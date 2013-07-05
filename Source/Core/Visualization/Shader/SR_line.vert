/*****************************************************************************/
/**
 *  @file   SR_line.vert
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

// Output parameters to fragment shader.
varying vec3 position; // vertex position in camera coordinate
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
    gl_FrontColor = gl_Color;

    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
    index = random_index;
    depth = gl_Position.z / gl_Position.w;
}
