/*****************************************************************************/
/**
 *  @file   ObjectBase.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__OBJECT_BASE_H_INCLUDE
#define KVS__OBJECT_BASE_H_INCLUDE

#include <iostream>
#include <kvs/XformControl>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Module>
#include <kvs/Indent>
#include <kvs/Deprecated>
#if KVS_ENABLE_DEPRECATED
#include <kvs/Material>
#endif


namespace kvs
{

class Camera;

/*==========================================================================*/
/**
 *  Object base class.
 */
/*==========================================================================*/
class ObjectBase : public kvs::XformControl
{
    kvsModuleBase;
    kvsModuleName( kvs::ObjectBase );

public:

    enum ObjectType
    {
        Geometry = 0,  ///< Geometric object.
        Volume,        ///< Volumetric object.
        Image,         ///< Image object
        Table,         ///< table object
        ObjectManager, ///< Object manager
        UnknownObject  ///< unknown object (for user defined object data)
    };

#if KVS_ENABLE_DEPRECATED
    enum Face
    {
        Front        = kvs::Material::Front,
        Back         = kvs::Material::Back,
        FrontAndBack = kvs::Material::FrontAndBack
    };
#endif

private:

    bool m_can_collision; ///< flag for collision detection
    std::string m_name; ///< object name
    kvs::Vector3f m_min_object_coord; ///< min coord in the object coordinate system
    kvs::Vector3f m_max_object_coord; ///< max coord in the object coordinate system
    kvs::Vector3f m_min_external_coord; ///< min coord in the external coordinate system
    kvs::Vector3f m_max_external_coord; ///< max coord in the external coordinate system
    bool m_has_min_max_object_coords; ///< has min-max coorinate values ?
    bool m_has_min_max_external_coords; ///< has min-max coorinate values ?
    kvs::Vector3f m_object_center; ///< center of gravity in object coordinate system
    kvs::Vector3f m_external_position; ///< position in external coordinate system
    kvs::Vector3f m_normalize; ///< normalize parameter
#if KVS_ENABLE_DEPRECATED
    kvs::Material m_material; ///< material
#endif
    bool m_show_flg; ///< flag for showing object

public:

    ObjectBase( const bool collision = true );
    virtual ~ObjectBase();

    ObjectBase& operator = ( const ObjectBase& object );

    void setName( const std::string& name );
    void setMinMaxObjectCoords( const kvs::Vector3f& min_coord, const kvs::Vector3f& max_coord );
    void setMinMaxExternalCoords( const kvs::Vector3f& min_coord, const kvs::Vector3f& max_coord );
#if KVS_ENABLE_DEPRECATED
    void setMaterial( const kvs::Material& material );
    void setFace( const Face face );
#endif
    void show();
    void hide();
    virtual void print( std::ostream& os, const kvs::Indent& indent = kvs::Indent(0) ) const;

    const std::string& name() const;
    virtual ObjectType objectType() const = 0;
    const kvs::Vector3f& minObjectCoord() const;
    const kvs::Vector3f& maxObjectCoord() const;
    const kvs::Vector3f& minExternalCoord() const;
    const kvs::Vector3f& maxExternalCoord() const;
    bool hasMinMaxObjectCoords() const;
    bool hasMinMaxExternalCoords() const;
    const kvs::Vector3f& objectCenter() const;
    const kvs::Vector3f& externalPosition() const;
    const kvs::Vector3f& normalize() const;
    bool isShown() const;
#if KVS_ENABLE_DEPRECATED
    const kvs::Material& material() const;
#endif
    const kvs::Vector2f positionInDevice( kvs::Camera* camera, const kvs::Vector3f& global_trans, const kvs::Vector3f& global_scale ) const;
    const kvs::Vector3f positionInWorld( const kvs::Vector3f& global_trans, const kvs::Vector3f& global_scale ) const;
    const kvs::Vector3f& positionInExternal() const;

    virtual void updateMinMaxCoords(){};
    void updateNormalizeParameters();
    void transform( const kvs::Vector3f& Tg, const kvs::Vector3f& Sg ) const;
#if KVS_ENABLE_DEPRECATED
    void applyMaterial();
#endif
    bool collision( const kvs::Vector2f& p_win, kvs::Camera* camera, const kvs::Vector3f& global_trans, const kvs::Vector3f& global_scale );
    bool collision( const kvs::Vector3f& p_world, const kvs::Vector3f& global_trans, const kvs::Vector3f& global_scale );

    void enableCollision();
    void disableCollision();
    bool canCollision() const;

protected:

    void setObjectCenter( const kvs::Vector3f& object_center );
    void setNormalize( const kvs::Vector3f& normalize );

private:

    const kvs::Vector3f object_to_world_coordinate(
        const kvs::Vector3f& p_obj,
        const kvs::Vector3f& global_trans,
        const kvs::Vector3f& global_scale ) const;

public:

    KVS_DEPRECATED( ObjectBase( const kvs::Vector3f& translation, const kvs::Vector3f& scaling, const kvs::Matrix33f& rotation, const bool collision = true ) )
    {
        m_can_collision = collision;
        m_name = std::string("unknown");
        m_min_object_coord = kvs::Vector3f( -3.0, -3.0, -3.0 );
        m_max_object_coord = kvs::Vector3f(  3.0,  3.0,  3.0 );
        m_min_external_coord = kvs::Vector3f( -3.0, -3.0, -3.0 );
        m_max_external_coord = kvs::Vector3f(  3.0,  3.0,  3.0 );
        m_has_min_max_object_coords = false;
        m_has_min_max_external_coords = false;
        m_show_flg = true;

        this->setXform( kvs::Xform( translation, scaling, rotation ) );
        this->saveXform();
    }

    KVS_DEPRECATED( void rotate( const kvs::Matrix33f& rotation, const kvs::Vector3f& center ) )
    {
        const kvs::Xform x = kvs::Xform::Translation( center )
                           * kvs::Xform::Rotation( rotation )
                           * kvs::Xform::Translation( -center );
        this->multiplyXform( x );
    }

    KVS_DEPRECATED( void scale( const kvs::Vector3f& scaling, const kvs::Vector3f& center ) )
    {
        const kvs::Xform x = kvs::Xform::Translation( center )
                           * kvs::Xform::Scaling( scaling )
                           * kvs::Xform::Translation( -center );
        this->multiplyXform( x );
    }

    KVS_DEPRECATED( friend std::ostream& operator << ( std::ostream& os, const ObjectBase& object ) );
};

} // end of namespace kvs

#endif // KVS__OBJECT_BASE_H_INCLUDE
