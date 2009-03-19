/****************************************************************************/
/**
 *  @file ClassName.h
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007-2008 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/****************************************************************************/
#ifndef KVS_CORE_CLASS_NAME_H_INCLUDE
#define KVS_CORE_CLASS_NAME_H_INCLUDE

#define kvsClassName( this_class )                \
    public:                                       \
    virtual const char* className( void ) const { \
        return ( # this_class );                  \
    }

#define kvsClassName_without_virtual( this_class ) \
    public:                                        \
    const char* className( void ) const {          \
        return ( # this_class );                   \
    }

#endif // KVS_CORE_CLASS_NAME_H_INCLUDE
