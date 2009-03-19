/****************************************************************************/
/**
 *  @file ObjectManager.h
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
#ifndef KVS_CORE_OBJECT_MANAGER_H_INCLUDE
#define KVS_CORE_OBJECT_MANAGER_H_INCLUDE

#include <map>
#include <kvs/ClassName>
#include <kvs/ObjectBase>
#include <kvs/Tree>


namespace kvs
{

typedef kvs::Tree<kvs::ObjectBase*>           object_manager_base;
typedef kvs::Tree<kvs::ObjectBase*>::iterator object_ptr;
typedef std::pair<int,object_ptr>             object_ptr_pair;
typedef std::map<int,object_ptr>              object_ptr_map;

const kvs::Vector3f CENTER_OF_OBJECT_MASTER( 0.0, 0.0, 0.0 );

/*==========================================================================*/
/**
*  Object manager class.
*/
/*==========================================================================*/
class ObjectManager : public object_manager_base, public kvs::ObjectBase
{
    kvsClassName( ObjectManager );

protected:

    bool           m_has_active_object; ///< If active object exists true.
    bool           m_enable_all_move;   ///< If All object move together true.
    object_ptr     m_root_ptr;          ///< pointer to root of tree
    object_ptr     m_active_object_ptr; ///< pointer to active object
    object_ptr_map m_object_ptr_map;    ///< object pointer map
    int            m_current_object_id; ///< current object ID

public:

    ObjectManager( void );

    virtual ~ObjectManager( void );

private:

    void insert_root( void );

public:

    const ObjectType objectType( void ) const;

    int insert( kvs::ObjectBase* obj );

    int insert( int parent_id, kvs::ObjectBase* obj );

    void erase( bool delete_flg = true );

    void erase( int obj_id, bool delete_flg = true );

    void change( int obj_id, kvs::ObjectBase* obj, bool delete_flg = true );

    const int nobjects( void ) const;

    kvs::ObjectBase* object( void );

    kvs::ObjectBase* object( int obj_id );

    const bool hasObject( void ) const;

    void resetXform( void );

    void resetXform( int obj_id );

    const kvs::Xform xform( void ) const;

    const kvs::Xform xform( int obj_id ) const;

    const int activeObjectID( void ) const;

    bool setActiveObjectID( int obj_id );

    kvs::ObjectBase* activeObject( void );

public:

    void resetActiveObjectXform( void );

    void eraseActiveObject( void );

public:

    void enableAllMove( void );

    void disableAllMove( void );

    const bool isEnableAllMove( void ) const;

    const bool hasActiveObject( void ) const;

    void releaseActiveObject( void );

    bool detectCollision( const kvs::Vector2f& p_win, kvs::Camera* camera );

    bool detectCollision( const kvs::Vector3f& p_world );

public:

    const kvs::Vector2f positionInDevice( kvs::Camera* camera ) const;

    void rotate( const kvs::Matrix33f& rotation );

    void translate( const kvs::Vector3f& translation );

    void scale( const kvs::Vector3f& scaling );

    void updateExternalCoords( void );

private:

    void update_normalize_parameters(
        const kvs::Vector3f& min_ext,
        const kvs::Vector3f& max_ext );

    void update_normalize_parameters( void );

    kvs::ObjectBase* get_control_target( void );

    kvs::Vector3f get_rotation_center( kvs::ObjectBase* obj );

    object_ptr get_control_first_pointer( void );

    object_ptr get_control_last_pointer( void );
};

} // end of namespace kvs

#endif // KVS_CORE_OBJECT_MANAGER_H_INCLUDE
