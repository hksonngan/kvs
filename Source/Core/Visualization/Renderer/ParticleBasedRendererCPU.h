/****************************************************************************/
/**
 *  @file   ParticleVolumeRendererCPU.h
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id: ParticleVolumeRenderer.h 1418 2013-02-21 07:02:46Z naohisa.sakamoto@gmail.com $
 */
/****************************************************************************/
#ifndef KVS__CPU__PARTICLE_BASED_RENDERER_H_INCLUDE
#define KVS__CPU__PARTICLE_BASED_RENDERER_H_INCLUDE

#include <kvs/VolumeRendererBase>
#include <kvs/ParticleBuffer>
#include <kvs/Module>


namespace kvs
{

namespace cpu
{

/*==========================================================================*/
/**
 *  Particle based volume renderer.
 */
/*==========================================================================*/
class ParticleVolumeRenderer : public kvs::VolumeRendererBase
{
    kvsModuleName( kvs::cpu::ParticleVolumeRenderer );
    kvsModuleCategory( Renderer );
    kvsModuleBaseClass( kvs::VolumeRendererBase );

public:

    friend class ParticleBufferCompositor;

protected:

    bool m_enable_rendering; ///< rendering flag
    size_t m_subpixel_level; ///< number of divisions in a pixel
    kvs::ParticleBuffer* m_buffer; ///< particle buffer

    // Reference data (NOTE: not allocated in thie class).
    const kvs::PointObject* m_ref_point; ///< pointer to the point data

public:

    ParticleVolumeRenderer();
    ParticleVolumeRenderer( const kvs::PointObject* point, const size_t subpixel_level = 1 );
    virtual ~ParticleVolumeRenderer();

    void exec( kvs::ObjectBase* object, kvs::Camera* camera, kvs::Light* light );

    void attachPointObject( const kvs::PointObject* point );
    void setSubpixelLevel( const size_t subpixel_level );

    void initialize();
    const kvs::ParticleBuffer* particleBuffer() const;
    size_t subpixelLevel() const;

    void enableRendering();
    void disableRendering();

protected:

    bool create_particle_buffer( const size_t width, const size_t height, const size_t subpixel_level );
    void clean_particle_buffer();
    void delete_particle_buffer();
    void create_image( const kvs::PointObject* point, const kvs::Camera* camera, const kvs::Light* light );
    void project_particle( const kvs::PointObject* point, const kvs::Camera* camera, const kvs::Light* light );
};

} // end of namespace cpu

} // end of namespace kvs

#endif // KVS__CPU__PARTICLE_BASED_RENDERER_H_INCLUDE
