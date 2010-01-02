/*****************************************************************************/
/**
 *  @file   CheckBoxGroup.h
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
#ifndef KVS__GLUT__CHECK_BOX_GROUP_H_INCLUDE
#define KVS__GLUT__CHECK_BOX_GROUP_H_INCLUDE

#include <list>
#include <kvs/ClassName>
#include <kvs/glut/WidgetBase>
#include <kvs/glut/Screen>
#include "CheckBox.h"


namespace kvs
{

namespace glut
{

class CheckBox;

/*===========================================================================*/
/**
 *  @brief  Check box group class.
 */
/*===========================================================================*/
class CheckBoxGroup : public kvs::glut::WidgetBase
{
    // Class name.
    kvsClassName( CheckBoxGroup );

public:

    typedef kvs::glut::WidgetBase BaseClass;

protected:

    std::list<kvs::glut::CheckBox*> m_boxes; ///< check box list

public:

    CheckBoxGroup( kvs::ScreenBase* screen, kvs::WindowBase* window );

    CheckBoxGroup( kvs::glut::Screen* screen = 0 );

public:

    virtual void pressed( kvs::glut::CheckBox* box ) {};

    virtual void pressed( int id ) {};

    virtual void released( kvs::glut::CheckBox* box ) {};

    virtual void released( int id ) {};

    virtual void screenUpdated( void ) {};

    virtual void screenResized( void ) {};

public:

    const std::list<kvs::glut::CheckBox*>& checkBoxes( void ) const;

    void add( kvs::glut::CheckBox* box );

    void remove( kvs::glut::CheckBox* box );

    void show( void );

    void hide( void );

private:

    void paintEvent( void );

    void resizeEvent( int width, int height );

    void mousePressEvent( kvs::MouseEvent* event );

    void mouseReleaseEvent( kvs::MouseEvent* event );
};

} // end of namespace glut

} // end of namespace kvs

#endif // KVS__GLUT__CHECK_BOX_GROUP_H_INCLUDE
