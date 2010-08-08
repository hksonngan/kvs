/*****************************************************************************/
/**
 *  @file   transfer_function.h
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
struct TransferFunction
{
    sampler1D data; // transfer function data
    float min_value; // min. scalar value
    float max_value; // max. scalar value
};
