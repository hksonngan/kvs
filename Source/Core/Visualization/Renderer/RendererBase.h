/****************************************************************************/
/**
 *  @file RendererBase.h
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
#ifndef KVS_CORE_RENDERER_BASE_H_INCLUDE
#define KVS_CORE_RENDERER_BASE_H_INCLUDE

#include <kvs/ClassName>
#include <kvs/Timer>
#include <kvs/Module>


namespace kvs
{

class ObjectBase;
class Camera;
class Light;

/*==========================================================================*/
/**
 *  Renderer base class.
 */
/*==========================================================================*/
class RendererBase
{
    kvsClassName( RendererBase );

    kvsModuleBase;

protected:

    kvs::Timer   m_timer;        ///< timer
    mutable bool m_shading_flag; ///< shading flag

public:

    RendererBase( void );

    virtual ~RendererBase( void );

public:

    const kvs::Timer& timer( void ) const;

protected:

    kvs::Timer& timer( void );

public:

    const bool isShading( void ) const;

    void enableShading( void ) const;

    void disableShading( void ) const;

public:

    void initialize( void );

    virtual void exec(
        kvs::ObjectBase* object,
        kvs::Camera*     camera = NULL,
        kvs::Light*      light  = NULL ) = 0;

protected:

    virtual void initialize_projection( void );

    virtual void initialize_modelview( void );
};


} // end of namespace kvs

#endif // KVS_CORE_RENDERER_BASE_H_INCLUDE
