/*****************************************************************************/
/**
 *  @file   Application.h
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
#ifndef KVS__QT__APPLICATION_H_INCLUDE
#define KVS__QT__APPLICATION_H_INCLUDE

#include <kvs/ApplicationBase>
#include <kvs/qt/Qt>


namespace kvs
{

namespace qt
{

/*===========================================================================*/
/**
 *  @brief  Qt viewer application class.
 */
/*===========================================================================*/
class Application : public kvs::ApplicationBase
{
private:

    QApplication* m_app; ///< Qt application

public:

    Application( int argc, char** argv );

    virtual ~Application( void );

public:

    virtual int run( void );

    virtual void quit( void );
};

} // end of namespace qt

} // end of namespace kvs

#endif // KVS__QT__APPLICATION_H_INCLUDE
