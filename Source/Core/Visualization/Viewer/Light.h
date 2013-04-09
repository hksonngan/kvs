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
#include <kvs/Vector3>
#include <kvs/Camera>
#include <kvs/Deprecated>


namespace kvs
{

class RGBAColor;

/*==========================================================================*/
/**
 *  Light class
 */
/*==========================================================================*/
class Light : public kvs::XformControl
{
private:
    kvs::Vector3f m_transform_center;
    unsigned int  m_id; ///< light ID
    kvs::Vector3f m_diffuse; ///< diffuse color
    kvs::Vector3f m_ambient; ///< ambient color
    kvs::Vector3f m_specular; ///< specular color

public:

    static void SetModelLocalViewer( bool flag );
    static void SetModelTwoSide( bool flag );
    static void SetModelAmbient( float ambient[4] );

public:

    Light();
    virtual ~Light();

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

    const kvs::Vector3f position() const;
    const kvs::Vector3f& diffuse() const;
    const kvs::Vector3f& ambient() const;
    const kvs::Vector3f& specular() const;

    virtual void update( const kvs::Camera* camera );
    void initialize();
    void on() const;
    void off() const;
    bool isEnabled() const;

    void resetXform();
    void rotate( const kvs::Matrix33f& rotation );
    void translate( const kvs::Vector3f& translation );
    void scale( const kvs::Vector3f& scaling );

public:

    KVS_DEPRECATED( static void setModelLocalViewer( bool flag ) ) { SetModelLocalViewer( flag ); }
    KVS_DEPRECATED( static void setModelTwoSide( bool flag ) ) { SetModelTwoSide( flag ); }
    KVS_DEPRECATED( static void setModelAmbient( float ambient[4] ) ) { SetModelAmbient( ambient ); }
};

} // end of namespace kvs

#endif // KVS__LIGHT_H_INCLUDE
