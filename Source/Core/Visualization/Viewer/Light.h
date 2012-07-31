/****************************************************************************/
/**
 *  @file Light.h
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
#ifndef KVS__LIGHT_H_INCLUDE
#define KVS__LIGHT_H_INCLUDE

#include <kvs/XformControl>
#include <kvs/ClassName>
#include <kvs/Vector3>
#include <kvs/Camera>


namespace kvs
{

class RGBAColor;

/*==========================================================================*/
/**
 *  Light class
 */
/*==========================================================================*/
class Light
{
    kvsClassName( kvs::Light );

private:
#if KVS_ENABLE_DEPRECATED
protected:
#endif
    kvs::XformControl m_xform_control;
    unsigned int  m_id;            ///< light ID
    kvs::Vector3f m_init_position; ///< initial light position
    kvs::Vector3f m_position;      ///< light position
    kvs::Vector3f m_diffuse;       ///< diffuse color
    kvs::Vector3f m_ambient;       ///< ambient color
    kvs::Vector3f m_specular;      ///< specular color

public:

    Light();

    virtual ~Light( void );

public:

    void initialize( void );

public:

    void setID( const unsigned int id );

    void setPosition( const float x, const float y, const float z );

    void setPosition( const kvs::Vector3f& position );

    void setColor( const float r, const float g, const float b );

    void setColor( const kvs::RGBAColor& color );

    void setDiffuse( const float r, const float g, const float b );

    void setDiffuse( const kvs::RGBAColor& color );

    void setAmbient( const float r, const float g, const float b );

    void setAmbient( const kvs::RGBAColor& color );

    void setSpecular( const float r, const float g, const float b );

    void setSpecular( const kvs::RGBAColor& color );

public:

    const kvs::Vector3f& position( void ) const;

    const kvs::Vector3f& diffuse( void ) const;

    const kvs::Vector3f& ambient( void ) const;

    const kvs::Vector3f& specular( void ) const;

public:

    virtual void update( const kvs::Camera* camera );

    void on( void ) const;

    void off( void ) const;

    const bool isEnabled( void ) const;

public:

    void resetXform( void );

    void rotate( const kvs::Matrix33f& rotation );

    void translate( const kvs::Vector3f& translation );

    void scale( const kvs::Vector3f& scaling );

public:

    static void setModelLocalViewer( bool flag );

    static void setModelTwoSide( bool flag );

    static void setModelAmbient( float ambient[4] );

#if KVS_ENABLE_DEPRECATED
public:

    operator kvs::XformControl() const
    {
        return m_xform_control;
    }

public:

    void clear()
    {
        m_xform_control.clear();
    }

    void set(
        const kvs::Vector3f&  translation,
        const kvs::Vector3f&  scaling,
        const kvs::Matrix33f& rotation )
    {
        m_xform_control.set( translation, scaling, rotation );
    }

    void set( const Xform& xform )
    {
        m_xform_control.set( xform );
    }

    void updateRotation( const kvs::Matrix33f& rotation )
    {
        m_xform_control.updateRotation( rotation );
    }

    void updateTranslation( const kvs::Vector3f& translation )
    {
        m_xform_control.updateTranslation( translation );
    }

    void updateScaling( const kvs::Vector3f& scaling )
    {
        m_xform_control.updateScaling( scaling );
    }

    void updateScaling( float scaling )
    {
        m_xform_control.updateScaling( scaling );
    }

    const kvs::Vector3f translation() const
    {
        return m_xform_control.translation();
    }

    const kvs::Matrix33f& rotation() const
    {
        return m_xform_control.rotation();
    }

    const kvs::Matrix33f scaledRotation() const
    {
        return m_xform_control.scaledRotation();
    }

    const kvs::Vector3f& scaling() const
    {
        return m_xform_control.scaling();
    }

    Xform get() const
    {
        return m_xform_control.get();
    }

    void get( float (*array)[16] ) const
    {
        m_xform_control.get( array );
    }

public:

    void setInitialXform(
        const kvs::Vector3f&  translation = kvs::Vector3f(0,0,0),
        const kvs::Vector3f&  scaling     = kvs::Vector3f(1,1,1),
        const kvs::Matrix33f& rotation    = kvs::Matrix33f(1,0,0,0,1,0,0,0,1) )
    {
        m_xform_control.setInitialXform( translation, scaling, rotation );
    }

    void saveXform()
    {
        m_xform_control.saveXform();
    }

    void setXform( const kvs::Xform& xform )
    {
        m_xform_control.setXform( xform );
    }

    void applyXform() const
    {
        m_xform_control.applyXform();
    }

    const kvs::Xform xform() const
    {
        return m_xform_control.xform();
    }
#endif
};

} // end of namespace kvs

#endif // KVS__LIGHT_H_INCLUDE
