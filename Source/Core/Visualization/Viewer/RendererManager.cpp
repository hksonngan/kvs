/****************************************************************************/
/**
 *  @file RendererManager.cpp
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
#include "RendererManager.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Constructor.
 */
/*==========================================================================*/
RendererManager::RendererManager( void )
{
    renderer_manager_base::clear();
    m_renderer_ptr_map.clear();
}

/*==========================================================================*/
/**
 *  Destructor.
 */
/*==========================================================================*/
RendererManager::~RendererManager( void )
{
    this->erase();
}

/*==========================================================================*/
/**
 *  Insert the renderer.
 *  @param renderer [in] pointer to the renderer
 *  @return renderer ID
 */
/*==========================================================================*/
int RendererManager::insert( kvs::RendererBase* renderer )
{
    static int ren_id = 0;
    ren_id++;

    m_renderer_ptr_map[ren_id] =
        renderer_manager_base::insert( this->end(), renderer );

    return( ren_id );
}

/*==========================================================================*/
/**
 *  Erase the renderer.
 *  @param delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::erase( bool delete_flg )
{
    if( delete_flg )
    {
        for( renderer_ptr p = begin(); p != end(); p++ )
        {
            if( *p ){ delete( *p ); *p = NULL; }
        }
    }

    renderer_manager_base::clear();
    m_renderer_ptr_map.clear();
}

/*==========================================================================*/
/**
 *  Erase the renderer which is specified by the given ID.
 *  @param renderer_id [in] renderer ID
 *  @param delete_flg [in] deleting the allocated memory flag
 */
/*==========================================================================*/
void RendererManager::erase( int renderer_id, bool delete_flg )
{
    renderer_ptr_map::iterator map_id = m_renderer_ptr_map.find(renderer_id);
    if( map_id == m_renderer_ptr_map.end() ) return;

    renderer_ptr ren_ptr = map_id->second; // pointer to the renderer
    kvs::RendererBase* ren = *ren_ptr;     // renderer

    if( delete_flg )
    {
        if( ren )
        {
            delete( ren );
            ren = NULL;
        }
    }

    // Erase the renderer in the renderer master.
    renderer_manager_base::erase( ren_ptr );

    // Erase the map component, which is specified by map_id,
    // in m_renderer_ptr_map.
    m_renderer_ptr_map.erase( map_id );
}

/*==========================================================================*/
/**
 *  Get the number of the stored renderers.
 *  @return number of the stored renderers
 */
/*==========================================================================*/
const int RendererManager::nrenderers( void ) const
{
    return( size() );
}

/*==========================================================================*/
/**
 *  Get the renderer.
 *  @return pointer to the renderer
 */
/*==========================================================================*/
kvs::RendererBase* RendererManager::renderer( void )
{
    // Pointer to the renderer.
    renderer_ptr ren_ptr = begin();

    if( !*ren_ptr ) return( NULL );
    else            return( *ren_ptr );
}

/*==========================================================================*/
/**
 *  Get the renderer which is specified by the given ID.
 *  @param renderer_id [in] renderer ID
 *  @return pointer to the renderer
 */
/*==========================================================================*/
kvs::RendererBase* RendererManager::renderer( int renderer_id )
{
    renderer_ptr_map::iterator map_id = m_renderer_ptr_map.find(renderer_id);
    if( map_id == m_renderer_ptr_map.end() )   return( NULL );

    // Pointer to the renderer.
    renderer_ptr ren_ptr = map_id->second;

    return( *ren_ptr );
}

/*==========================================================================*/
/**
 *  Test whether the renderer manager has renderers.
 *  @return true, if the renderer manager has renderers.
 */
/*==========================================================================*/
const bool RendererManager::hasRenderer( void ) const
{
    return( renderer_manager_base::size() != 0 );
}

}

