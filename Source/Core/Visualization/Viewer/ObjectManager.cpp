/****************************************************************************/
/**
 *  @file ObjectManager.cpp
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
#include <iostream>
#include "ObjectManager.h"
#include "Camera.h"
#include <kvs/Math>
#include <kvs/Vector2>
#include <kvs/Vector3>
#include <kvs/Vector4>


namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructor.
 */
/*==========================================================================*/
ObjectManager::ObjectManager( void ) :
    kvs::ObjectBase( true )
{
    object_manager_base::clear();
    kvs::Xform::initialize();
    m_has_active_object = false;
    m_enable_all_move   = false;
    m_object_ptr_map.clear();

    m_current_object_id = 0;
    insert_root();

    m_min_object_coord   = kvs::Vector3f(  1000000,  1000000,  1000000 );
    m_max_object_coord   = kvs::Vector3f( -1000000, -1000000, -1000000 );
    m_min_external_coord = kvs::Vector3f( -3.0, -3.0, -3.0 );
    m_max_external_coord = kvs::Vector3f(  3.0,  3.0,  3.0 );
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
ObjectManager::~ObjectManager( void )
{
    this->erase();
    kvs::Xform::clear();
    m_object_ptr_map.clear();
}

/*==========================================================================*/
/**
 *  Insert the root of the objects.
 */
/*==========================================================================*/
void ObjectManager::insert_root( void )
{
    m_root_ptr = object_manager_base::insert( object_manager_base::begin(), this );
}

const kvs::ObjectBase::ObjectType ObjectManager::objectType( void ) const
{
    return( kvs::ObjectBase::ObjectManager );
}

/*==========================================================================*/
/**
 *  Insert a pointer to the object base to the object master.
 *  @param obj [in] pointer to the object base
 *  @return object ID
 */
/*==========================================================================*/
int ObjectManager::insert( kvs::ObjectBase* obj )
{
    obj->updateNormalizeParameters();
    update_normalize_parameters( obj->minExternalCoord(),
                                 obj->maxExternalCoord() );

    /* Calculate a object ID by counting the number of this method called.
     * Therefore, we define the object ID as static parameter in this method,
     * and count it.
     */
    m_current_object_id++;

    object_ptr obj_ptr = object_manager_base::appendChild( m_root_ptr, obj );

    /* A pair of the object ID and a pointer to the object is inserted to
     * the object map. The pointer to the object is got by inserting the
     * object to the object master base.
     */
    m_object_ptr_map.insert( object_ptr_pair( m_current_object_id, obj_ptr ) );

    return( m_current_object_id );
}

/*==========================================================================*/
/**
 *  Append a pointer to the object base to the object base specified by id.
 *  @param parent_id [in] id of the parent object
 *  @param obj [in] pointer to the object base
 *  @return object ID
 */
/*==========================================================================*/
int ObjectManager::insert( int parent_id, kvs::ObjectBase* obj )
{
    obj->updateNormalizeParameters();
    update_normalize_parameters( obj->minExternalCoord(), 
                                 obj->maxExternalCoord() );

    object_ptr_map::iterator map_id = m_object_ptr_map.find(parent_id);
    if( map_id == m_object_ptr_map.end() ) return( -1 );

    // Append the object.
    m_current_object_id++;

    object_ptr parent_ptr = map_id->second; // pointer to the parent
    object_ptr child_ptr  = object_manager_base::appendChild( parent_ptr, obj );

    m_object_ptr_map.insert( object_ptr_pair( m_current_object_id, child_ptr ) );

    return( m_current_object_id );
}

/*==========================================================================*/
/**
 *  Erase the all objects.
 *  @param delete_flg [in] deleting the allocated memory flag
 *
 *  Erase the all objects, which is registrated in the object master base.
 *  Simultaniously, the allocated memory region for the all objects is deleted.
 */
/*==========================================================================*/
void ObjectManager::erase( bool delete_flg )
{
    object_ptr first = object_manager_base::begin();
    object_ptr last  = object_manager_base::end();

    // Skip the root.
    ++first;

    if( delete_flg )
    {
        for( ; first != last; ++first )
        {
            if( *first )
            {
                delete( *first );
                *first = NULL;
            }
        }
    }

    object_manager_base::clear();
    m_object_ptr_map.clear();

    insert_root();

    update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  Erase the object by a specificated object ID.
 *  @param obj_id [in] object ID
 *  @param delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void ObjectManager::erase( int obj_id, bool delete_flg )
{
    /* Search the object which is specified by given object ID in the
     * object pointer map. If it isn't found, this method executes nothing.
     */
    object_ptr_map::iterator map_id = m_object_ptr_map.find(obj_id);
    if( map_id == m_object_ptr_map.end() ) return;

    // Delete the object.
    object_ptr ptr = map_id->second; // pointer to the object
    kvs::ObjectBase* obj = *ptr;     // object

    if( delete_flg )
    {
        if( obj )
        {
            delete( obj );
            obj = NULL;
        }
    }

    // Erase the object in the object master base.
    object_manager_base::erase( ptr );

    // Erase the map component, which is specified by map_id,
    // in m_obj_ptr_map.
    m_object_ptr_map.erase( map_id );

    update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  Change the object by a specificated object ID.
 *  @param obj_id [in] object ID stored in the object manager
 *  @param obj [in] pointer to the inserting object
 *  @param delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void ObjectManager::change( int obj_id, ObjectBase* obj, bool delete_flg )
{
    /* Search the object which is specified by given object ID in the
     * object pointer map. If it isn't found, this method executes nothing.
     */
    object_ptr_map::iterator map_id = m_object_ptr_map.find(obj_id);
    if( map_id == m_object_ptr_map.end() ) return;

    // Change the object.
    object_ptr ptr = map_id->second; // pointer to the object
    kvs::ObjectBase* old_obj = *ptr; // object

    // Save the Xform.
    kvs::Xform xform = old_obj->xform();

    // Erase the old object
    if( delete_flg )
    {
        if( old_obj )
        {
            delete( old_obj );
            old_obj = NULL;
        }
    }

    // Insert the new object
    obj->updateNormalizeParameters();
    obj->setXform( xform );

    *ptr = obj;

    update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  Get the number of the stored objects in the object manager.
 *  @return number of the stored objects
 */
/*==========================================================================*/
const int ObjectManager::nobjects( void ) const
{
    return( object_manager_base::size() );
}

/*==========================================================================*/
/**
 *  Get the pointer to the top object.
 *  @return pointer to the top object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::object( void )
{
    // pointer to the object
    object_ptr obj_ptr = object_manager_base::begin();

    // skip the root
    ++obj_ptr;

    if( !*obj_ptr ) return( NULL );
    else            return( *obj_ptr );
}

/*==========================================================================*/
/**
 *  Get the object by a specificated object ID.
 *  @param obj_id [in] object ID
 *  @return pointer to the object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::object( int obj_id )
{
    /* Search the object which is specified by given object ID in the
     * object pointer map. If it isn't found, this method executes nothing.
     */

    object_ptr_map::iterator map_id = m_object_ptr_map.find(obj_id);
    if( map_id == m_object_ptr_map.end() )  return( NULL );

    // pointer to the object
    object_ptr obj_ptr = map_id->second;

    return( *obj_ptr );
}

/*==========================================================================*/
/**
 *  Check including object in the object master.
 *  @return true, if some objects are included.
 */
/*==========================================================================*/
const bool ObjectManager::hasObject( void ) const
{
    return( object_manager_base::size() > 1 );
}

/*==========================================================================*/
/**
 *  Reset the xforms of the all objects.
 */
/*==========================================================================*/
void ObjectManager::resetXform( void )
{
    object_ptr first = object_manager_base::begin();
    object_ptr last  = object_manager_base::end();

    for( ; first != last; ++first )
    {
        (*first)->resetXform();
    }

    kvs::XformControl::resetXform();
}

/*==========================================================================*/
/**
 *  Reset the xform of the object which is specified by given ID.
 *  @param obj_id [in] object ID
 */
/*==========================================================================*/
void ObjectManager::resetXform( int obj_id )
{
    object_ptr_map::iterator map_id = m_object_ptr_map.find(obj_id);
    if( map_id == m_object_ptr_map.end() ) return;

    // pointer to the object
    object_ptr obj_ptr = map_id->second;

    object_ptr first = object_manager_base::begin( obj_ptr );
    object_ptr last  = object_manager_base::end( obj_ptr );

    const kvs::Xform obj_form = (*obj_ptr)->xform();
    const kvs::Xform trans = Xform(*this) * obj_form.inverse();

    (*obj_ptr)->setXform( Xform(*this) );

    for( ; first != last; ++first )
    {
        (*first)->setXform( trans * (*first)->xform() );
    }
}

/*==========================================================================*/
/**
 *  Get the xform of the object manager.
 */
/*==========================================================================*/
const kvs::Xform ObjectManager::xform( void ) const
{
    return( kvs::XformControl::xform() );
}

/*==========================================================================*/
/**
 *  Get the xform of the object which is specified by the given ID.
 *  @param obj_id [in] object ID
 */
/*==========================================================================*/
const kvs::Xform ObjectManager::xform( int obj_id ) const
{
    /* Search the object which is specified by given object ID in the
     * object pointer map. If it isn't found, this method retrun initial Xform.
     */
    object_ptr_map::const_iterator map_id = m_object_ptr_map.find(obj_id);
    if( map_id == m_object_ptr_map.end() )
    {
        Xform xform;
        return( xform );
    }

    // Delete the object.
    object_ptr obj_ptr = map_id->second; // pointer to the object
    kvs::ObjectBase* obj = *obj_ptr;     // object

    return( obj->xform() );
}

/*==========================================================================*/
/**
 *  Get the active object ID.
 *  @return active object ID, if active object is nothing, -1 is returned.
 */
/*==========================================================================*/
const int ObjectManager::activeObjectID( void ) const
{
    if( m_has_active_object )
    {
        for( object_ptr_map::const_iterator p = m_object_ptr_map.begin();
             p != m_object_ptr_map.end();
             p++ )
        {
            if( m_active_object_ptr == p->second ) return( p->first );
        }
    }

    return( -1 );
}

/*==========================================================================*/
/**
 *  Set the active object ID.
 *  @param obj_id [in] object ID
 *  @return true, if the object specified by the given ID is found.
 */
/*==========================================================================*/
bool ObjectManager::setActiveObjectID( int obj_id )
{
    object_ptr_map::iterator map_id = m_object_ptr_map.find(obj_id);
    if( map_id == m_object_ptr_map.end() )
    {
        return ( false );
    }

    m_active_object_ptr = map_id->second;
    m_has_active_object = true;

    return( true );
}

/*==========================================================================*/
/**
 *  Get the pointer to the active object.
 *  @return pointer to the active object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::activeObject( void )
{
    return( m_has_active_object ? *m_active_object_ptr : NULL );
}

/*==========================================================================*/
/**
 *  Release the xform of the active object.
 */
/*==========================================================================*/
void ObjectManager::resetActiveObjectXform( void )
{
    if( m_has_active_object )
    {
        (*m_active_object_ptr)->resetXform();
        (*m_active_object_ptr)->multiplyXform( kvs::Xform(*this) );
    }
}

/*==========================================================================*/
/**
 *  Erase the active object.
 */
/*==========================================================================*/
void ObjectManager::eraseActiveObject( void )
{
    if( m_has_active_object )
    {
        if( *m_active_object_ptr )
        {
            delete( *m_active_object_ptr );
            *m_active_object_ptr = NULL;
        }
        object_manager_base::erase( m_active_object_ptr );
    }

    update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  Enable to move all objects.
 */
/*==========================================================================*/
void ObjectManager::enableAllMove( void )
{
    m_enable_all_move = true;
}

/*==========================================================================*/
/**
 *  Disable to move all objects.
 */
/*==========================================================================*/
void ObjectManager::disableAllMove( void )
{
    m_enable_all_move = false;
}

/*==========================================================================*/
/**
 *  Test whether the object manager is able to move all objects or not.
 *  @return true, if the object manager is able to move all objects.
 */
/*==========================================================================*/
const bool ObjectManager::isEnableAllMove( void ) const
{
    return( m_enable_all_move );
}

/*==========================================================================*/
/**
 *  Test whether the object manager has the active object.
 *  @return true, if the object manager has the active object.
 */
/*==========================================================================*/
const bool ObjectManager::hasActiveObject( void ) const
{
    return( m_has_active_object );
}

/*==========================================================================*/
/**
 *  Release the active object.
 */
/*==========================================================================*/
void ObjectManager::releaseActiveObject( void )
{
    m_has_active_object = false;
}

/*==========================================================================*/
/**
 *  Test the collision detection.
 *  @param p_win [in] point in the window coordinate
 *  @param camera [in] pointer to the camera
 *  @return true, if the collision is detected.
 */
/*==========================================================================*/
bool ObjectManager::detectCollision(
    const kvs::Vector2f& p_win,
    kvs::Camera*         camera )
{
    double min_distance = 100000;

    object_ptr first = object_manager_base::begin();
    object_ptr last  = object_manager_base::end();

    // skip the root
    ++first;

    for( ; first != last; ++first )
    {
        if( !(*first)->canCollision() ) continue;

        const kvs::Vector2f diff =
            (*first)->positionInDevice( camera, m_object_center, m_normalize ) - p_win;

        const double distance = diff.length();

        if( distance < min_distance )
        {
            min_distance        = distance;
            m_active_object_ptr = first;
        }
    }

    return( m_has_active_object =
            (*m_active_object_ptr)->collision( p_win, camera,
                                               m_object_center,
                                               m_normalize ) );
}

/*==========================================================================*/
/**
 *  Test the collision detection.
 *  @param p_world [in] point in the world coordinate
 *  @return true, if the collision is detected.
 */
/*==========================================================================*/
bool ObjectManager::detectCollision( const kvs::Vector3f& p_world )
{
    double min_distance = 100000;

    object_ptr first = object_manager_base::begin();
    object_ptr last  = object_manager_base::end();

    // skip the root
    ++first;

    for( ; first != last; ++first )
    {
        if( !(*first)->canCollision() ) continue;

        const kvs::Vector3f diff =
            (*first)->positionInWorld( m_object_center, m_normalize ) - p_world;

        const double distance = diff.length();

        if( distance < min_distance )
        {
            min_distance        = distance;
            m_active_object_ptr = first;
        }
    }

    return( m_has_active_object =
            (*m_active_object_ptr)->collision( p_world,
                                               m_object_center,
                                               m_normalize ) );
}

/*==========================================================================*/
/**
 *  Get the object manager position in the device coordinate.
 *  @param camera [in] pointer to the camera
 */
/*==========================================================================*/
const kvs::Vector2f ObjectManager::positionInDevice( kvs::Camera* camera ) const
{
    kvs::Vector2f ret;
    glPushMatrix();
    {
        camera->update();

        ret     = camera->projectObjectToWindow( kvs::Xform::translation() );
        ret.y() = camera->windowHeight() - ret.y();
    }
    glPopMatrix();

    return( ret );
}

/*==========================================================================*/
/**
 *  Rotate the all objects.
 *  @param rotation [in] current rotation matrix.
 */
/*==========================================================================*/
void ObjectManager::rotate( const kvs::Matrix33f& rotation )
{
    kvs::ObjectBase* object = get_control_target();
    kvs::Vector3f center = get_rotation_center( object );

    object->rotate( rotation, center );

    object_ptr first = get_control_first_pointer();
    object_ptr last  = get_control_last_pointer();

    for( ; first != last; ++first )
    {
        (*first)->rotate( rotation, center );
    }
}

/*==========================================================================*/
/**
 *  Translate the all objects.
 *  @param translation [in] current translation vector
 */
/*==========================================================================*/
void ObjectManager::translate( const kvs::Vector3f& translation )
{
    kvs::ObjectBase* object = get_control_target();

    object->kvs::XformControl::translate( translation );

    object_ptr first = get_control_first_pointer();
    object_ptr last  = get_control_last_pointer();

    for( ; first != last; ++first )
    {
        (*first)->translate( translation );
    }
}

/*==========================================================================*/
/**
 *  Scaling the all objects.
 *  @param scaling [in] current scaling value.
 */
/*==========================================================================*/
void ObjectManager::scale( const kvs::Vector3f& scaling )
{
    kvs::ObjectBase* object = get_control_target();

    kvs::Vector3f center = get_rotation_center( object );

    object->scale( scaling, center );

    object_ptr first = get_control_first_pointer();
    object_ptr last  = get_control_last_pointer();

    for( ; first != last; ++first )
    {
        (*first)->scale( scaling, center );
    }
}

/*==========================================================================*/
/**
 *  Update the external coordinate.
 */
/*==========================================================================*/
void ObjectManager::updateExternalCoords( void )
{
    update_normalize_parameters();
}

/*==========================================================================*/
/**
 *  Update the normalize parameters.
 *  @param min_ext [in] min. external coordinate value
 *  @param max_ext [in] max. external coordinate value
 */
/*==========================================================================*/
void ObjectManager::update_normalize_parameters(
    const kvs::Vector3f& min_ext,
    const kvs::Vector3f& max_ext )
{
    if( kvs::Math::Equal( 0.0f, min_ext.x() ) &&
        kvs::Math::Equal( 0.0f, min_ext.y() ) &&
        kvs::Math::Equal( 0.0f, min_ext.z() ) &&
        kvs::Math::Equal( 0.0f, max_ext.x() ) &&
        kvs::Math::Equal( 0.0f, max_ext.y() ) &&
        kvs::Math::Equal( 0.0f, max_ext.z() ) ) return;

    m_min_object_coord.x() = m_min_object_coord.x() < min_ext.x() ?
        m_min_object_coord.x() : min_ext.x();
    m_min_object_coord.y() = m_min_object_coord.y() < min_ext.y() ?
        m_min_object_coord.y() : min_ext.y();
    m_min_object_coord.z() = m_min_object_coord.z() < min_ext.z() ?
        m_min_object_coord.z() : min_ext.z();
    m_max_object_coord.x() = m_max_object_coord.x() > max_ext.x() ?
        m_max_object_coord.x() : max_ext.x();
    m_max_object_coord.y() = m_max_object_coord.y() > max_ext.y() ?
        m_max_object_coord.y() : max_ext.y();
    m_max_object_coord.z() = m_max_object_coord.z() > max_ext.z() ?
        m_max_object_coord.z() : max_ext.z();

    const kvs::Vector3f diff_obj = m_max_object_coord - m_min_object_coord;
    const float max_diff = kvs::Math::Max( diff_obj.x(), diff_obj.y(), diff_obj.z() );
    const float normalize = 6.0f / max_diff;

    m_normalize.x() = normalize;
    m_normalize.y() = normalize;
    m_normalize.z() = normalize;

    m_object_center = ( m_max_object_coord + m_min_object_coord ) * 0.5f;
}

/*==========================================================================*/
/**
 *  Update normalize parameters.
 */
/*==========================================================================*/
void ObjectManager::update_normalize_parameters( void )
{
    m_min_object_coord   = kvs::Vector3f(  1000000,  1000000,  1000000 );
    m_max_object_coord   = kvs::Vector3f( -1000000, -1000000, -1000000 );
    m_min_external_coord = kvs::Vector3f( -3.0, -3.0, -3.0 );
    m_max_external_coord = kvs::Vector3f(  3.0,  3.0,  3.0 );

    int ctr = 0;
    if( object_manager_base::size() > 1 )
    {
        object_ptr first = object_manager_base::begin();
        object_ptr last  = object_manager_base::end();

        // skip the root
        ++first;

        for( ; first != last; ++first )
        {
            if( kvs::Math::Equal( 0.0f, (*first)->minExternalCoord().x() ) &&
                kvs::Math::Equal( 0.0f, (*first)->minExternalCoord().y() ) &&
                kvs::Math::Equal( 0.0f, (*first)->minExternalCoord().z() ) &&
                kvs::Math::Equal( 0.0f, (*first)->maxExternalCoord().x() ) &&
                kvs::Math::Equal( 0.0f, (*first)->maxExternalCoord().y() ) &&
                kvs::Math::Equal( 0.0f, (*first)->maxExternalCoord().z() ) ) continue;

            m_min_object_coord.x() =
                m_min_object_coord.x() < (*first)->minExternalCoord().x() ?
                m_min_object_coord.x() : (*first)->minExternalCoord().x();
            m_min_object_coord.y() =
                m_min_object_coord.y() < (*first)->minExternalCoord().y() ?
                m_min_object_coord.y() : (*first)->minExternalCoord().y();
            m_min_object_coord.z() =
                m_min_object_coord.z() < (*first)->minExternalCoord().z() ?
                m_min_object_coord.z() : (*first)->minExternalCoord().z();
            m_max_object_coord.x() =
                m_max_object_coord.x() > (*first)->maxExternalCoord().x() ?
                m_max_object_coord.x() : (*first)->maxExternalCoord().x();
            m_max_object_coord.y() =
                m_max_object_coord.y() > (*first)->maxExternalCoord().y() ?
                m_max_object_coord.y() : (*first)->maxExternalCoord().y();
            m_max_object_coord.z() =
                m_max_object_coord.z() > (*first)->maxExternalCoord().z() ?
                m_max_object_coord.z() : (*first)->maxExternalCoord().z();

            ctr++;
        }
    }

    if( ctr == 0 )
    {
        m_normalize     = kvs::Vector3f( 1.0 );
        m_object_center = kvs::Vector3f( 0.0 );
    }
    else
    {
        const kvs::Vector3f diff_obj = m_max_object_coord - m_min_object_coord;

        const float max_diff = kvs::Math::Max( diff_obj.x(), diff_obj.y(), diff_obj.z() );

        const float normalize = 6.0f / max_diff;

        m_normalize.x() = normalize;
        m_normalize.y() = normalize;
        m_normalize.z() = normalize;

        m_object_center = ( m_max_object_coord + m_min_object_coord ) * 0.5f;
    }
}

/*==========================================================================*/
/**
 *  Get the control target object.
 *  @return pointer to the control target object
 */
/*==========================================================================*/
kvs::ObjectBase* ObjectManager::get_control_target( void )
{
    if( isEnableAllMove() )
    {
        return( this );
    }
    else
    {
        return( *m_active_object_ptr );
    }
}

/*==========================================================================*/
/**
 *  Get the rotation center.
 *  @param obj [in] pointer to the object
 *  @return rotation center
 */
/*==========================================================================*/
kvs::Vector3f ObjectManager::get_rotation_center( kvs::ObjectBase* obj )
{
    if( isEnableAllMove() )
    {
        return( kvs::Vector3f( (*this)[0][3], (*this)[1][3], (*this)[2][3] ) );
    }
    else
    {
        return( obj->positionInWorld( m_object_center, m_normalize ) );
    }
}

/*==========================================================================*/
/**
 *  Get the pointer to the first object in the object manager.
 *  @return pointer to the top object
 */
/*==========================================================================*/
object_ptr ObjectManager::get_control_first_pointer( void )
{
    object_ptr first;

    if( isEnableAllMove() )
    {
        first = object_manager_base::begin();
        ++first;
    }
    else
    {
        first = object_manager_base::begin( m_active_object_ptr );
    }

    return( first );
}

/*==========================================================================*/
/**
 *  Get the pointer to the last object in the object manager.
 *  @return 
 */
/*==========================================================================*/
object_ptr ObjectManager::get_control_last_pointer( void )
{
    object_ptr last;

    if( isEnableAllMove() )
    {
        last = object_manager_base::end();
    }
    else
    {
        last = object_manager_base::end( m_active_object_ptr );
    }

    return( last );
}

} // end of namespace kvs
