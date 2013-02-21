/****************************************************************************/
/**
 *  @file   PolygonRenderer.h
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
#ifndef KVS__POLYGON_RENDERER_H_INCLUDE
#define KVS__POLYGON_RENDERER_H_INCLUDE

#include <kvs/RendererBase>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Polygon renderer.
 */
/*==========================================================================*/
class PolygonRenderer : public kvs::RendererBase
{
    kvsModuleName( kvs::PolygonRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::RendererBase );

protected:

    mutable bool m_enable_anti_aliasing; ///< flag for anti-aliasing (AA)
    mutable bool m_enable_multisample_anti_aliasing; ///< flag for multisample anti-aliasing (MSAA)
    mutable bool m_enable_two_side_lighting; ///< flag for two-side lighting

public:

    PolygonRenderer();
    virtual ~PolygonRenderer();

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void enableAntiAliasing( const bool multisample = false ) const;
    void disableAntiAliasing() const;
    void enableTwoSideLighting() const;
    void disableTwoSideLighting() const;
    bool isTwoSideLighting() const;

protected:

    virtual void initialize_projection();
    virtual void initialize_modelview();
};

} // end of namespace kvs

#endif // KVS__POLYGON_RENDERER_H_INCLUDE
