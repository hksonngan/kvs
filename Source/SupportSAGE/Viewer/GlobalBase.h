/****************************************************************************/
/**
 *  @file GlobalBase.h
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
#ifndef KVS_SUPPORT_SAGE_GLOBAL_BASE_H_INCLUDE
#define KVS_SUPPORT_SAGE_GLOBAL_BASE_H_INCLUDE

#include <kvs/GlobalCore>
#include "ApplicationInterface.h"


namespace kvs
{

namespace sage
{

/*==========================================================================*/
/**
*  Global base class for SAGE.
*/
/*==========================================================================*/
class GlobalBase : public kvs::GlobalCore
{
    friend class ScreenBase;

public:

    static kvs::sage::ApplicationInterface* sail; ///< SAGE application interface

public:

    GlobalBase( int count, char** values );

    virtual ~GlobalBase( void );
};

} // end of namespace sage

} // end of namespace kvs

#endif // KVS_SUPPORT_SAGE_GLOBAL_BASE_H_INCLUDE
