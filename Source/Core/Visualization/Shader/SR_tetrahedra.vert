/*****************************************************************************/
/**
 *  @file   tetrahedra.vert
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
attribute float value; // normalized scalar value for the vertex
attribute vec2 random_index; // index for accessing to the random texture

// Output parameters to geometry shader.
varying vec4 position_in; // vertex position in camera coordinate
varying vec4 position_ndc_in; // vertex position in normalized device coordinate
varying vec3 normal_in; // normal vector in camera coordinate
varying float value_in; // scalar value for the vertex
varying vec2 random_index_in; // index for accessing to the random texture


/*===========================================================================*/
/**
 *  @brief  Main function of vertex shader.
 */
/*===========================================================================*/
void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

    position_in = gl_ModelViewMatrix * gl_Vertex;
    position_ndc_in = vec4( gl_Position.xyz, 1.0 ) / gl_Position.w;
    normal_in = gl_NormalMatrix * gl_Normal;

    value_in = value / gl_Position.w;
    random_index_in = random_index;
}
