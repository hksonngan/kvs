/****************************************************************************/
/**
 *  @file   RendererBase.h
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
#ifndef KVS__RENDERER_BASE_H_INCLUDE
#define KVS__RENDERER_BASE_H_INCLUDE

#include <string>
#include <kvs/Timer>
#include <kvs/Module>
#include <kvs/Deprecated>


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
    kvsModuleName( kvs::RendererBase );
    kvsModuleBase;

private:

    std::string m_name; ///< renderer name
    kvs::Timer m_timer; ///< timer
    mutable bool m_shading_flag; ///< shading flag

public:

    RendererBase();
    virtual ~RendererBase();

    void setName( const std::string& name );
    const std::string& name() const;
    const kvs::Timer& timer() const;
    bool isShading() const;
    void enableShading() const;
    void disableShading() const;

    virtual void exec( kvs::ObjectBase* object, kvs::Camera* camera = NULL, kvs::Light* light  = NULL ) = 0;

protected:

    void startTimer();
    void stopTimer();

protected:

    KVS_DEPRECATED( kvs::Timer& timer() ) { return m_timer; }
    KVS_DEPRECATED( void initialize() ) { initialize_projection(); initialize_modelview(); }
    KVS_DEPRECATED( virtual void initialize_projection() ) {}
    KVS_DEPRECATED( virtual void initialize_modelview() ) {}
};


} // end of namespace kvs

#endif // KVS__RENDERER_BASE_H_INCLUDE
