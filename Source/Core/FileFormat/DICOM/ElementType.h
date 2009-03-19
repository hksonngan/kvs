/****************************************************************************/
/**
 *  @file ElementType.h
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
#ifndef KVS__DCM_ELEMENT_TYPE_H_INCLUDE
#define KVS__DCM_ELEMENT_TYPE_H_INCLUDE

#include <string>

namespace kvs
{

namespace dcm
{

enum ElementType
{
    ELEM_UNKNOWN         = 0, ///< unknown type element
    ELEM_IMPLICIT        = 1, ///< implicit type element
    ELEM_EXPLICIT        = 2, ///< explicit type element
    ELEM_EXPLICIT_CUSTOM = 3, ///< explicit (custom) type element
    NUMBER_OF_ELEMENT_TYPES = 4
};

const std::string ELEMENT_TYPE_TO_STRING[NUMBER_OF_ELEMENT_TYPES] =
{
    "Unknown",
    "Implicit",
    "Explicit",
    "Explicit (custum)"
};

} // end of namespace dcm

} // end of namespace kvs

#endif // KVS__DCM_ELEMENT_TYPE_H_INCLUDE
