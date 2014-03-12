/*****************************************************************************/
/**
 *  @file   Streamline.h
 *  @author Yukio Yasuhara, Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__STREAMLINE_H_INCLUDE
#define KVS__STREAMLINE_H_INCLUDE

#include <kvs/Module>
#include "StreamlineBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  Streamline class.
 */
/*===========================================================================*/
class Streamline : public kvs::StreamlineBase
{
    kvsModule( kvs::Streamline, Mapper );
    kvsModuleBaseClass( kvs::StreamlineBase );

public:

    Streamline();
    Streamline(
        const kvs::StructuredVolumeObject* volume,
        const kvs::PointObject* seed_points,
        const kvs::TransferFunction& transfer_function );
    virtual ~Streamline();

    BaseClass::SuperClass* exec( const kvs::ObjectBase* object );

protected:

    bool check_for_acceptance( const std::vector<kvs::Real32>& vertices );
    bool check_for_termination(
        const kvs::Vector3f& current_vertex,
        const kvs::Vector3f& direction,
        const size_t integration_times,
        const kvs::Vector3f& next_vertex );
    const kvs::Vector3f interpolate_vector( const kvs::Vector3f& vertex, const kvs::Vector3f& direction );
    const kvs::Vector3f calculate_vector( const kvs::Vector3f& vertex );
    const kvs::RGBColor calculate_color( const kvs::Vector3f& direction );
    void set_min_max_vector_length( const kvs::VolumeObjectBase* volume );
};

} // end of namespace kvs

#endif // KVS__STREAMLINE_BASE_H_INCLUDE
