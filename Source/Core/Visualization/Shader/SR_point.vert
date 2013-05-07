/*****************************************************************************/
/**
 *  @file   SR_point.vert
 *  @author Naohisa Sakamoto
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
// Input
attribute vec2 random_index;

// Output
varying vec3 position;
varying vec3 normal;
varying vec2 index;
varying float depth;

void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;

    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
    normal = ( gl_NormalMatrix * gl_Normal ).xyz;
    index = random_index;
    depth = gl_Position.z / gl_Position.w;
}
