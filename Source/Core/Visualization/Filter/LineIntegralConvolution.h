
/*****************************************************************************/
/**
 *  @file   line_integral_convolution.h
 *  @brief  LIC (Line Integral Convolution) filtering class.
 *
 *  @author Naohisa Sakamoto
 *  @date   2009/01/15 11:36:35
 */
/*----------------------------------------------------------------------------
 *
 *  $Author: kawamura $
 *  $Date: 2009/01/15 12:52:12 $
 *  $Source: /home/Repository/viz-server2/cvsroot/KVS_RC1/Source/Core/Visualization/Filter/LineIntegralConvolution.h,v $
 *  $Revision: 1.2 $
 */
/*****************************************************************************/
#ifndef KVS_LINE_INTEGRAL_CONVOLUTION_H_INCLUDE
#define KVS_LINE_INTEGRAL_CONVOLUTION_H_INCLUDE

#include <kvs/StructuredVolumeObject>
#include <kvs/FilterBase>
#include <kvs/ClassName>
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
    // Class name.
    kvsClassName( LineIntegralConvolution );

    // Module information.
    kvsModuleCategory( Filter );
    kvsModuleBaseClass( kvs::FilterBase );
    kvsModuleSuperClass( kvs::StructuredVolumeObject );


protected:

    double                       m_length; //!< stream length
    kvs::StructuredVolumeObject* m_noise;  //!< white noise volume

public:

    LineIntegralConvolution( void );

    LineIntegralConvolution( const kvs::StructuredVolumeObject* volume );

    LineIntegralConvolution( const kvs::StructuredVolumeObject* volume, const double length );

    virtual ~LineIntegralConvolution( void );

public:

    void setLength( const double length );

public:

    kvs::ObjectBase* exec( const kvs::ObjectBase* object );

protected:

    void filtering( const kvs::StructuredVolumeObject* volume );

    void create_noise_volume( const kvs::StructuredVolumeObject* volume );

    template <typename T>
    void convolution( const kvs::StructuredVolumeObject* volume );
};

} // end of namespace kvs


#endif // KVS__LINE_INTEGRAL_CONVOLUTION_H_INCLUDE
