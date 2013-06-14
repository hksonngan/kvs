/****************************************************************************/
/**
 *  @file IDManager.h
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
#ifndef KVS__ID_MANAGER_H_INCLUDE
#define KVS__ID_MANAGER_H_INCLUDE

#include <list>
#include <vector>
#include <utility>
#include <cstdlib>


namespace kvs
{

/*==========================================================================*/
/**
 *  ID manager class.
 */
/*==========================================================================*/
class IDManager
{
public:
    typedef std::pair<int,int> IDPair;
    typedef std::list<IDPair> IDs;
    typedef std::list<IDPair>::iterator ID_ptr;
    typedef std::list<IDPair>::reverse_iterator ID_rptr;

private:
    std::vector<int> m_flip_table;
    IDs m_id_list;

public:

    IDManager();
    virtual ~IDManager();

    IDPair operator [] ( size_t index ) const;

    size_t size() const;
    void insert( int object_id, int renderer_id );
    void insertObjectID( int object_id );
    void insertRendererID( int renderer_id );
    std::vector<int> objectID( int renderer_id ) const;
    int objectID() const;
    std::vector<int> rendererID( int object_id ) const;
    int rendererID() const;
    void erase();
    void erase( int object_id, int renderer_id );
    void eraseByObjectID( int object_id );
    void eraseByRendererID( int renderer_id );
    void changeObject( int object_id );
    void changeObject( int renderer_id, int object_id );
    void changeObject( const IDPair& id_pair, int object_id );
    void changeRenderer( int renderer_id );
    void changeRenderer( int object_id, int renderer_id );
    void changeRenderer( const IDPair& id_pair, int renderer_id );
    void flip();

private:

    void update_flip_table();

private:
    IDManager( const IDManager& );
    IDManager& operator =( const IDManager& );
};

} // end of namespace kvs

#endif // KVS__ID_MANAGER_H_INCLUDE