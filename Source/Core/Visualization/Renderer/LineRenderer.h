/****************************************************************************/
/**
 *  @file LineRenderer.h
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
#ifndef KVS_CORE_LINE_RENDERER_H_INCLUDE
#define KVS_CORE_LINE_RENDERER_H_INCLUDE

#include "RendererBase.h"
#include <kvs/ClassName>
#include <kvs/Module>


namespace kvs
{

class ObjectBase;
class Camera;
class Light;

/*==========================================================================*/
/**
 *  Line renderer.
 */
/*==========================================================================*/
class LineRenderer : public kvs::RendererBase
{
    // Class name.
    kvsClassName( LineRenderer );

    // Module information.
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::RendererBase );

protected:

    bool m_enable_anti_aliasing;

public:

    LineRenderer( void );

    virtual ~LineRenderer( void );

public:

    void enableAntiAliasing( void );

    void disableAntiAliasing( void );

public:

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

protected:

    virtual void initialize_projection( void );

    virtual void initialize_modelview( void );
};

} // end of namespace kvs

#endif // KVS_CORE_LINE_RENDERER_H_INCLUDE
