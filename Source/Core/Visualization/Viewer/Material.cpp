/****************************************************************************/
/**
 *  @file Material.cpp
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
#include "Material.h"
#include <cstring>
#include <kvs/Vector4>
#include <kvs/RGBAColor>


namespace kvs
{

Material::Material( void )
{
    initialize();
}

Material::Material(
    const kvs::RGBAColor& ambient,
    const kvs::RGBAColor& diffuse,
    const kvs::RGBAColor& specular,
    float                 shininess,
    MaterialFace          face )
{
    setAmbient( ambient );
    setDiffuse( diffuse );
    setSpecular( specular );
    setShininess( shininess );
    m_face = face;
}

Material::Material(
    const float  ambient[4],
    const float  diffuse[4],
    const float  specular[4],
    float        shininess,
    MaterialFace face )
{
    setAmbient( ambient );
    setDiffuse( diffuse );
    setSpecular( specular );
    setShininess( shininess );
    m_face = face;
}

Material::Material(
    float ambi_r, float ambi_g, float ambi_b, float ambi_a,
    float diff_r, float diff_g, float diff_b, float diff_a,
    float spec_r, float spec_g, float spec_b, float spec_a,
    float shininess,
    MaterialFace face )
{
    setAmbient(   ambi_r, ambi_g, ambi_b, ambi_a );
    setDiffuse(   diff_r, diff_g, diff_b, diff_a );
    setSpecular(  spec_r, spec_g, spec_b, spec_a );
    setShininess( shininess );
    m_face = face;
}

Material::Material( const Material& material )
{
    *this = material;
}

Material::~Material( void )
{
}

void Material::initialize( void )
{
    m_ambient[0]  = m_ambient[1]  = m_ambient[2]  = m_ambient[3]  = 1.0f;
    m_diffuse[0]  = m_diffuse[1]  = m_diffuse[2]  = m_diffuse[3]  = 1.0f;
    m_specular[0] = m_specular[1] = m_specular[2] = m_specular[3] = 1.0f;
    m_shininess   = 100.0f;
    m_face = Front;
}

void Material::clear( void )
{
    m_ambient[0]  = m_ambient[1]  = m_ambient[2]  = m_ambient[3]  = 0.0f;
    m_diffuse[0]  = m_diffuse[1]  = m_diffuse[2]  = m_diffuse[3]  = 0.0f;
    m_specular[0] = m_specular[1] = m_specular[2] = m_specular[3] = 0.0f;
    m_shininess   = 0.0f;
    m_face = Front;
}

Material& Material::operator = ( const Material& material )
{
    size_t byte_size = sizeof(float) * 4;

    memcpy( m_ambient,  material.m_ambient,  byte_size );
    memcpy( m_diffuse,  material.m_diffuse,  byte_size );
    memcpy( m_specular, material.m_specular, byte_size );
    m_shininess = material.m_shininess;
    m_face      = material.m_face;

    return( *this );
}

const kvs::Vector4f Material::ambient( void ) const
{
    return( kvs::Vector4f( m_ambient ) );
}

const kvs::Vector4f Material::diffuse( void ) const
{
    return( kvs::Vector4f( m_diffuse ) );
}

const kvs::Vector4f Material::specular( void ) const
{
    return( kvs::Vector4f( m_specular ) );
}

const float Material::shininess( void ) const
{
    return( m_shininess );
}

void Material::setFace( MaterialFace face )
{
    m_face = face;
}

void Material::setAmbient( float r, float g, float b, float a )
{
    m_ambient[0] = r;
    m_ambient[1] = g;
    m_ambient[2] = b;
    m_ambient[3] = a;
}

void Material::setAmbient( const float ambient[4] )
{
    memcpy( m_ambient, ambient, sizeof(float) * 4 );
}

void Material::setAmbient( const RGBAColor& ambient )
{
    float ambi[4] = { static_cast<float>(ambient.r()) / 255.0f,
                      static_cast<float>(ambient.g()) / 255.0f,
                      static_cast<float>(ambient.b()) / 255.0f,
                      static_cast<float>(ambient.a()) };

    memcpy( m_ambient, ambi, sizeof(float) * 4 );
}

void Material::setDiffuse( float r, float g, float b, float a )
{
    m_diffuse[0] = r;
    m_diffuse[1] = g;
    m_diffuse[2] = b;
    m_diffuse[3] = a;
}

void Material::setDiffuse( const float diffuse[4] )
{
    memcpy( m_diffuse, diffuse, sizeof(float) * 4 );
}

void Material::setDiffuse( const kvs::RGBAColor& diffuse )
{
    float diff[4] = { static_cast<float>(diffuse.r()) / 255.0f,
                      static_cast<float>(diffuse.g()) / 255.0f,
                      static_cast<float>(diffuse.b()) / 255.0f,
                      static_cast<float>(diffuse.a()) };

    memcpy( m_diffuse, diff, sizeof(float) * 4 );
}

void Material::setSpecular( float r, float g, float b, float a )
{
    m_specular[0] = r;
    m_specular[1] = g;
    m_specular[2] = b;
    m_specular[3] = a;
}

void Material::setSpecular( const float specular[4] )
{
    memcpy( m_specular, specular, sizeof(float) * 4 );
}

void Material::setSpecular( const kvs::RGBAColor& specular )
{
    float spec[4] = { static_cast<float>(specular.r()) / 255.0f,
                      static_cast<float>(specular.g()) / 255.0f,
                      static_cast<float>(specular.b()) / 255.0f,
                      static_cast<float>(specular.a()) };

    memcpy( m_specular, spec, sizeof(float) * 4 );
}

void Material::setShininess( float shininess )
{
    m_shininess = shininess;
}

void Material::apply( void )
{
    glMaterialfv( (GLenum)m_face, GL_AMBIENT,   m_ambient );
    glMaterialfv( (GLenum)m_face, GL_DIFFUSE,   m_diffuse );
    glMaterialfv( (GLenum)m_face, GL_SPECULAR,  m_specular );
    glMaterialf(  (GLenum)m_face, GL_SHININESS, m_shininess );
}

} // end of namespace kvs
