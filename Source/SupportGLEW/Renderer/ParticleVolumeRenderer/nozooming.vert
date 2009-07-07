/*****************************************************************************/
/**
 *  @file   nozooming.vert
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
varying vec3 position;
varying vec3 normal;

void main(void)
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();

    normal = gl_Normal.xyz;
    position = gl_Position.xyz;
}
