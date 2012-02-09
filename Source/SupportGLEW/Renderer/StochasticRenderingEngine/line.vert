/*****************************************************************************/
/**
 *  @file   line.vert
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
varying vec3 position;
varying vec2 id;

attribute vec2 identifier;

void main( void )
{
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;

    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
    id = identifier;
}
