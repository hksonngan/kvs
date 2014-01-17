/****************************************************************************/
/**
 *  @file   ObjectManager.cpp
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
/****************************************************************************/
#include "ObjectManager.h"
#include <iostream>
#include <kvs/Camera>
#include <kvs/Math>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Vector4>
#include <kvs/OpenGL>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Creates a new ObjectManager class.
 */
/*===========================================================================*/
ObjectManager::ObjectManager() :
    kvs::ObjectBase( true )
{
    m_object_tree.clear();
    m_has_active_object = false;
    m_enable_all_move = true;
    m_object_map.clear();

    m_current_object_id = 0;
    this->insert_root();

    const kvs::Vec3 min_obj = kvs::Vec3::All(  1000000.0f );
    const kvs::Vec3 max_obj = kvs::Vec3::All( -1000000.0f );
    ObjectBase::setMinMaxObjectCoords( min_obj, max_obj );

    const kvs::Vec3 min_ext = kvs::Vec3::All( -3.0f );
    const kvs::Vec3 max_ext = kvs::Vec3::All(  3.0f );
    ObjectBase::setMinMaxExternalCoords( min_ext, max_ext );
}

/*===========================================================================*/
/**
 *  @brief  Destroys the ObjectManager class.
 */
/*===========================================================================*/
ObjectManager::~ObjectManager()
{
    ObjectIterator object = m_object_tree.begin();
    ObjectIterator last = m_object_tree.end();
    ++object; // Skip the root object (the object manager)
    while ( object != last )
    {
        delete *object;
        ++object;
    }

    m_object_tree.clear();
    m_object_map.clear();
}

/*===========================================================================*/
/**
 *  @brief  Returns the object type (ObjectManager).
 *  @return object type
 */
/*===========================================================================*/
kvs::ObjectBase::ObjectType ObjectManager::objectType() const
{
    return kvs::ObjectBase::ObjectManager;
}

/*==========================================================================*/
/**
 *  @brief  Insert a pointer to the object base to the object master.
 *  @param  object [in] pointer to the object base
 *  @return object ID
 */
/*==========================================================================*/
int ObjectManager::insert( kvs::ObjectBase* object )
{
    // Updates the normalize parameters of the object manager and the object.
    const kvs::Vec3 min_ext = object->minExternalCoord();
    const kvs::Vec3 max_ext = object->maxExternalCoord();
    this->update_normalize_parameters( min_ext, max_ext );
    object->updateNormalizeParameters();

    // Calculate the object ID by counting the number of this method called.
    // Therefore, we define the object ID as static parameter in this method
    // and count it.
    m_current_object_id++;

    // A pair of the object ID and a pointer to the object is inserted to
    // the object map. The pointer to the object is got by inserting the
    // object to the object master base.
    ObjectIterator parent = m_root;
    ObjectIterator current = m_object_tree.appendChild( parent, object );
    m_object_map.insert( ObjectPair( m_current_object_id, current ) );

    return m_current_object_id;
}

/*==========================================================================*/
/**
 *  @brief  Append the object under the parent object specified by ID number.
 *  @param  id [in] ID of the parent object
 *  @param  object [in] pointer to the object
 *  @return object ID
 */
/*==========================================================================*/
int ObjectManager::insert( int id, kvs::ObjectBase* object )
{
    // Updates the normalize parameters of the object manager and the object.
    const kvs::Vec3 min_ext = object->minExternalCoord();
    const kvs::Vec3 max_ext = object->maxExternalCoord();
    this->update_normalize_parameters( min_ext, max_ext );
    object->updateNormalizeParameters();

    // Finds the parent object by the specified ID.
    ObjectMap::iterator map_id = m_object_map.find( id );
    if ( map_id == m_object_map.end() ) { return -1; }

    // Append the object.
    m_current_object_id++;

    ObjectIterator parent = map_id->second;
    ObjectIterator current = m_object_tree.appendChild( parent, object );
    m_object_map.insert( ObjectPair( m_current_object_id, current ) );

    return m_current_object_id;
}

/*==========================================================================*/
/**
 *  @brief  Erase the all objects.
 *  @param  delete_flag [in] deleting the allocated memory flag
 *
 *  Erase the all objects, which is registrated in the object manager.
 *  Simultaniously, the allocated memory region for the all objects is deleted.
 */
/*==========================================================================*/
void ObjectManager::erase( bool delete_flag )
{
    ObjectIterator object = m_object_tree.begin();
    ObjectIterator last = m_object_tree.end();
    ++object; // skip the root object (the object manager)

    if ( delete_flag )
    {
        while ( object != last )
        {
            delete *object;
            ++object;
        }
    }

    m_object_tree.clear();
    m_object_map.clear();

    this->insert_root();
    this->update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  @brief  Erase the object by a specificated object ID.
 *  @param  id [in] object ID
 *  @param  delete_flag [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void ObjectManager::erase( int id, bool delete_flag )
{
    // Search the object which is specified by given object ID in the
    // object pointer map. If it isn't found, this method executes nothing.
    ObjectMap::iterator map_id = m_object_map.find( id );
    if ( map_id == m_object_map.end() ) { return; }

    // Delete the object.
    ObjectIterator object = map_id->second; // pointer to the object node
    if ( delete_flag ) { delete *object; }

    // Erase the object in the object master base.
    m_object_tree.erase( object );

    // Erase the map component, which is specified by map_id.
    m_object_map.erase( map_id );

    this->update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  @brief  Erase the object by a specificated object name.
 *  @param  name [in] object name
 *  @param  delete_flag [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void ObjectManager::erase( std::string name, bool delete_flag )
{
    ObjectMap::iterator map_id = m_object_map.begin();
    ObjectMap::iterator map_end = m_object_map.end();
    while ( map_id != map_end )
    {
        ObjectIterator object = map_id->second;
        if ( (*object)->name() == name )
        {
            // Erase the object specified by the name.
            if ( delete_flag ) { delete *object; }
            m_object_tree.erase( object );
            m_object_map.erase( map_id );

            this->update_normalize_parameters();
            break;
        }
        ++map_id;
    }
}

/*==========================================================================*/
/**
 *  @brief  Change the object by a specificated object ID.
 *  @param  id [in] object ID registered in the object manager
 *  @param  object [in] pointer to the inserting object
 *  @param  delete_flag [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void ObjectManager::change( int id, ObjectBase* object, bool delete_flag )
{
    // Search the object which is specified by given object ID in the
    // object pointer map. If it isn't found, this method executes nothing.
    ObjectMap::iterator map_id = m_object_map.find( id );
    if ( map_id == m_object_map.end() ) { return; }

    // Save the xform of the object specified by the given ID.
    kvs::ObjectBase* registered_object = *(map_id->second);
    const kvs::Xform x = registered_object->xform();

    // Erase the old object
    if ( delete_flag ) { delete registered_object; }

    // Change the object
    object->updateNormalizeParameters();
    object->setXform( x );
    *(map_id->second) = object;

    this->update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  @brief  Change the object by a specificated object name.
 *  @param  name [in] object name registered in the object manager
 *  @param  object [in] pointer to the inserting object
 *  @param  delete_flag [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void ObjectManager::change( std::string name, kvs::ObjectBase* object, bool delete_flag )
{
    ObjectMap::iterator map_id = m_object_map.begin();
    ObjectMap::iterator map_end = m_object_map.end();
    while ( map_id != map_end )
    {
        kvs::ObjectBase* registered_object = *(map_id->second);
        if ( registered_object->name() == name )
        {
            const kvs::Xform x = registered_object->xform();
            if ( delete_flag ) { delete registered_object; }

            object->updateNormalizeParameters();
            object->setXform( x );
            *(map_id->second) = object;

            this->update_normalize_parameters();
            break;
        }

        ++map_id;
    }
}

/*==========================================================================*/
/**
 *  @brief  Returns the pointer to the top object.
 *  @return pointer to the top object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::object()
{
    ObjectIterator object = m_object_tree.begin();
    ++object; // Skip the root object.

    return *object;
}

/*==========================================================================*/
/**
 *  @brief  Returns the object by a specificated object ID.
 *  @param  id [in] object ID
 *  @return pointer to the object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::object( int id )
{
    // Search the object which is specified by given object ID in the
    // object pointer map. If it isn't found, this method executes nothing.
    ObjectMap::iterator map_id = m_object_map.find( id );
    if ( map_id == m_object_map.end() ) { return NULL; }

    // Pointer to the object
    ObjectIterator object = map_id->second;

    return *object;
}

/*==========================================================================*/
/**
 *  @brief  Returns the object by a specificated object name.
 *  @param  name [in] object name
 *  @return pointer to the object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::object( std::string name )
{
    ObjectMap::iterator map_id = m_object_map.begin();
    ObjectMap::iterator map_end = m_object_map.end();
    while ( map_id != map_end )
    {
        kvs::ObjectBase* object = *(map_id->second);
        if ( object->name() == name ) { return object; }
        ++map_id;
    }

    return NULL;
}

/*==========================================================================*/
/**
 *  @brief  Returns the pointer to the active object.
 *  @return pointer to the active object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::activeObject()
{
    return m_has_active_object ? *m_active_object : NULL;
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of the stored objects in the object manager.
 *  @return number of the stored objects
 */
/*==========================================================================*/
int ObjectManager::numberOfObjects() const
{
    return m_object_tree.size();
}

/*==========================================================================*/
/**
 *  @brief  Check the including object in the object master.
 *  @return true, if some objects are included.
 */
/*==========================================================================*/
bool ObjectManager::hasObject() const
{
    return m_object_tree.size() > 1;
}

/*==========================================================================*/
/**
 *  @brief  Check whether the object manager has the active object.
 *  @return true, if the object manager has the active object.
 */
/*==========================================================================*/
bool ObjectManager::hasActiveObject() const
{
    return m_has_active_object;
}

/*===========================================================================*/
/**
 *  @brief  Returns the object ID from the pointer to the object.
 *  @param  object [in] pointer to the object
 *  @return object ID
 */
/*===========================================================================*/
int ObjectManager::objectID( const kvs::ObjectBase *object ) const
{
    ObjectMap::const_iterator map_id = m_object_map.begin();
    ObjectMap::const_iterator map_end = m_object_map.end();
    while ( map_id != map_end )
    {
        const kvs::ObjectBase* registered_object = *(map_id->second);
        if ( registered_object == object ) { return map_id->first; }
        ++map_id;
    }

    return -1;
}

/*===========================================================================*/
/**
 *  @brief  Returns the parent object ID from the object iterator.
 *  @param  it [in] object iterator
 *  @return parent object ID
 */
/*===========================================================================*/
int ObjectManager::parentObjectID( const ObjectIterator it ) const
{
    if ( it == m_object_tree.end() ) { return -1; }
    if ( it.node()->parent == NULL ) { return -1; }
    return this->objectID( it.node()->parent->data );
}

/*===========================================================================*/
/**
 *  @brief  Returns the parent object ID from the pointer to the object.
 *  @param  object [in] pointer to the object
 *  @return parent object ID
 */
/*===========================================================================*/
int ObjectManager::parentObjectID( const kvs::ObjectBase *object ) const
{
    ObjectIterator registered_object = m_object_tree.begin();
    ObjectIterator last = m_object_tree.end();
    while ( registered_object != last )
    {
        if ( *registered_object == object)
        {
            return this->parentObjectID( registered_object );
        }

        ++registered_object;
    }

    return -1;
}

/*===========================================================================*/
/**
 *  @brief  Returns the parent object ID from the object ID.
 *  @param  id [in] object ID
 *  @return parent object ID
 */
/*===========================================================================*/
int ObjectManager::parentObjectID( int id ) const
{
    if ( id < 0 ) { return -1; }

    ObjectManager* manager = const_cast<ObjectManager*>( this );
    const kvs::ObjectBase* object = manager->object( id );
    if ( object == NULL ) { return -1; }

    return this->parentObjectID( object );
}

/*==========================================================================*/
/**
 *  @brief  Returns the active object ID.
 *  @return active object ID, if active object is nothing, -1 is returned.
 */
/*==========================================================================*/
int ObjectManager::activeObjectID() const
{
    if ( m_has_active_object )
    {
        ObjectMap::const_iterator map_id = m_object_map.begin();
        ObjectMap::const_iterator map_end = m_object_map.end();
        while ( map_id != map_end )
        {
            if ( m_active_object == map_id->second ) { return map_id->first; }
            ++map_id;
        }
    }

    return -1;
}

/*==========================================================================*/
/**
 *  @brief  Returns the xform of the object manager.
 */
/*==========================================================================*/
kvs::Xform ObjectManager::xform() const
{
    return kvs::ObjectBase::xform();
}

/*==========================================================================*/
/**
 *  @brief  Returns the xform of the object which is specified by the given ID.
 *  @param  id [in] object ID
 */
/*==========================================================================*/
kvs::Xform ObjectManager::xform( int id ) const
{
    // Search the object which is specified by given object ID in the
    // object pointer map. If it isn't found, this method retrun initial Xform.
    ObjectMap::const_iterator map_id = m_object_map.find( id );
    if ( map_id == m_object_map.end() )
    {
        kvs::Xform xform;
        return xform;
    }

    kvs::ObjectBase* object = *(map_id->second);
    return object->xform();
}

/*==========================================================================*/
/**
 *  @brief  Reset the xforms of the all objects.
 */
/*==========================================================================*/
void ObjectManager::resetXform()
{
    ObjectIterator object = m_object_tree.begin();
    ObjectIterator last = m_object_tree.end();
    while ( object != last ) { (*object)->resetXform(); ++object; }

    kvs::ObjectBase::resetXform();
}

/*==========================================================================*/
/**
 *  @brief  Reset the xform of the object which is specified by given ID.
 *  @param  id [in] object ID
 */
/*==========================================================================*/
void ObjectManager::resetXform( int id )
{
    ObjectMap::iterator map_id = m_object_map.find( id );
    if( map_id == m_object_map.end() ) { return; }

    ObjectIterator object = map_id->second;
    ObjectIterator child_object = m_object_tree.begin( object );
    ObjectIterator last = m_object_tree.end( object );

    const kvs::Xform x = this->xform() * (*object)->xform().inverse();
    (*object)->setXform( this->xform() );

    while ( child_object != last )
    {
        (*child_object)->setXform( x * (*child_object)->xform() );
        ++child_object;
    }
}

/*==========================================================================*/
/**
 *  @brief  Release the xform of the active object.
 */
/*==========================================================================*/
void ObjectManager::resetActiveObjectXform()
{
    if ( m_has_active_object )
    {
        (*m_active_object)->resetXform();
        (*m_active_object)->multiplyXform( this->xform() );
    }
}

/*==========================================================================*/
/**
 *  @brief  Sets the active object ID.
 *  @param  id [in] object ID
 *  @return true, if the object specified by the given ID is found.
 */
/*==========================================================================*/
bool ObjectManager::setActiveObject( int id )
{
    ObjectMap::iterator map_id = m_object_map.find( id );
    if ( map_id == m_object_map.end() ) { return false; }

    m_active_object = map_id->second;
    m_has_active_object = true;

    return true;
}

/*==========================================================================*/
/**
 *  @brief  Erase the active object.
 */
/*==========================================================================*/
void ObjectManager::eraseActiveObject()
{
    if ( m_has_active_object )
    {
        delete *m_active_object;
        *m_active_object = NULL;
        m_object_tree.erase( m_active_object );
    }

    this->update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  @brief  Release the active object.
 */
/*==========================================================================*/
void ObjectManager::releaseActiveObject()
{
    m_has_active_object = false;
}

/*==========================================================================*/
/**
 *  @brief  Enable to move all objects.
 */
/*==========================================================================*/
void ObjectManager::enableAllMove()
{
    m_enable_all_move = true;
}

/*==========================================================================*/
/**
 *  @brief  Disable to move all objects.
 */
/*==========================================================================*/
void ObjectManager::disableAllMove()
{
    m_enable_all_move = false;
}

/*==========================================================================*/
/**
 *  @brief  Check whether the object manager is able to move all objects or not.
 *  @return true, if the object manager is able to move all objects.
 */
/*==========================================================================*/
bool ObjectManager::isEnableAllMove() const
{
    return m_enable_all_move;
}

/*==========================================================================*/
/**
 *  @brief  Test the collision detection.
 *  @param  p_win [in] point in the window coordinate
 *  @param  camera [in] pointer to the camera
 *  @return true, if the collision is detected.
 */
/*==========================================================================*/
bool ObjectManager::detectCollision( const kvs::Vec2& p_win, kvs::Camera* camera )
{
    const kvs::Vec3 center = ObjectBase::objectCenter();
    const kvs::Vec3 scale = ObjectBase::normalize();

    double min_distance = 100000.0;
    ObjectIterator object = m_object_tree.begin();
    ObjectIterator last = m_object_tree.end();
    ++object; // Skip the root object.
    while ( object != last )
    {
        if ( !(*object)->canCollision() ) { continue; }

        const kvs::Vec2 p = (*object)->positionInDevice( camera, center, scale );
        const kvs::Vec2 diff = p - p_win;
        const double distance = diff.length();
        if ( distance < min_distance )
        {
            min_distance = distance;
            m_active_object = object;
        }

        ++object;
    }

    m_has_active_object =
        (*m_active_object)->collision( p_win, camera, center, scale );

    return m_has_active_object;
}

/*==========================================================================*/
/**
 *  @brief  Test the collision detection.
 *  @param  p_world [in] point in the world coordinate
 *  @return true, if the collision is detected.
 */
/*==========================================================================*/
bool ObjectManager::detectCollision( const kvs::Vec3& p_world )
{
    const kvs::Vec3 center = ObjectBase::objectCenter();
    const kvs::Vec3 scale = ObjectBase::normalize();

    double min_distance = 100000;
    ObjectIterator object = m_object_tree.begin();
    ObjectIterator last = m_object_tree.end();
    ++object; // Skip the root object.
    while ( object != last )
    {
        if ( !(*object)->canCollision() ) { continue; }

        const kvs::Vec3 p = (*object)->positionInWorld( center, scale );
        const kvs::Vec3 diff = p - p_world;
        const double distance = diff.length();
        if ( distance < min_distance )
        {
            min_distance = distance;
            m_active_object = object;
        }
    }

    m_has_active_object =
        (*m_active_object)->collision( p_world, center, scale );

    return m_has_active_object;
}

/*==========================================================================*/
/**
 *  @brief  Rotate the all objects.
 *  @param  rotation [in] current rotation matrix.
 */
/*==========================================================================*/
void ObjectManager::rotate( const kvs::Mat3& rotation )
{
    kvs::ObjectBase* object = this->get_control_target();

    // The center of rotation will be set to the center of gravity of
    // the control target object.
    const kvs::Vec3 center = this->get_rotation_center( object );
    const kvs::Xform x =
        kvs::Xform::Translation( center ) *
        kvs::Xform::Rotation( rotation ) *
        kvs::Xform::Translation( -center );
    object->multiplyXform( x );

    // Apply the xform to all of the registered objects.
    ObjectIterator registered_object = this->get_control_first_pointer();
    ObjectIterator last = this->get_control_last_pointer();
    while ( registered_object != last )
    {
        (*registered_object)->multiplyXform( x );
        ++registered_object;
    }
}

/*==========================================================================*/
/**
 *  @brief  Translate the all objects.
 *  @param  translation [in] current translation vector
 */
/*==========================================================================*/
void ObjectManager::translate( const kvs::Vec3& translation )
{
    kvs::ObjectBase* object = this->get_control_target();

    const kvs::Xform x = kvs::Xform::Translation( translation );
    object->multiplyXform( x );

    // Apply the xform to all of the registered objects.
    ObjectIterator registered_object = this->get_control_first_pointer();
    ObjectIterator last = this->get_control_last_pointer();
    while ( registered_object != last )
    {
        (*registered_object)->multiplyXform( x );
        ++registered_object;
    }
}

/*==========================================================================*/
/**
 *  @brief  Scaling the all objects.
 *  @param  scaling [in] current scaling value.
 */
/*==========================================================================*/
void ObjectManager::scale( const kvs::Vec3& scaling )
{
    kvs::ObjectBase* object = this->get_control_target();

    // The center of scaling will be set to the center of gravity of
    // the control target object.
    const kvs::Vec3 center = this->get_rotation_center( object );
    const kvs::Xform x =
        kvs::Xform::Translation( center ) *
        kvs::Xform::Scaling( scaling ) *
        kvs::Xform::Translation( -center );
    object->multiplyXform( x );

    // Apply the xform to all of the registered objects.
    ObjectIterator registered_object = this->get_control_first_pointer();
    ObjectIterator last = this->get_control_last_pointer();
    while ( registered_object != last )
    {
        (*registered_object)->multiplyXform( x );
        ++registered_object;
    }
}

/*==========================================================================*/
/**
 *  @brief  Returns the position of the object manager in the device coordinate.
 *  @param  camera [in] pointer to the camera
 */
/*==========================================================================*/
kvs::Vec2 ObjectManager::positionInDevice( kvs::Camera* camera ) const
{
    kvs::OpenGL::PushMatrix();
    camera->update();
    kvs::Vec3 p = kvs::ObjectBase::xform().translation();
    kvs::Vec2 ret = camera->projectObjectToWindow( p );
    ret.y() = camera->windowHeight() - ret.y();
    kvs::OpenGL::PopMatrix();

    return ret;
}

/*==========================================================================*/
/**
 *  @brief  Update the external coordinate.
 */
/*==========================================================================*/
void ObjectManager::updateExternalCoords()
{
    this->update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  @brief  Insert the root of the objects.
 */
/*==========================================================================*/
void ObjectManager::insert_root()
{
    m_root = m_object_tree.insert( m_object_tree.begin(), this );
}

/*==========================================================================*/
/**
 *  @brief  Update the normalize parameters.
 *  @param  min_ext [in] min. external coordinate value
 *  @param  max_ext [in] max. external coordinate value
 */
/*==========================================================================*/
void ObjectManager::update_normalize_parameters(
    const kvs::Vec3& min_ext,
    const kvs::Vec3& max_ext )
{
    if ( kvs::Math::Equal( 0.0f, min_ext.x() ) &&
         kvs::Math::Equal( 0.0f, min_ext.y() ) &&
         kvs::Math::Equal( 0.0f, min_ext.z() ) &&
         kvs::Math::Equal( 0.0f, max_ext.x() ) &&
         kvs::Math::Equal( 0.0f, max_ext.y() ) &&
         kvs::Math::Equal( 0.0f, max_ext.z() ) ) { return; }

    const kvs::Vec3 min_obj(
        kvs::Math::Min( ObjectBase::minObjectCoord().x(), min_ext.x() ),
        kvs::Math::Min( ObjectBase::minObjectCoord().y(), min_ext.y() ),
        kvs::Math::Min( ObjectBase::minObjectCoord().z(), min_ext.z() ) );
    const kvs::Vec3 max_obj(
        kvs::Math::Max( ObjectBase::maxObjectCoord().x(), max_ext.x() ),
        kvs::Math::Max( ObjectBase::maxObjectCoord().y(), max_ext.y() ),
        kvs::Math::Max( ObjectBase::maxObjectCoord().z(), max_ext.z() ) );
    ObjectBase::setMinMaxObjectCoords( min_obj, max_obj );

    const kvs::Vec3 diff = max_obj - min_obj;
    const float max_diff = kvs::Math::Max( diff.x(), diff.y(), diff.z() );
    const float normalize = 6.0f / max_diff;

    ObjectBase::setNormalize( kvs::Vec3::All( normalize ) );
    ObjectBase::setObjectCenter( ( max_obj + min_obj ) * 0.5f );
}

/*==========================================================================*/
/**
 *  @brief  Update normalize parameters.
 */
/*==========================================================================*/
void ObjectManager::update_normalize_parameters()
{
    kvs::Vec3 min_ext = kvs::Vec3::All( -3.0f );
    kvs::Vec3 max_ext = kvs::Vec3::All(  3.0f );
    ObjectBase::setMinMaxExternalCoords( min_ext, max_ext );

    kvs::Vec3 min_obj = kvs::Vec3::All(  1000000 );
    kvs::Vec3 max_obj = kvs::Vec3::All( -1000000 );
    int counter = 0;
    if ( m_object_tree.size() > 1 )
    {
        ObjectIterator object = m_object_tree.begin();
        ObjectIterator last = m_object_tree.end();
        ++object; // Skip the root object
        while ( object != last )
        {
            min_ext = (*object)->minExternalCoord();
            max_ext = (*object)->maxExternalCoord();

            if ( kvs::Math::Equal( 0.0f, min_ext.x() ) &&
                 kvs::Math::Equal( 0.0f, min_ext.y() ) &&
                 kvs::Math::Equal( 0.0f, min_ext.z() ) &&
                 kvs::Math::Equal( 0.0f, max_ext.x() ) &&
                 kvs::Math::Equal( 0.0f, max_ext.y() ) &&
                 kvs::Math::Equal( 0.0f, max_ext.z() ) ) { continue; }

            min_obj.x() = kvs::Math::Min( min_obj.x(), min_ext.x() );
            min_obj.y() = kvs::Math::Min( min_obj.y(), min_ext.y() );
            min_obj.z() = kvs::Math::Min( min_obj.z(), min_ext.z() );
            max_obj.x() = kvs::Math::Max( max_obj.x(), max_ext.x() );
            max_obj.y() = kvs::Math::Max( max_obj.y(), max_ext.y() );
            max_obj.z() = kvs::Math::Max( max_obj.z(), max_ext.z() );

            ++counter;
            ++object;
        }
    }

    ObjectBase::setMinMaxObjectCoords( min_obj, max_obj );

    if ( counter == 0 )
    {
        ObjectBase::setNormalize( kvs::Vec3::All( 1.0 ) );
        ObjectBase::setObjectCenter( kvs::Vec3::All( 0.0 ) );
    }
    else
    {
        const kvs::Vec3 diff = max_obj - min_obj;
        const float max_diff = kvs::Math::Max( diff.x(), diff.y(), diff.z() );
        const float normalize = 6.0f / max_diff;
        ObjectBase::setNormalize( kvs::Vec3::All( normalize ) );
        ObjectBase::setObjectCenter( ( max_obj + min_obj ) * 0.5f );
    }
}

/*==========================================================================*/
/**
 *  @breif  Returns the control target object.
 *  @return pointer to the control target object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::get_control_target()
{
    if ( m_has_active_object )
    {
        return *m_active_object;
    }
    else
    {
        return this;
    }
}

/*==========================================================================*/
/**
 *  @brief  Returns the rotation center.
 *  @param  object [in] pointer to the object
 *  @return rotation center
 */
/*==========================================================================*/
kvs::Vec3 ObjectManager::get_rotation_center( kvs::ObjectBase* object )
{
    if ( this->isEnableAllMove() )
    {
        return this->kvs::ObjectBase::xform().translation();
    }
    else
    {
        const kvs::Vec3 center = ObjectBase::objectCenter();
        const kvs::Vec3 scale = ObjectBase::normalize();
        return object->positionInWorld( center, scale );
    }
}

/*==========================================================================*/
/**
 *  @breif  Returns the pointer to the first object in the object manager.
 *  @return pointer to the top object
 */
/*==========================================================================*/
ObjectManager::ObjectIterator ObjectManager::get_control_first_pointer()
{
    if ( m_has_active_object )
    {
        return m_object_tree.begin( m_active_object );
    }
    else
    {
        ObjectIterator object = m_object_tree.begin();
        ++object; // Skip the root object.
        return object;
    }
}

/*==========================================================================*/
/**
 *  @brief  Returns the pointer to the last object in the object manager.
 *  @return pointer to the last object in the object manager
 */
/*==========================================================================*/
ObjectManager::ObjectIterator ObjectManager::get_control_last_pointer()
{
    if ( m_has_active_object )
    {
        return m_object_tree.end( m_active_object );
    }
    else
    {
        return m_object_tree.end();
    }
}

} // end of namespace kvs
