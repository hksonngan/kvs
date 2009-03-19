/****************************************************************************/
/**
 *  @file Shader.cpp
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
#include "Shader.h"
#include <kvs/Math>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Shader::Base::Base( void )
{
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
Shader::Base::~Base( void )
{
}

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Shader::Lambert::Lambert( void ):
    Ka( 0.5f ),
    Kd( 0.5f )
{
}

/*==========================================================================*/
/**
 *  Copy constructor.
 *  @param shader [in] shader
 */
/*==========================================================================*/
Shader::Lambert::Lambert( const Shader::Lambert& shader )
{
    C  = shader.C;
    L  = shader.L;
    Ka = shader.Ka;
    Kd = shader.Kd;
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param ka [in] ambient
 *  @param kd [in] diffuse
 */
/*==========================================================================*/
Shader::Lambert::Lambert( const float ka, const float kd )
{
    Ka = ka;
    Kd = kd;
}

/*==========================================================================*/
/**
 *  Set the camera and light.
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void Shader::Lambert::set( const Camera* camera, const Light* light )
{
    kvs::IgnoreUnusedVariable( camera );

    L = -light->position().normalize();
}

/*==========================================================================*/
/**
 *  Get the attenuation value.
 *  @return attenuation value
 */
/*==========================================================================*/
inline const float Shader::Lambert::attenuation( const float gradient[3] ) const
{
    // Normal vector.
    const kvs::Vector3f N( kvs::Vector3f( gradient ).normalize() );

    //const float dd = kvs::Math::Max( N.dot( L ), 0.0 );
    const float dd = kvs::Math::Abs( N.dot( L ) );

    /* I = Ia + Id
     *
     * Ia = Ka (constant term)
     * Id = Ip *  Kd * cos(A) = Ip * Kd * ( L dot N )
     *
     * Ip : the intensity emitted from the light source.
     */
    const float Ia = Ka;
    const float Id = Kd * dd;

    return( kvs::Math::Min( Ia + Id, 1.0f ) );
}

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Shader::Phong::Phong( void ):
    Ka( 0.2f ),
    Kd( 0.5f ),
    Ks( 0.3f ),
    S( 20.0f )
{
}

/*==========================================================================*/
/**
 *  Copy constructor.
 *  @param shader [in] shader
 */
/*==========================================================================*/
Shader::Phong::Phong( const Shader::Phong& shader )
{
    C  = shader.C;
    L  = shader.L;
    Ka = shader.Ka;
    Kd = shader.Kd;
    Ks = shader.Ks;
    S  = shader.S;
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param ka [in] ambient
 *  @param kd [in] diffuse
 *  @param ks [in] specular
 *  @param s [in] shininess
 */
/*==========================================================================*/
Shader::Phong::Phong( const float ka, const float kd, const float ks, const float s )
{
    Ka = ka;
    Kd = kd;
    Ks = ks;
    S  = s;
}

/*==========================================================================*/
/**
 *  Set the camera and light.
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void Shader::Phong::set( const kvs::Camera* camera, const kvs::Light* light )
{
    kvs::IgnoreUnusedVariable( camera );

    L = -light->position().normalize();
}

/*==========================================================================*/
/**
 *  Get the attenuation value.
 *  @return attenuation value
 */
/*==========================================================================*/
inline const float Shader::Phong::attenuation( const float gradient[3] ) const
{
    // Normal vector N and reflection vector R.
    const kvs::Vector3f N( kvs::Vector3f( gradient ).normalize() );
    const kvs::Vector3f R( 2.0f * N.dot( L ) * N - L );

    //const float dd = Math::Max( N.dot( L ), 0.0f );
    //const float ds = Math::Max( N.dot( R ), 0.0f );
    const float dd = kvs::Math::Abs( N.dot( L ) );
    const float ds = kvs::Math::Abs( N.dot( R ) );

    /* I = Ia + Id + Is
     *
     * Is = Ip * Ks * cos^s(B) = Ip * Ks * ( R dot N )^s
     */
    const float Ia = Ka;
    const float Id = Kd * dd;
    const float Is = Ks * std::pow( ds, S );

    return( kvs::Math::Min( Ia + Id + Is, 1.0f ) );
}

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
Shader::BlinnPhong::BlinnPhong( void ):
    Ka( 0.2f ),
    Kd( 0.5f ),
    Ks( 0.3f ),
    S( 20.0f )
{
}

/*==========================================================================*/
/**
 *  Copy constructor.
 *  @param shader [in] shader
 */
/*==========================================================================*/
Shader::BlinnPhong::BlinnPhong( const Shader::BlinnPhong& shader )
{
    C  = shader.C;
    L  = shader.L;
    H  = shader.H;
    Ka = shader.Ka;
    Kd = shader.Kd;
    Ks = shader.Ks;
    S  = shader.S;
}

/*==========================================================================*/
/**
 *  Consturctor.
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
Shader::BlinnPhong::BlinnPhong( const kvs::Camera* camera, const kvs::Light* light )
{
    this->set( camera, light );
}

/*==========================================================================*/
/**
 *  Set the camera and light
 *  @param camera [in] pointer to the camera
 *  @param light [in] pointer to the light
 */
/*==========================================================================*/
void Shader::BlinnPhong::set( const kvs::Camera* camera, const kvs::Light* light )
{
    C = -camera->position().normalize();
    L = -light->position().normalize();
    H = ( C + L ).normalize();
}

/*==========================================================================*/
/**
 *  Get the attenuation value.
 *  @return attenuation value
 */
/*==========================================================================*/
inline const float Shader::BlinnPhong::attenuation( const float gradient[3] ) const
{
    // Normal vector.
    const kvs::Vector3f N( kvs::Vector3f( gradient ).normalize() );

    //const float dd = kvs::Math::Max( N.dot( L ), 0.0 );
    //const float ds = kvs::Math::Max( N.dot( H ), 0.0 );
    const float dd = kvs::Math::Abs( N.dot( L ) );
    const float ds = kvs::Math::Abs( N.dot( H ) );

    /* I = Ia + Id + Is
     *
     * Is = Ip * Ks * cos^s(B) = Ip * Ks * ( H dot N )^s
     */
    const float Ia = Ka;
    const float Id = Kd * dd;
    const float Is = Ks * ::pow( ds, S );

    return( kvs::Math::Min( Ia + Id + Is, 1.0f ) );
}

} // end of namespace kvs
