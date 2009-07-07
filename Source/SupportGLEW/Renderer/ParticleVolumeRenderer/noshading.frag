/*****************************************************************************/
/**
 *  @file   noshading.frag
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
varying vec2 centerCoord;
varying float radius;


/*===========================================================================*/
/**
 *  @brief  Calculates a color of the particle.
 */
/*===========================================================================*/
void main(void)
{
    // Discard a pixel outside circle.
    if ( radius > 0.0 )
    {
        if( distance( gl_FragCoord.xy, centerCoord ) > radius ) discard;
    }

    gl_FragColor = gl_Color;
}
