/****************************************************************************/
/**
 *  @file RendererManager.cpp
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
#include "RendererManager.h"
#include <kvs/RendererBase>


namespace
{

// for compatibility
class RendererDeleter
{
public:
    RendererDeleter()
    {
        m_auto_delete = true;
    }

    void operator ()( kvs::RendererBase* ren )
    {
        if ( m_auto_delete )
        {
            delete ren;
        }
    }

    void disableAutoDelete()
    {
        m_auto_delete = false;
    }

private:
    bool m_auto_delete;
};

void DisableDelete( const kvs::SharedPointer<kvs::RendererBase>& sp )
{
    // Disable deletion if the deleter type of sp is RendererDeleter.
    RendererDeleter* d = kvs::get_deleter<RendererDeleter>( sp );
    if ( d )
    {
        d->disableAutoDelete();
    }
}

}

namespace kvs
{

/*==========================================================================*/
/**
 *  @brief  Constructs a new RendererManager class.
 */
/*==========================================================================*/
RendererManager::RendererManager()
{
    m_renderer_id = 0;
}

/*==========================================================================*/
/**
 *  @brief  Destroys the RendererManager class.
 */
/*==========================================================================*/
RendererManager::~RendererManager()
{
}

/*==========================================================================*/
/**
 *  @brief  Insert the renderer.
 *  @param  renderer [in] pointer to the renderer
 *  @return renderer ID
 */
/*==========================================================================*/
int RendererManager::insert( kvs::RendererBase* renderer )
{
    return this->insert( RendererSP( renderer, ::RendererDeleter() ) );
}

/*==========================================================================*/
/**
 *  @brief  Erase the renderer.
 *  @param  delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::erase( bool delete_flg )
{
    if ( !delete_flg )
    {
        Iterator itr = m_renderer_list.begin();
        Iterator last = m_renderer_list.end();
        while ( itr != last )
        {
            ::DisableDelete( itr->second );
            ++itr;
        }
    }

    m_renderer_list.clear();
}

/*==========================================================================*/
/**
 *  @brief  Erase the renderer which is specified by the given ID.
 *  @param  renderer_id [in] renderer ID
 *  @param  delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::erase( int renderer_id, bool delete_flg )
{
    Iterator itr = this->find_renderer( renderer_id );
    if ( itr == m_renderer_list.end() ) return;

    if ( !delete_flg )
    {
        ::DisableDelete( itr->second );
    }

    m_renderer_list.erase( itr );
}

/*==========================================================================*/
/**
 *  @breif  Erase the renderer which is specified by the given name.
 *  @param  renderer_name [in] renderer name
 *  @param  delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::erase( const std::string& renderer_name, bool delete_flg )
{
    Iterator itr = this->find_renderer( renderer_name );
    if ( itr == m_renderer_list.end() ) return;

    if ( !delete_flg )
    {
        ::DisableDelete( itr->second );
    }

    m_renderer_list.erase( itr );
}

/*==========================================================================*/
/**
 *  @brief  Change the renderer by the specificated renderer ID.
 *  @param  renderer_id [in] renderer ID stored in the renderer manager
 *  @param  renderer [in] pointer to the inserting renderer
 *  @param  delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::change( int renderer_id, kvs::RendererBase* renderer, bool delete_flg )
{
    /* Search the object which is specified by given renderer ID in the
     * renderer pointer list. If it isn't found, this method executes nothing.
     */
    Iterator itr = this->find_renderer( renderer_id );
    if ( itr == m_renderer_list.end() ) return;

    if ( !delete_flg )
    {
        ::DisableDelete( itr->second );
    }

    // Change the renderer.
    itr->second = RendererSP( renderer, ::RendererDeleter() );
}

/*==========================================================================*/
/**
 *  @breif  Change the renderer by the specificated renderer name.
 *  @param  renderer_name [in] renderer name stored in the renderer manager
 *  @param  renderer [in] pointer to the inserting renderer
 *  @param  delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::change( const std::string& renderer_name, kvs::RendererBase* renderer, bool delete_flg )
{
    Iterator itr = this->find_renderer( renderer_name );
    if ( itr == m_renderer_list.end() ) return;

    if ( !delete_flg )
    {
        ::DisableDelete( itr->second );
    }

    // Change the renderer.
    itr->second = RendererSP( renderer, ::RendererDeleter() );
}

/*==========================================================================*/
/**
 *  @brief  Insert the renderer.
 *  @param  renderer [in] pointer to the renderer
 *  @return renderer ID
 */
/*==========================================================================*/
int RendererManager::insert( const kvs::SharedPointer<kvs::RendererBase>& renderer )
{
    ++m_renderer_id;
    m_renderer_list.push_back( std::make_pair( m_renderer_id, renderer ) );
    return m_renderer_id;
}

/*==========================================================================*/
/**
 *  @brief  Erase the renderer.
 */
/*==========================================================================*/
void RendererManager::erase()
{
    m_renderer_list.clear();
}

/*==========================================================================*/
/**
 *  @brief  Erase the renderer which is specified by the given ID.
 *  @param  renderer_id [in] renderer ID
 */
/*==========================================================================*/
void RendererManager::erase( int renderer_id )
{
    Iterator itr = this->find_renderer( renderer_id );
    if ( itr == m_renderer_list.end() ) return;

    m_renderer_list.erase( itr );
}

/*==========================================================================*/
/**
 *  @brief  Erase the renderer which is specified by the given name.
 *  @param  renderer_name [in] renderer name
 */
/*==========================================================================*/
void RendererManager::erase( const std::string& renderer_name )
{
    Iterator itr = this->find_renderer( renderer_name );
    if ( itr == m_renderer_list.end() ) return;

    m_renderer_list.erase( itr );
}

/*==========================================================================*/
/**
 *  @brief  Change the renderer by the specificated renderer ID.
 *  @param  renderer_id [in] renderer ID stored in the renderer manager
 *  @param  renderer [in] pointer to the inserting renderer
 */
/*==========================================================================*/
void RendererManager::change( int renderer_id, const kvs::SharedPointer<kvs::RendererBase>& renderer )
{
    /* Search the object which is specified by given renderer ID in the
     * renderer pointer list. If it isn't found, this method executes nothing.
     */
    Iterator itr = this->find_renderer( renderer_id );
    if ( itr == m_renderer_list.end() ) return;

    // Change the renderer.
    itr->second = renderer;
}

/*==========================================================================*/
/**
 *  @brief  Change the renderer by the specificated renderer name.
 *  @param  renderer_name [in] renderer name stored in the renderer manager
 *  @param  renderer [in] pointer to the inserting renderer
 */
/*==========================================================================*/
void RendererManager::change( const std::string& renderer_name, const kvs::SharedPointer<kvs::RendererBase>& renderer )
{
    Iterator itr = this->find_renderer( renderer_name );
    if ( itr == m_renderer_list.end() ) return;

    // Change the renderer.
    itr->second = renderer;
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of the stored renderers.
 *  @return number of the stored renderers
 */
/*==========================================================================*/
int RendererManager::nrenderers() const
{
    return this->numberOfRenderers();
}

/*==========================================================================*/
/**
 *  @brief  Returns the number of the stored renderers.
 *  @return number of the stored renderers
 */
/*==========================================================================*/
int RendererManager::numberOfRenderers() const
{
    return m_renderer_list.size();
}

/*==========================================================================*/
/**
 *  @brief  Returns the renderer.
 *  @return pointer to the renderer
 */
/*==========================================================================*/
kvs::RendererBase* RendererManager::renderer()
{
    return m_renderer_list.begin()->second.get();
}

/*==========================================================================*/
/**
 *  @breig  Returns the renderer which is specified by the given ID.
 *  @param  renderer_id [in] renderer ID
 *  @return pointer to the renderer
 */
/*==========================================================================*/
kvs::RendererBase* RendererManager::renderer( int renderer_id )
{
    Iterator itr = this->find_renderer( renderer_id );
    if ( itr != m_renderer_list.end() )
    {
        return itr->second.get();
    }
    return NULL;
}

/*==========================================================================*/
/**
 *  @brief  Returns the renderer which is specified by the given name.
 *  @param  renderer_name [in] renderer name
 *  @return pointer to the renderer
 */
/*==========================================================================*/
kvs::RendererBase* RendererManager::renderer( const std::string& renderer_name )
{
    Iterator itr = this->find_renderer( renderer_name );
    if ( itr != m_renderer_list.end() )
    {
        return itr->second.get();
    }
    return NULL;
}

/*===========================================================================*/
/**
 *  @brief  Returns the interator to the renderer specified by the ID.
 *  @param  id [in] renderer ID
 *  @return interotr of the renderer
 */
/*===========================================================================*/
RendererManager::Iterator RendererManager::find_renderer( int id )
{
    Iterator itr = m_renderer_list.begin();
    Iterator last = m_renderer_list.end();
    while ( itr != last )
    {
        if ( itr->first == id )
        {
            return itr;
        }
        ++itr;
    }
    return last;
}

/*===========================================================================*/
/**
 *  @brief  Returns the interator to the renderer specified by the name.
 *  @param  id [in] renderer ID
 *  @return interotr of the renderer
 */
/*===========================================================================*/
RendererManager::Iterator RendererManager::find_renderer( const std::string& name )
{
    Iterator itr = m_renderer_list.begin();
    Iterator last = m_renderer_list.end();
    while ( itr != last )
    {
        if ( itr->second->name() == name )
        {
            return itr;
        }
        ++itr;
    }
    return last;
}

/*==========================================================================*/
/**
 *  @brief  Test whether the renderer manager has renderers.
 *  @return true, if the renderer manager has renderers.
 */
/*==========================================================================*/
bool RendererManager::hasRenderer() const
{
    return m_renderer_list.size() != 0;
}

} // end of namespace kvs
