/*****************************************************************************/
/**
 *  @file   qualifire.h
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

// Type qualifiers.
#if __VERSION__ >= 130
#define VertIn in
#define VertOut out
#define GeomIn in
#define GeomOut out
#define FragIn in
#else
#define VertIn attribute
#define VertOut varying
#define GeomIn varying in
#define GeomOut varying out
#define FragIn varying
#endif
