/****************************************************************************/
/**
 *  @file Light.cpp
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
#include "Light.h"
#include <kvs/OpenGL>
#include <kvs/RGBAColor>
#include <kvs/Vector3>
#include <kvs/Matrix33>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 *  @param collision [in] collision dectection flag
 */
/*==========================================================================*/
Light::Light()
{
    this->initialize();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Light::~Light( void )
{
}

/*==========================================================================*/
/**
 *  Initialize the member parameters.
 */
/*==========================================================================*/
void Light::initialize( void )
{
    m_id = GL_LIGHT0;
    this->setPosition( 0.0, 0.0, 12.0 );
    m_diffuse.set( 1.0, 1.0, 1.0 );
    m_ambient.set( 0.0, 0.0, 0.0 );
    m_specular.set( 1.0, 1.0, 1.0 );
}

/*==========================================================================*/
/**
 *  Set the light ID.
 *  @param id [in] light ID
 */
/*==========================================================================*/
void Light::setID( const unsigned int id )
{
    m_id = id;
}

/*==========================================================================*/
/**
 *  Set the light position.
 *  @param x [in] x coordinate value
 *  @param y [in] y coordinate value
 *  @param z [in] z coordinate value
 */
/*==========================================================================*/
void Light::setPosition( const float x, const float y, const float z )
{
    this->setPosition( kvs::Vector3f( x, y, z ) );
}

/*==========================================================================*/
/**
 *  Set the light position.
 *  @param position [in] light position
 */
/*==========================================================================*/
void Light::setPosition( const kvs::Vector3f& position )
{
    m_init_position.set( position.x(), position.y(), position.z() );
    m_position.set( position.x(), position.y(), position.z() );
}

/*==========================================================================*/
/**
 *  Set the diffuse color of the light.
 *  @param r [in] red component (0.0-1.0)
 *  @param g [in] green component (0.0-1.0)
 *  @param b [in] blue component (0.0-1.0)
 */
/*==========================================================================*/
void Light::setColor( const float r, const float g, const float b )
{
    m_diffuse.set( r, g, b );
}

/*==========================================================================*/
/**
 *  Set the diffuse color of the light.
 *  @param color [in] diffuse color
 */
/*==========================================================================*/
void Light::setColor( const kvs::RGBAColor& color )
{
    m_diffuse.set( static_cast<float>(color.r()) / 255.0f,
                   static_cast<float>(color.g()) / 255.0f,
                   static_cast<float>(color.b()) / 255.0f );
}

/*==========================================================================*/
/**
 *  Set the diffuse color of the light.
 *  @param r [in] red component (0.0-1.0)
 *  @param g [in] green component (0.0-1.0)
 *  @param b [in] blue component (0.0-1.0)
 */
/*==========================================================================*/
void Light::setDiffuse( const float r, const float g, const float b )
{
    m_diffuse.set( r, g, b );
}

/*==========================================================================*/
/**
 *  Set the diffuse color of the light.
 *  @param color [in] diffuse color
 */
/*==========================================================================*/
void Light::setDiffuse( const kvs::RGBAColor& color )
{
    m_diffuse.set( static_cast<float>(color.r()) / 255.0f,
                   static_cast<float>(color.g()) / 255.0f,
                   static_cast<float>(color.b()) / 255.0f );
}

/*==========================================================================*/
/**
 *  Set the ambient color of the light.
 *  @param r [in] red component (0.0-1.0)
 *  @param g [in] green component (0.0-1.0)
 *  @param b [in] blue component (0.0-1.0)
 */
/*==========================================================================*/
void Light::setAmbient( const float r, const float g, const float b )
{
    m_ambient.set( r, g, b );
}

/*==========================================================================*/
/**
 *  Set the ambient color of the light.
 *  @param color [in] ambient color
 */
/*==========================================================================*/
void Light::setAmbient( const kvs::RGBAColor& color )
{
    m_ambient.set( static_cast<float>(color.r()) / 255.0f,
                   static_cast<float>(color.g()) / 255.0f,
                   static_cast<float>(color.b()) / 255.0f );
}

/*==========================================================================*/
/**
 *  Set the specular color of the light.
 *  @param r [in] red component (0.0-1.0)
 *  @param g [in] green component (0.0-1.0)
 *  @param b [in] blue component (0.0-1.0)
 */
/*==========================================================================*/
void Light::setSpecular( const float r, const float g, const float b )
{
    m_specular.set( r, g, b );
}

/*==========================================================================*/
/**
 *  Set the specular color of the light.
 *  @param color [in] specular color
 */
/*==========================================================================*/
void Light::setSpecular( const kvs::RGBAColor& color )
{
    m_specular.set( static_cast<float>(color.r()) / 255.0f,
                    static_cast<float>(color.g()) / 255.0f,
                    static_cast<float>(color.b()) / 255.0f );
}

/*==========================================================================*/
/**
 *  Get the light position.
 */
/*==========================================================================*/
const kvs::Vector3f& Light::position( void ) const
{
    return( m_position );
}

/*==========================================================================*/
/**
 *  Get the diffuse color of the light.
 */
/*==========================================================================*/
const kvs::Vector3f& Light::diffuse( void ) const
{
    return( m_diffuse );
}

/*==========================================================================*/
/**
 *  Get the ambient color of the light.
 */
/*==========================================================================*/
const kvs::Vector3f& Light::ambient( void ) const
{
    return( m_ambient );
}

/*==========================================================================*/
/**
 *  Get the specular color of the light.
 */
/*==========================================================================*/
const kvs::Vector3f& Light::specular( void ) const
{
    return( m_specular );
}

/*==========================================================================*/
/**
 *  Update the light.
 */
/*==========================================================================*/
void Light::update( const kvs::Camera* camera )
{
    const kvs::Vector3f p = camera->projectWorldToCamera( this->position() );

    const kvs::Vector4f position( p, 1.0f );
    const kvs::Vector4f diffuse( this->diffuse(), 1.0f );
    const kvs::Vector4f ambient( this->ambient(), 1.0f );
    const kvs::Vector4f specular( this->specular(), 1.0f );

    glPushMatrix();
    glLoadIdentity();
    {
        glLightfv( m_id, GL_POSITION, &(position[0]) );
        glLightfv( m_id, GL_DIFFUSE,  &(diffuse[0]) );
        glLightfv( m_id, GL_AMBIENT,  &(ambient[0]) );
        glLightfv( m_id, GL_SPECULAR, &(specular[0]) );
    }
    glPopMatrix();
}

/*==========================================================================*/
/**
 *  Turn on the light.
 */
/*==========================================================================*/
void Light::on( void ) const
{
    glEnable( m_id );
}

/*==========================================================================*/
/**
 *  Turn off the light.
 */
/*==========================================================================*/
void Light::off( void ) const
{
    glDisable( m_id );
}

/*==========================================================================*/
/**
 *  Test whether the light is enable or not.
 *  @return true, if the light is enable.
 */
/*==========================================================================*/
const bool Light::isEnabled( void ) const
{
    return( glIsEnabled( m_id ) == GL_TRUE );
}

/*===========================================================================*/
/**
 *  @brief  Resets the xform of the light.
 */
/*===========================================================================*/
void Light::resetXform( void )
{
    kvs::XformControl::resetXform();
    m_position = m_init_position;
}

/*==========================================================================*/
/**
 *  Rotate the light.
 *  @param rotation [in] rotation matrix
 */
/*==========================================================================*/
void Light::rotate( const kvs::Matrix33f& rotation )
{
    kvs::XformControl::rotate( rotation );
     m_position = this->xform().transform( m_init_position );
}

/*==========================================================================*/
/**
 *  Translate the light.
 *  @param translation [in] translation vector
 */
/*==========================================================================*/
void Light::translate( const kvs::Vector3f& translation )
{
    kvs::XformControl::translate( translation );
    m_position = this->xform().transform( m_init_position );
}

/*==========================================================================*/
/**
 *  Scale the light.
 *  @param scaling [in] scaling vector.
 */
/*==========================================================================*/
void Light::scale( const kvs::Vector3f& scaling )
{
    kvs::XformControl::scale( scaling );
    m_position = this->xform().transform( m_init_position );
}

/*==========================================================================*/
/**
 *  Set the lighting model as a local-viewer.
 *  @param flag [in] set flag
 */
/*==========================================================================*/
void Light::setModelLocalViewer( bool flag )
{
    glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, flag );
}

/*==========================================================================*/
/**
 *  Set the lighting model as a two-side.
 *  @param flag [in] set flag
 */
/*==========================================================================*/
void Light::setModelTwoSide( bool flag )
{
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, flag );
}

/*==========================================================================*/
/**
 *  Set the lighting model as a ambient light.
 *  @param ambient [in] ambient color
 */
/*==========================================================================*/
void Light::setModelAmbient( float ambient[4] )
{
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient );
}

} // end of namespace kvs

