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
#ifndef KVS_SUPPORT_QT_GLOBAL_BASE_H_INCLUDE
#define KVS_SUPPORT_QT_GLOBAL_BASE_H_INCLUDE

#include "../Qt.h"
#include <kvs/GlobalCore>


namespace kvs
{

namespace qt
{

/*==========================================================================*/
/**
 *  Global base class for Qt.
 */
/*==========================================================================*/
class GlobalBase : public kvs::GlobalCore
{
    friend class ScreenBase;

public:

    static QApplication* application; ///< Qt application

public:

    GlobalBase( int count, char** values );

    virtual ~GlobalBase( void );
};

} // end of namespace qt

} // end of namespace kvs

#endif // KVS_SUPPORT_QT_GLOBAL_BASE_H_INCLUDE
