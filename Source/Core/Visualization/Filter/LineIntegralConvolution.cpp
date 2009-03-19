/*****************************************************************************/
/**
 *  @file   line_integral_convolution.cpp
 *  @brief  LIC (Line Integral Convolution) class.
 *
 *  @author Naohisa Sakamoto
 *  @date   2009/01/15 20:06:32
 */
/*----------------------------------------------------------------------------
 *
 *  $Author: kawamura $
 *  $Date: 2009/01/15 12:52:12 $
 *  $Source: /home/Repository/viz-server2/cvsroot/KVS_RC1/Source/Core/Visualization/Filter/LineIntegralConvolution.cpp,v $
 *  $Revision: 1.2 $
 */
/*****************************************************************************/
#include "LineIntegralConvolution.h"
#include<kvs/MersenneTwister>
#include<kvs/Vector3>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  
 */
/*===========================================================================*/
LineIntegralConvolution::LineIntegralConvolution( void ):
    m_length( 0.0 ),
    m_noise( NULL )
{

}

/*===========================================================================*/
/**
 *  @brief  
 *
 *  @param  volume      
 */
/*===========================================================================*/
LineIntegralConvolution::LineIntegralConvolution( const kvs::StructuredVolumeObject* volume ):
    m_noise( NULL )
{
    const kvs::Vector3ui& r = volume->resolution();
    m_length = kvs::Math::Max<double>( r.x(), r.y(), r.z() ) * 0.1;
    this->exec( volume );
}

/*===========================================================================*/
/**
 *  @brief  
 *
 *  @param  volume      
 *  @param  length      
 */
/*===========================================================================*/
LineIntegralConvolution::LineIntegralConvolution( const kvs::StructuredVolumeObject* volume, const double length ):
    m_length( length ),
    m_noise( NULL )
{
    this->exec( volume );
}

/*===========================================================================*/
/**
 *  @brief  
 */
/*===========================================================================*/
LineIntegralConvolution::~LineIntegralConvolution( void )
{
    if( m_noise ){ delete m_noise; m_noise = NULL; }
}

/*===========================================================================*/
/**
 *  @brief  
 *
 *  @param  length      
 */
/*===========================================================================*/
void LineIntegralConvolution::setLength( const double length )
{
    m_length = length;
}

/*===========================================================================*/
/**
 *  @brief  LIC.
 *
 *  @param  volume [i] pointer to a uniform volume data
 *
 *  @return LIC filtered unifrom volume data
 */
/*===========================================================================*/
kvs::ObjectBase* LineIntegralConvolution::exec( const kvs::ObjectBase* object )
{
    const kvs::ObjectBase::ObjectType object_type = object->objectType();
    if ( object_type == kvs::ObjectBase::Geometry )
    {
        kvsMessageError("Geometry object is not supported.");
        return( NULL );
    }

    const kvs::VolumeObjectBase* volume = reinterpret_cast<const kvs::VolumeObjectBase*>( object );
    const kvs::VolumeObjectBase::VolumeType volume_type = volume->volumeType();
    if ( volume_type == kvs::VolumeObjectBase::Structured )
    {
        this->create_noise_volume( reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
        this->filtering( reinterpret_cast<const kvs::StructuredVolumeObject*>( object ) );
    }
    else // volume_type == kvs::VolumeObjectBase::Unstructured
    {
        kvsMessageError("Unstructured volume object is not supported.");
        return( NULL );
    }

    return( this );
}

void LineIntegralConvolution::filtering( const kvs::StructuredVolumeObject* volume )
{
    // Set the min/max coordinates.
    //BaseClass::set_min_max_coords( volume, this );
    SuperClass::setMinMaxObjectCoords( volume->minObjectCoord(), volume->maxObjectCoord() );
    SuperClass::setMinMaxExternalCoords( volume->minExternalCoord(), volume->maxExternalCoord() );

    const std::type_info& type = volume->values().typeInfo()->type();
    if(      type == typeid(float) )  this->convolution<float>( volume );
    else if( type == typeid(double) ) this->convolution<double>( volume );
    else
    {
        kvsMessageError("Input volume data type is not float/double.");
        return;
    }
}

/*===========================================================================*/
/**
 *  @brief  Create a noise volume.
 *
 *  @param  volume [i] pointer to a uniform volume data
 */
/*===========================================================================*/
void LineIntegralConvolution::create_noise_volume( const kvs::StructuredVolumeObject* volume )
{
    kvs::Vector3ui resol( volume->resolution() );

    //kvs::StructuredVolumeObject::Values data;
    kvs::ValueArray<kvs::UInt8> data( volume->nnodes() );

    // Random number generator. R = [0,1)
    kvs::MersenneTwister R;

    // Create a white noise volume.
    unsigned int counter = 0;
    for( size_t k = 0; k < resol.z(); k++ )
    {
        for( size_t j = 0; j < resol.y(); j++ )
        {
            for( size_t i = 0; i < resol.x(); i++ )
            {
                data[ counter ] = static_cast<kvs::UInt8>(  R() * 255.0 );
                counter++;
            }
        }
    }

    // Copy the white noise volume to m_noise.
    m_noise = new kvs::StructuredVolumeObject( volume->resolution(), 1, kvs::AnyValueArray( data ) );

    if( !m_noise )
    {
        kvsMessageError("Cannot create noise volume.");
        return;
    }
}

/*===========================================================================*/
/**
 *  @brief  Convolution.
 *
 *  @param  volume [i] pointer to a uniform volume data
 */
/*===========================================================================*/
template <typename T>
void LineIntegralConvolution::convolution( const kvs::StructuredVolumeObject* volume )
{
    kvs::Vector3<T> u;         // vector of node
    kvs::Vector3<T> p;         // position of node
    kvs::Vector3<T> travel_t;  //
    kvs::Vector3<T> entry_pos; //

    const kvs::UInt8*           noise_data = static_cast<const kvs::UInt8*>( m_noise->values().pointer() );
    const T*                    src_data = static_cast<const T*>( volume->values().pointer() );

    kvs::ValueArray<kvs::UInt8> dst_data( volume->nnodes() );

    const kvs::Vector3ui resol( volume->resolution() );

    unsigned int counter = 0;
    for( size_t k = 0; k < resol.z(); k++ )
    {
        for( size_t j = 0; j < resol.y(); j++ )
        {
            for( size_t i = 0; i < resol.x(); i++ )
            {
                int i_c = i;
                int j_c = j;
                int k_c = k;

                T acc_length = T(0);
                T acc_data   = T(0);

                unsigned int loc_c = counter;

                for( int m = 1; m > -2; m -= 2  )
                {
                    i_c = i;
                    j_c = j;
                    k_c = k;

                    entry_pos[0] = T( i + 0.5 );
                    entry_pos[1] = T( j + 0.5 );
                    entry_pos[2] = T( k + 0.5 );

                    loc_c = counter;

                    while( acc_length < m_length )
                    {
                        T   t_min = 1.0e+10;
                        int l_min = -1;
                        int inc;

                        int scalar = noise_data[loc_c];

                        u = (T)m * kvs::Vector3<T>( src_data + 3 * loc_c );

                        p[0] = T( i_c );
                        p[1] = T( j_c );
                        p[2] = T( k_c );

                        for( int l = 0; l < 3; l++ )
                        {
                            if( kvs::Math::IsZero( u[l] ) )
                            {
                                travel_t[l] = T( 1.1e+10 );
                            }
                            else if( u[l] < T(0) )
                            {
                                travel_t[l] = ( p[l] - entry_pos[l] ) / u[l];
                            }
                            else
                            {
                                travel_t[l] = ( p[l] + 1 - entry_pos[l] ) / u[l];
                            }

                            if( travel_t[l] < t_min )
                            {
                                t_min = travel_t[l];
                                l_min = l;
                            }
                        }

                        if( l_min == -1 ) break;

                        entry_pos += u * t_min;

                        inc = u[l_min] < T(0) ? -1 : 1;

                        if( l_min == 0 )
                        {
                            loc_c += inc;
                            i_c   += inc;
                        }
                        else if( l_min == 1 )
                        {
                            loc_c += inc * resol.x();
                            j_c   += inc;
                        }
                        else if( l_min == 2 )
                        { 
                            loc_c += inc * resol.x() * resol.y();
                            k_c   += inc;
                        }

                        T length = t_min * static_cast<T>( u.length() );

                        /* For small length (close to 0.0) it enters in a infinite loop */
                        if( kvs::Math::IsZero( length ) ) length = T( 1.1e+10 );

                        if( acc_length < 1.1e-10 ) acc_length = T(0);

                        acc_data   += length * scalar;
                        acc_length += length;

                        if( i_c < 0 || i_c >= static_cast<int>(resol.x()) ||
                            j_c < 0 || j_c >= static_cast<int>(resol.y()) ||
                            k_c < 0 || k_c >= static_cast<int>(resol.z()) ) break;
                    }
                }

                acc_data /= acc_length;
                dst_data[counter] = (kvs::UInt8)( (int)(acc_data) % 256 );

                counter++;
            }
        }
    }

    SuperClass::setGridType( volume->gridType() );
    SuperClass::setVeclen( 1 );
    SuperClass::setResolution( volume->resolution() );
    SuperClass::setValues( kvs::AnyValueArray( dst_data ) );
    SuperClass::setMinMaxValues( 0, 255 );
}

} // end of namespace kvs
