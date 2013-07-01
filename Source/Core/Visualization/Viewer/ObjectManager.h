/****************************************************************************/
/**
 *  @file   ObjectManager.h
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
#ifndef KVS__OBJECT_MANAGER_H_INCLUDE
#define KVS__OBJECT_MANAGER_H_INCLUDE

#include <string>
#include <map>
#include <kvs/ObjectBase>
#include <kvs/Tree>
#include <kvs/Deprecated>


namespace kvs
{

/*==========================================================================*/
/**
*  Object manager class.
*/
/*==========================================================================*/
class ObjectManager : public kvs::ObjectBase
{
public:
    typedef kvs::Tree<kvs::ObjectBase*> ObjectTree;
    typedef ObjectTree::iterator ObjectIterator;
    typedef std::pair<int,ObjectIterator> ObjectPair;
    typedef std::map<int,ObjectIterator> ObjectMap;

private:
    bool m_has_active_object; ///< If active object exists true.
    bool m_enable_all_move; ///< If All object move together true.
    ObjectIterator m_root; ///< pointer to the root of the tree
    ObjectIterator m_active_object; ///< pointer to the active object
    ObjectMap m_object_map; ///< object map
    int m_current_object_id; ///< current object ID
    ObjectTree m_object_tree; ///< object tree

public:

    ObjectManager();
    virtual ~ObjectManager();

    ObjectType objectType() const;
    int insert( kvs::ObjectBase* obj );
    int insert( int parent_id, kvs::ObjectBase* obj );
    void erase( bool delete_flg = true );
    void erase( int obj_id, bool delete_flg = true );
    void erase( std::string obj_name, bool delete_flg = true );
    void change( int obj_id, kvs::ObjectBase* obj, bool delete_flg = true );
    void change( std::string obj_name, kvs::ObjectBase* obj, bool delete_flg = true );
    int numberOfObjects() const;
    kvs::ObjectBase* object();
    kvs::ObjectBase* object( int obj_id );
    kvs::ObjectBase* object( std::string obj_name );
    bool hasObject() const;
    void resetXform();
    void resetXform( int obj_id );
    kvs::Xform xform() const;
    kvs::Xform xform( int obj_id ) const;
    int objectID( const kvs::ObjectBase *object ) const;
    int parentObjectID( const ObjectIterator it ) const;
    int parentObjectID( const kvs::ObjectBase *object ) const;
    int parentObjectID( int object_id ) const;
    int activeObjectID() const;
    bool setActiveObjectID( int obj_id );
    kvs::ObjectBase* activeObject();

    void resetActiveObjectXform();
    void eraseActiveObject();

    void enableAllMove();
    void disableAllMove();
    bool isEnableAllMove() const;
    bool hasActiveObject() const;
    void releaseActiveObject();
    bool detectCollision( const kvs::Vector2f& p_win, kvs::Camera* camera );
    bool detectCollision( const kvs::Vector3f& p_world );

    kvs::Vector2f positionInDevice( kvs::Camera* camera ) const;
    void rotate( const kvs::Matrix33f& rotation );
    void translate( const kvs::Vector3f& translation );
    void scale( const kvs::Vector3f& scaling );
    void updateExternalCoords();

private:

    void insert_root();
    void update_normalize_parameters( const kvs::Vector3f& min_ext, const kvs::Vector3f& max_ext );
    void update_normalize_parameters();
    kvs::ObjectBase* get_control_target();
    kvs::Vector3f get_rotation_center( kvs::ObjectBase* obj );
    ObjectIterator get_control_first_pointer();
    ObjectIterator get_control_last_pointer();

private:
    ObjectManager( const ObjectManager& );
    ObjectManager& operator =( const ObjectManager& );

public:
    KVS_DEPRECATED( int nobjects() const ) { return numberOfObjects(); }
};

} // end of namespace kvs

#endif // KVS__OBJECT_MANAGER_H_INCLUDE
