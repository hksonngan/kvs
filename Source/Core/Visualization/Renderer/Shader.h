/****************************************************************************/
/**
 *  @file Shader.h
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
#ifndef KVS_CORE_SHADER_H_INCLUDE
#define KVS_CORE_SHADER_H_INCLUDE

#include <kvs/Vector3>
#include <kvs/Camera>
#include <kvs/Light>


namespace kvs
{

/*==========================================================================*/
/**
 *  Shader class.
 */
/*==========================================================================*/
class Shader
{
public:

    enum Type
    {
        UnknownShading = 0, ///< unknown shading type
        LambertShading,     ///< Lambertian shading
        PhongShading,       ///< Phong shading
        BlinnPhongShading   ///< Blinn-Phong shading
    };

    struct Base
    {
        kvs::Vector3f camera_position; ///< camera position in the object coordinate
        kvs::Vector3f light_position; ///< light position in the object coordinate

        Base( void );

        virtual ~Base( void );

        virtual void set( const kvs::Camera* camera, const kvs::Light* light ) = 0;

        virtual const Shader::Type type( void ) const = 0;

        virtual const float attenuation( const kvs::Vector3f& vertex, const kvs::Vector3f& gradient ) const = 0;
    };

public:

    typedef Base shader_type;

public:

    struct Lambert : public Base
    {
        float Ka; ///< ambient coefficient
        float Kd; ///< diffuse coefficient

        Lambert( void );

        Lambert( const Lambert& shader );

        Lambert( const float ka, const float kd );

        void set( const kvs::Camera* camera, const kvs::Light* light );

        const Shader::Type type( void ) const;

        const float attenuation( const kvs::Vector3f& vertex, const kvs::Vector3f& gradient ) const;
    };

    struct Phong : public Base
    {
        float Ka; ///< ambient coefficient
        float Kd; ///< diffuse coefficient
        float Ks; ///< specular coefficient
        float S;  ///< shininess

        Phong( void );

        Phong( const Phong& shader );

        Phong( const float ka, const float kd, const float ks, const float s );

        void set( const kvs::Camera* camera, const kvs::Light* light );

        const Shader::Type type( void ) const;

        const float attenuation( const kvs::Vector3f& vertex, const kvs::Vector3f& gradient ) const;
    };

    struct BlinnPhong : public Base
    {
        float Ka; ///< ambient coefficient
        float Kd; ///< diffuse coefficient
        float Ks; ///< specular coefficient
        float S;  ///< shininess

        BlinnPhong( void );

        BlinnPhong( const BlinnPhong& shader );

        BlinnPhong( const float ka, const float kd, const float ks, const float s );

        void set( const kvs::Camera* camera, const kvs::Light* light );

        const Shader::Type type( void ) const;

        const float attenuation( const kvs::Vector3f& vertex, const kvs::Vector3f& gradient ) const;
    };
};

} // end of namespace kvs

#endif // KVS_CORE_SHADER_H_INCLUDE
