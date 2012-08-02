/****************************************************************************/
/**
 *  @file XformControl.h
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
#ifndef KVS__XFORM_CONTROL_H_INCLUDE
#define KVS__XFORM_CONTROL_H_INCLUDE

#include <kvs/Xform>
#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Xform control class.
 */
/*==========================================================================*/
class XformControl : public kvs::Xform
{
    kvsClassName( kvs::XformControl );

protected:

    kvs::Xform m_initial_xform; ///< initial transform vector

public:

    XformControl();

#if KVS_ENABLE_DEPRECATED
    XformControl(
        const kvs::Vector3f&  translation,
        const kvs::Vector3f&  scaling,
        const kvs::Matrix33f& rotation )
    {
        this->setXform( kvs::Xform( translation, scaling, rotation ) );
        this->saveXform();
    }
#endif

    virtual ~XformControl( void );

public:
#if KVS_ENABLE_DEPRECATED
    void setInitialXform(
        const kvs::Vector3f&  translation = kvs::Vector3f(0,0,0),
        const kvs::Vector3f&  scaling     = kvs::Vector3f(1,1,1),
        const kvs::Matrix33f& rotation    = kvs::Matrix33f(1,0,0,0,1,0,0,0,1) )
    {
        this->setXform( kvs::Xform( translation, scaling, rotation ) );
        this->saveXform();
    }
#endif

    void saveXform( void );

    void resetXform( void );

    void setXform( const kvs::Xform& xform );

    void applyXform( void ) const;

    const kvs::Xform xform( void ) const;

public:

    void rotate( const kvs::Matrix33f& rotation );

    void translate( const kvs::Vector3f& translation );

    void scale( const kvs::Vector3f& scaling );
};

} // end of namespace kvs

#endif // KVS__XFORM_CONTROL_H_INCLUDE
