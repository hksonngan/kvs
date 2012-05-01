/****************************************************************************/
/**
 *  @file ClassName.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS__CLASS_NAME_H_INCLUDE
#define KVS__CLASS_NAME_H_INCLUDE

#define kvsClassName( this_class )          \
    public:                                 \
    virtual const char* className() const { \
        return #this_class;                 \
    }

#define kvsClassName_without_virtual( this_class ) \
    public:                                        \
    const char* className() const {                \
        return #this_class;                        \
    }

#endif // KVS__CLASS_NAME_H_INCLUDE
