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

#if defined( ENABLE_EXACT_DEPTH_TESTING )
varying float depth;
#endif

void main( void )
{
    gl_Position = ftransform();
    position = ( gl_ModelViewMatrix * gl_Vertex ).xyz;
    gl_TexCoord[0] = gl_MultiTexCoord0;

#if defined( ENABLE_EXACT_DEPTH_TESTING )
    depth = gl_Position.z / gl_Position.w;
#endif
}
