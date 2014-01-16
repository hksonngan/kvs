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
private:
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
    int insert( kvs::ObjectBase* object );
    int insert( int id, kvs::ObjectBase* object );
    void erase( bool delete_flag = true );
    void erase( int id, bool delete_flag = true );
    void erase( std::string name, bool delete_flag = true );
    void change( int id, kvs::ObjectBase* object, bool delete_flag = true );
    void change( std::string name, kvs::ObjectBase* object, bool delete_flag = true );
    kvs::ObjectBase* object();
    kvs::ObjectBase* object( int id );
    kvs::ObjectBase* object( std::string name );

    int numberOfObjects() const;
    bool hasObject() const;
    int objectID( const kvs::ObjectBase *object ) const;
    int parentObjectID( const ObjectIterator it ) const;
    int parentObjectID( const kvs::ObjectBase *object ) const;
    int parentObjectID( int id ) const;

    kvs::Xform xform() const;
    kvs::Xform xform( int id ) const;
    void resetXform();
    void resetXform( int id );

    kvs::ObjectBase* activeObject();
    int activeObjectID() const;
    bool hasActiveObject() const;
    bool setActiveObject( int id );
    void resetActiveObjectXform();
    void eraseActiveObject();
    void releaseActiveObject();

    void enableAllMove();
    void disableAllMove();
    bool isEnableAllMove() const;
    bool detectCollision( const kvs::Vec2& p_win, kvs::Camera* camera );
    bool detectCollision( const kvs::Vec3& p_world );

    kvs::Vec2 positionInDevice( kvs::Camera* camera ) const;
    void rotate( const kvs::Mat3& rotation );
    void translate( const kvs::Vec3& translation );
    void scale( const kvs::Vec3& scaling );
    void updateExternalCoords();

private:

    void insert_root();
    void update_normalize_parameters( const kvs::Vec3& min_ext, const kvs::Vec3& max_ext );
    void update_normalize_parameters();
    kvs::ObjectBase* get_control_target();
    kvs::Vec3 get_rotation_center( kvs::ObjectBase* object );
    ObjectIterator get_control_first_pointer();
    ObjectIterator get_control_last_pointer();

private:
    ObjectManager( const ObjectManager& );
    ObjectManager& operator =( const ObjectManager& );

public:
    KVS_DEPRECATED( int nobjects() const ) { return numberOfObjects(); }
    KVS_DEPRECATED( bool setActiveObjectID( int id ) ) { return setActiveObject( id ); }
};

} // end of namespace kvs

#endif // KVS__OBJECT_MANAGER_H_INCLUDE
