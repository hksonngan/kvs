/*****************************************************************************/
/**
 *  @file   StreamlineBase.h
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
/*****************************************************************************/
#ifndef KVS__STREAMLINE_BASE_H_INCLUDE
#define KVS__STREAMLINE_BASE_H_INCLUDE

#include <kvs/Module>
#include <kvs/MapperBase>
#include <kvs/LineObject>
#include <kvs/PointObject>
#include <kvs/StructuredVolumeObject>


namespace kvs
{

/*===========================================================================*/
/**
 *  Streamline class.
 */
/*===========================================================================*/
class StreamlineBase : public kvs::MapperBase, public kvs::LineObject
{
    kvsModule( kvs::StreamlineBase, Mapper );
    kvsModuleBaseClass( kvs::MapperBase );
    kvsModuleSuperClass( kvs::LineObject );

public:

    enum IntegrationMethod
    {
        Euler = 0,
        RungeKutta2nd = 1,
        RungeKutta4th = 2
    };

    enum IntegrationDirection
    {
        BackwardDirection = -1,
        BothDirections = 0,
        ForwardDirection = 1
    };

protected:

    kvs::PointObject* m_seed_points; ///< seed points
    IntegrationMethod m_integration_method; ///< integtration method
    IntegrationDirection m_integration_direction; ///< integration direction
    float m_integration_interval; ///< integration interval in the object coordinate
    float m_vector_length_threshold; ///< threshold of the vector length
    size_t m_integration_times_threshold; ///< threshold of the integration times
    bool m_enable_boundary_condition; ///< flag for the boundray condition
    bool m_enable_vector_length_condition; ///< flag for the vector length condition
    bool m_enable_integration_times_condition; ///< flag for the integration times

public:

    StreamlineBase();
    virtual ~StreamlineBase();

    void setSeedPoints( const kvs::PointObject* seed_points );
    void setIntegrationMethod( const StreamlineBase::IntegrationMethod method );
    void setIntegrationDirection( const StreamlineBase::IntegrationDirection direction );
    void setIntegrationInterval( const float interval );
    void setVectorLengthThreshold( const float length );
    void setIntegrationTimesThreshold( const size_t times );
    void setEnableBoundaryCondition( const bool enabled );
    void setEnableVectorLengthCondition( const bool enabled );
    void setEnableIntegrationTimesCondition( const bool enabled );

    virtual kvs::ObjectBase* exec( const kvs::ObjectBase* object ) = 0;

protected:

    virtual bool check_for_acceptance( const std::vector<kvs::Real32>& vertices ) = 0;
    virtual bool check_for_termination(
        const kvs::Vector3f& current_vertex,
        const kvs::Vector3f& direction,
        const size_t integration_times,
        const kvs::Vector3f& next_vertex ) = 0;
    virtual const kvs::Vector3f interpolate_vector( const kvs::Vector3f& vertex, const kvs::Vector3f& direction ) = 0;
    virtual const kvs::Vector3f calculate_vector( const kvs::Vector3f& vertex ) = 0;
    virtual const kvs::RGBColor calculate_color( const kvs::Vector3f& direction ) = 0;

    void mapping( const kvs::VolumeObjectBase* volume );
    void extract_lines( const kvs::StructuredVolumeObject* volume );
    bool calculate_line( std::vector<kvs::Real32>* vertices, std::vector<kvs::UInt8>* colors, const size_t index );
    bool calculate_one_side(
        std::vector<kvs::Real32>* coords,
        std::vector<kvs::UInt8>* colors,
        const kvs::Vector3f& seed_point,
        const kvs::Vector3f& seed_vector );
    bool calculate_next_vertex(
        const kvs::Vector3f& current_vertex,
        const kvs::Vector3f& current_direction,
        kvs::Vector3f* next_vertex );
    bool integrate_by_euler(
        const kvs::Vector3f& current_vertex,
        const kvs::Vector3f& current_direction,
        kvs::Vector3f* next_vertex );
    bool integrate_by_runge_kutta_2nd(
        const kvs::Vector3f& current_vertex,
        const kvs::Vector3f& current_direction,
        kvs::Vector3f* next_vertex );
    bool integrate_by_runge_kutta_4th(
        const kvs::Vector3f& current_vertex,
        const kvs::Vector3f& current_direction,
        kvs::Vector3f* next_vertex );

    bool check_for_inside_volume( const kvs::Vector3f& seed );
    bool check_for_vector_length( const kvs::Vector3f& direction );
    bool check_for_integration_times( const size_t times );
};

} // end of namespace kvs

#endif // KVS__STREAMLINE_BASE_H_INCLUDE
