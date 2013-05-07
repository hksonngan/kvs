/*****************************************************************************/
/**
 *  @file   uniform_grid.vert
 *  @author Naoya Maeda
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
varying vec3 position;
varying float depth;


void main()
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;

    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
    depth = gl_Position.z / gl_Position.w;
}
