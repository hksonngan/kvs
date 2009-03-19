/****************************************************************************/
/**
 *  @file HitAndMissSampling.h
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
#ifndef KVS_CORE_HIT_AND_MISS_SAMPLING_H_INCLUDE
#define KVS_CORE_HIT_AND_MISS_SAMPLING_H_INCLUDE

#include <kvs/PointObject>
#include <kvs/VolumeObjectBase>
#include <kvs/StructuredVolumeObject>
#include <kvs/UnstructuredVolumeObject>
#include <kvs/MapperBase>
#include <kvs/ClassName>
#include <kvs/Module>


namespace kvs
{

/*==========================================================================*/
/**
 *  Hit and Miss sampling class.
 */
/*==========================================================================*/
class HitAndMissSampling : public kvs::MapperBase, public kvs::PointObject
{
    // Class name.
    kvsClassName( HitAndMissSampling );

    // Module information.
    kvsModuleCategory( Mapper );
    kvsModuleBaseClass( kvs::MapperBase );
    kvsModuleSuperClass( kvs::PointObject );

public:

    HitAndMissSampling( void );

    HitAndMissSampling(
        const kvs::VolumeObjectBase* volume );

    HitAndMissSampling(
        const kvs::VolumeObjectBase* object,
        const kvs::TransferFunction& transfer_function );

    virtual ~HitAndMissSampling( void );

public:

    kvs::ObjectBase* exec( const kvs::ObjectBase* object );

private:

    void mapping( const kvs::StructuredVolumeObject* volume );

    void mapping( const kvs::UnstructuredVolumeObject* volume );

//    void set_min_max_coords( void );

    template <typename T>
    void generate_particles( const kvs::StructuredVolumeObject* volume );

    template <typename T>
    void generate_particles( const kvs::UnstructuredVolumeObject* volume );
};

} // end of namespace kvs

#endif // KVS_CORE_HIT_AND_MISS_SAMPLING_H_INCLUDE
