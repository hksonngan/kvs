/*****************************************************************************/
/**
 *  @file   volume.h
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
struct Volume
{
    vec3      ratio;     // ratio of the volume resolution (256x256x128 => 1:1:0.5)
    float     min_range; // min. range
    float     max_range; // max. range
    float     min_value; // min. scalar value
    float     max_value; // max. scalar value
    sampler3D data;      // volume data (scalar field)
};
