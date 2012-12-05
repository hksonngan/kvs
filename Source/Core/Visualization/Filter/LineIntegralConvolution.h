
/*****************************************************************************/
/**
 *  @file   line_integral_convolution.h
 *  @brief  LIC (Line Integral Convolution) filtering class.
 *
 *  @author Naohisa Sakamoto
 *  @date   2012/12/05 15:23:06
 */
/*----------------------------------------------------------------------------
 *
 *  $Author: kawamura $
 *  $Date: 2009/01/15 12:52:12 $
 *  $Source: /home/Repository/viz-server2/cvsroot/KVS_RC1/Source/Core/Visualization/Filter/LineIntegralConvolution.h,v $
 *  $Revision: 1.2 $
 */
/*****************************************************************************/
#ifndef KVS__LINE_INTEGRAL_CONVOLUTION_H_INCLUDE
#define KVS__LINE_INTEGRAL_CONVOLUTION_H_INCLUDE

#include <kvs/StructuredVolumeObject>
#include <kvs/FilterBase>
#include <kvs/Module>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  LIC class.
 */
/*===========================================================================*/
class LineIntegralConvolution : public kvs::FilterBase, public kvs::StructuredVolumeObject
{
    kvsModuleName( kvs::LineIntegralConvolution );
    kvsModuleCategory( Filter );
    kvsModuleBaseClass( kvs::FilterBase );
    kvsModuleSuperClass( kvs::StructuredVolumeObject );

protected:

    double m_length; ///< stream length
    kvs::StructuredVolumeObject* m_noise; ///< white noise volume

public:

    LineIntegralConvolution();
    LineIntegralConvolution( const kvs::StructuredVolumeObject* volume );
    LineIntegralConvolution( const kvs::StructuredVolumeObject* volume, const double length );
    virtual ~LineIntegralConvolution();

    void setLength( const double length );

    SuperClass* exec( const kvs::ObjectBase* object );

protected:

    void filtering( const kvs::StructuredVolumeObject* volume );
    void create_noise_volume( const kvs::StructuredVolumeObject* volume );
    template <typename T>
    void convolution( const kvs::StructuredVolumeObject* volume );
};

} // end of namespace kvs

#endif // KVS__LINE_INTEGRAL_CONVOLUTION_H_INCLUDE
