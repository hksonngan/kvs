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


namespace kvs
{

/*==========================================================================*/
/**
 *  Xform control class.
 */
/*==========================================================================*/
class XformControl
{
private:

    kvs::Xform m_current_xform;
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

protected:
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

#if KVS_ENABLE_DEPRECATED
    void applyXform( void ) const;
#endif

    const kvs::Xform xform( void ) const;

public:

    void rotate( const kvs::Matrix33f& rotation );

    void translate( const kvs::Vector3f& translation );

    void scale( const kvs::Vector3f& scaling );

#if KVS_ENABLE_DEPRECATED
public:

    void initialize( void )
    {
        this->setXform( kvs::Xform() );
    }

    void clear( void )
    {
        kvs::Xform xform( kvs::Vector3f( 0, 0, 0 ),
                          kvs::Vector3f( 0, 0, 0 ),
                          kvs::Matrix33f( 0, 0, 0,
                                          0, 0, 0,
                                          0, 0, 0 ) );
        this->setXform( xform );
    }

    void set(
        const kvs::Vector3f&  translation,
        const kvs::Vector3f&  scaling,
        const kvs::Matrix33f& rotation )
    {
        kvs::Xform xform( translation, scaling, rotation );
        this->setXform( xform );
    }

    void set( const Xform& xform )
    {
        this->setXform( xform );
    }

public:

    void updateRotation( const kvs::Matrix33f& rotation )
    {
        kvs::Xform xform = this->xform();
        xform.bind( kvs::Xform::Rotation( rotation ) );
        this->setXform( xform );
    }

    void updateTranslation( const kvs::Vector3f& translation )
    {
        kvs::Xform xform = this->xform();
        xform.bind( kvs::Xform::Translation( translation ) );
        this->setXform( xform );
    }

    void updateScaling( const kvs::Vector3f& scaling )
    {
        kvs::Xform xform = this->xform();
        xform.bind( kvs::Xform::Scaling( scaling ) );
        this->setXform( xform );
    }

    void updateScaling( float scaling )
    {
        kvs::Xform xform = this->xform();
        xform.bind( kvs::Xform::Scaling( scaling ) );
        this->setXform( xform );
    }

    const kvs::Vector3f translation( void ) const
    {
        return this->xform().translation();
    }

    const kvs::Matrix33f rotation( void ) const
    {
        return this->xform().rotation();
    }

    const kvs::Matrix33f scaledRotation( void ) const
    {
        return this->xform().scaledRotation();
    }

    const kvs::Vector3f scaling( void ) const
    {
        return this->xform().scaling();
    }

    Xform get( void ) const
    {
        return this->xform();
    }

    void get( float (*array)[16] ) const
    {
        this->xform().toArray( *array );
    }
#endif
};

} // end of namespace kvs

#endif // KVS__XFORM_CONTROL_H_INCLUDE
