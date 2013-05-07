/*****************************************************************************/
/**
 *  @file   tetrahedra.vert
 *  @author Jun Nishimura
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
// Output parameters to geometry shader.
varying vec4 position_in;
varying vec2 random_index_in;
varying float value_in;
varying vec3 normal_in;

// Input parameters.
attribute vec2 random_index;
attribute float value;


/*===========================================================================*/
/**
 *  @brief  Main function of vertex shader.
 */
/*===========================================================================*/
void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

    position_in = gl_ModelViewMatrix * gl_Vertex;
    random_index_in = random_index;
    value_in = value;
    normal_in = gl_NormalMatrix * gl_Normal;
}
