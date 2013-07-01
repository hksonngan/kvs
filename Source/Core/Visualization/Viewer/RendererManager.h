/****************************************************************************/
/**
 *  @file RendererManager.h
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
#ifndef KVS__RENDERER_MANAGER_H_INCLUDE
#define KVS__RENDERER_MANAGER_H_INCLUDE

#include <string>
#include <utility>
#include <vector>
#include <kvs/SharedPointer>
#include <kvs/Deprecated>


namespace kvs
{

class RendererBase;

/*==========================================================================*/
/**
*  Renderer manager class.
*/
/*==========================================================================*/
class RendererManager
{
private:
    typedef kvs::SharedPointer<kvs::RendererBase>    RendererSP;
    typedef std::vector<std::pair<int, RendererSP> > RendererList;
    typedef RendererList::iterator                   Iterator;

private:
    RendererList m_renderer_list;
    int m_renderer_id;

public:
    RendererManager();
    virtual ~RendererManager();

    int insert( kvs::RendererBase* renderer );
    void erase( bool delete_flg );
    void erase( int renderer_id, bool delete_flg );
    void erase( const std::string& renderer_name, bool delete_flg );
    void change( int renderer_id, kvs::RendererBase* renderer, bool delete_flg );
    void change( const std::string& renderer_name, kvs::RendererBase* renderer, bool delete_flg );
    kvs::RendererBase* renderer();
    kvs::RendererBase* renderer( int renderer_id );
    kvs::RendererBase* renderer( const std::string& renderer_name );

    int insert( const kvs::SharedPointer<kvs::RendererBase>& renderer );
    void erase();
    void erase( int renderer_id );
    void erase( const std::string& renderer_name );
    void change( int renderer_id, const kvs::SharedPointer<kvs::RendererBase>& renderer );
    void change( const std::string& renderer_name, const kvs::SharedPointer<kvs::RendererBase>& renderer );
    int numberOfRenderers() const;
    bool hasRenderer() const;

    //const kvs::SharedPointer<kvs::RendererBase>& renderer( int renderer_id );
    //const kvs::SharedPointer<kvs::RendererBase>& renderer( const std::string& renderer_name );

private:
    Iterator find_renderer( int id );
    Iterator find_renderer( const std::string& name );

private:
    RendererManager( const RendererManager& );
    RendererManager& operator =( const RendererManager& );

public:
    KVS_DEPRECATED( int nrenderers() const ) { return numberOfRenderers(); }
};

} // end of namespace kvs

#endif // KVS__RENDERER_MANAGER_H_INCLUDE
