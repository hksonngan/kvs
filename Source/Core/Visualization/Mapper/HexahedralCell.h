/****************************************************************************/
/**
 *  @file HexahedralCell.h
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
#ifndef KVS_CORE_HEXAHEDRAL_CELL_H_INCLUDE
#define KVS_CORE_HEXAHEDRAL_CELL_H_INCLUDE

#include <kvs/Type>
#include <kvs/Vector4>
#include <kvs/Matrix44>
#include <kvs/UnstructuredVolumeObject>
#include "CellBase.h"


namespace kvs
{

template <typename T>
class HexahedralCell : public kvs::CellBase<T>
{
public:

    enum { NumberOfNodes = kvs::UnstructuredVolumeObject::Hexahedra };

public:

    typedef kvs::CellBase<T> BaseClass;

public:

    HexahedralCell( const kvs::UnstructuredVolumeObject* volume );

    virtual ~HexahedralCell( void );

public:

    void attachCell( const kvs::UInt32 cell );

    void attachPoint( const kvs::Vector3f& point );

    const kvs::Vector3f randomSampling( void );

    const kvs::Real32 volume( void );

    const kvs::Real32 averagedScalar( void );

    const kvs::Real32 scalar( void );

    const kvs::Vector3f gradient( void );

private:

    void calculate_interpolation_function( void );

    void calculate_differential_function( void );

    const kvs::Matrix33f get_transposed_Jacobi_matrix( void ) const;

    const kvs::Vector3f convert_local_to_global( void ) const;
};

template <typename T>
inline HexahedralCell<T>::HexahedralCell(
    const kvs::UnstructuredVolumeObject* volume ):
    kvs::CellBase<T>( volume )
{
}

template <typename T>
inline HexahedralCell<T>::~HexahedralCell( void )
{
}

template <typename T>
inline void HexahedralCell<T>::attachCell( const kvs::UInt32 index )
{
    // Aliases.
    const kvs::UnstructuredVolumeObject* volume = BaseClass::m_reference_volume;
    const kvs::UInt32* const connections = volume->connections().pointer();
    const kvs::Real32* const coords      = volume->coords().pointer();
    const T* const           values      = static_cast<const T*>( volume->values().pointer() );

    const kvs::UInt32 nnodes = NumberOfNodes;
    const kvs::UInt32 connection_index = nnodes * index;

    const kvs::UInt32 node_index[nnodes] =
    {
        connections[ connection_index     ],
        connections[ connection_index + 1 ],
        connections[ connection_index + 2 ],
        connections[ connection_index + 3 ],
        connections[ connection_index + 4 ],
        connections[ connection_index + 5 ],
        connections[ connection_index + 6 ],
        connections[ connection_index + 7 ]
    };

    const kvs::UInt32 coord_index[nnodes] =
    {
        3 * node_index[0],
        3 * node_index[1],
        3 * node_index[2],
        3 * node_index[3],
        3 * node_index[4],
        3 * node_index[5],
        3 * node_index[6],
        3 * node_index[7]
    };

    BaseClass::m_vertices[0].set( coords[ coord_index[0] ], coords[ coord_index[0] + 1 ], coords[ coord_index[0] + 2 ] );
    BaseClass::m_vertices[1].set( coords[ coord_index[1] ], coords[ coord_index[1] + 1 ], coords[ coord_index[1] + 2 ] );
    BaseClass::m_vertices[2].set( coords[ coord_index[2] ], coords[ coord_index[2] + 1 ], coords[ coord_index[2] + 2 ] );
    BaseClass::m_vertices[3].set( coords[ coord_index[3] ], coords[ coord_index[3] + 1 ], coords[ coord_index[3] + 2 ] );
    BaseClass::m_vertices[4].set( coords[ coord_index[4] ], coords[ coord_index[4] + 1 ], coords[ coord_index[4] + 2 ] );
    BaseClass::m_vertices[5].set( coords[ coord_index[5] ], coords[ coord_index[5] + 1 ], coords[ coord_index[5] + 2 ] );
    BaseClass::m_vertices[6].set( coords[ coord_index[6] ], coords[ coord_index[6] + 1 ], coords[ coord_index[6] + 2 ] );
    BaseClass::m_vertices[7].set( coords[ coord_index[7] ], coords[ coord_index[7] + 1 ], coords[ coord_index[7] + 2 ] );

    BaseClass::m_scalars[0] = values[ node_index[0] ];
    BaseClass::m_scalars[1] = values[ node_index[1] ];
    BaseClass::m_scalars[2] = values[ node_index[2] ];
    BaseClass::m_scalars[3] = values[ node_index[3] ];
    BaseClass::m_scalars[4] = values[ node_index[4] ];
    BaseClass::m_scalars[5] = values[ node_index[5] ];
    BaseClass::m_scalars[6] = values[ node_index[6] ];
    BaseClass::m_scalars[7] = values[ node_index[7] ];
}

template <typename T>
inline void HexahedralCell<T>::attachPoint( const kvs::Vector3f& point )
{
    BaseClass::set_global_point( point );
}

template <typename T>
const kvs::Vector3f HexahedralCell<T>::randomSampling( void )
{
    // Generate a point in the local coordinate.
    const float s = BaseClass::random_number();
    const float t = BaseClass::random_number();
    const float u = BaseClass::random_number();

    BaseClass::set_local_point( kvs::Vector3f( s, t, u ) );

    this->calculate_interpolation_function();
    BaseClass::set_global_point( this->convert_local_to_global() );

    return( BaseClass::m_global_point );
}

template <typename T>
inline const kvs::Real32 HexahedralCell<T>::volume( void )
{
    size_t nmetric_sample = 3;
    size_t sampling_1D = nmetric_sample;
    size_t sampling_2D = sampling_1D * sampling_1D;
    size_t sampling_3D = sampling_1D * sampling_2D;

    const float sampling_length = 1.0f / static_cast<float>( sampling_1D );
    const float adjastment = sampling_length * 0.5f;

    kvs::Vector3f sampling_position;

    float sum_metric = 0;

    for( size_t k = 0 ; k < sampling_1D ; k++ )
    {
        for( size_t j = 0 ; j < sampling_1D ; j++ )
        {
            for( size_t i = 0 ; i < sampling_1D ; i++ )
            {
                sampling_position[ 0 ] = i * sampling_length - adjastment;
                sampling_position[ 1 ] = j * sampling_length - adjastment;
                sampling_position[ 2 ] = k * sampling_length - adjastment;

                BaseClass::set_local_point( sampling_position );
                this->calculate_differential_function();

                const kvs::Matrix33f J = this->get_transposed_Jacobi_matrix();
                const float metric_element = J.determinant();

                sum_metric += kvs::Math::Abs<float>( metric_element );
            }
        }
    }

    return( sum_metric / static_cast<float>( sampling_3D ) );
}

template <typename T>
inline const kvs::Real32 HexahedralCell<T>::averagedScalar( void )
{
    const kvs::Real32 w = 1.0f / HexahedralCell::NumberOfNodes;

    return( static_cast<kvs::Real32>(
                BaseClass::m_scalars[0] +
                BaseClass::m_scalars[1] +
                BaseClass::m_scalars[2] +
                BaseClass::m_scalars[3] +
                BaseClass::m_scalars[4] +
                BaseClass::m_scalars[5] +
                BaseClass::m_scalars[6] +
                BaseClass::m_scalars[7] ) * w );
}

template <typename T>
inline const kvs::Real32 HexahedralCell<T>::scalar( void )
{
    const float* I = BaseClass::m_interpolation_functions;
    const T* s = BaseClass::m_scalars;

    return( static_cast<kvs::Real32>(
                I[0]*s[0] +
                I[1]*s[1] +
                I[2]*s[2] +
                I[3]*s[3] +
                I[4]*s[4] +
                I[5]*s[5] +
                I[6]*s[6] +
                I[7]*s[7] ) );
}

template <typename T>
inline const kvs::Vector3f HexahedralCell<T>::gradient( void )
{
    this->calculate_differential_function();

    // Calculate a gradient vector in the local coordinate.
    const float* dIdx = BaseClass::m_differential_functions;
    const float* dIdy = BaseClass::m_differential_functions + NumberOfNodes;
    const float* dIdz = BaseClass::m_differential_functions + NumberOfNodes * 2;
    const T*     s    = BaseClass::m_scalars;

    const float dsdx =
        static_cast<float>(
            s[0]*dIdx[0] + s[1]*dIdx[1] + s[2]*dIdx[2] + s[3]*dIdx[3] +
            s[4]*dIdx[4] + s[5]*dIdx[5] + s[6]*dIdx[6] + s[7]*dIdx[7] );

    const float dsdy =
        static_cast<float>(
            s[0]*dIdy[0] + s[1]*dIdy[1] + s[2]*dIdy[2] + s[3]*dIdy[3] +
            s[4]*dIdy[4] + s[5]*dIdy[5] + s[6]*dIdy[6] + s[7]*dIdy[7] );

    const float dsdz =
        static_cast<float>(
            s[0]*dIdz[0] + s[1]*dIdz[1] + s[2]*dIdz[2] + s[3]*dIdz[3] +
            s[4]*dIdz[4] + s[5]*dIdz[5] + s[6]*dIdz[6] + s[7]*dIdz[7] );

    const kvs::Vector3f g( dsdx, dsdy, dsdz );

    // Calculate a gradient vector in the global coordinate.
    const kvs::Matrix33f J = this->get_transposed_Jacobi_matrix();
    const kvs::Vector3f  G = J.inverse() * g;

    return( G );
}

/*==========================================================================*/
/**
 *  Calculates the interpolation functions in the local coordinate.
 */
/*==========================================================================*/
template <typename T>
inline void HexahedralCell<T>::calculate_interpolation_function( void )
{
    const float x = BaseClass::m_local_point[0];
    const float y = BaseClass::m_local_point[1];
    const float z = BaseClass::m_local_point[2];

    const float xy = x * y;
    const float yz = y * z;
    const float zx = z * x;

    const float xyz = xy * z;

    BaseClass::m_interpolation_functions[0] = z - zx - yz + xyz;
    BaseClass::m_interpolation_functions[1] = zx - xyz;
    BaseClass::m_interpolation_functions[2] = xyz;
    BaseClass::m_interpolation_functions[3] = yz - xyz;
    BaseClass::m_interpolation_functions[4] = 1.0f - x - y - z + xy + yz + zx - xyz;
    BaseClass::m_interpolation_functions[5] = x - xy - zx + xyz;
    BaseClass::m_interpolation_functions[6] = xy - xyz;
    BaseClass::m_interpolation_functions[7] = y - xy - yz + xyz;
}

/*==========================================================================*/
/**
 *  Calculates the differential functions in the local coordinate.
 */
/*==========================================================================*/
template <typename T>
inline void HexahedralCell<T>::calculate_differential_function( void )
{
    const float x = BaseClass::m_local_point[0];
    const float y = BaseClass::m_local_point[1];
    const float z = BaseClass::m_local_point[2];

    const float xy = x * y;
    const float yz = y * z;
    const float zx = z * x;

    // dNdx
    BaseClass::m_differential_functions[ 0] =  - z + yz;
    BaseClass::m_differential_functions[ 1] =  z - yz;
    BaseClass::m_differential_functions[ 2] =  yz;
    BaseClass::m_differential_functions[ 3] =  - yz;
    BaseClass::m_differential_functions[ 4] =  - 1.0f + y +z - yz;
    BaseClass::m_differential_functions[ 5] =  1.0f - y - z + yz;
    BaseClass::m_differential_functions[ 6] =  y - yz;
    BaseClass::m_differential_functions[ 7] =  - y + yz;

    // dNdy
    BaseClass::m_differential_functions[ 8] =  - z + zx;
    BaseClass::m_differential_functions[ 9] =  - zx;
    BaseClass::m_differential_functions[10] =  zx;
    BaseClass::m_differential_functions[11] =  z - zx;
    BaseClass::m_differential_functions[12] =  - 1.0f + x + z - zx;
    BaseClass::m_differential_functions[13] =  - x + zx;
    BaseClass::m_differential_functions[14] =  x - zx;
    BaseClass::m_differential_functions[15] =  1.0f - x - z + zx;

    // dNdz
    BaseClass::m_differential_functions[16] =  1.0f - y - x + xy;
    BaseClass::m_differential_functions[17] =  x - xy;
    BaseClass::m_differential_functions[18] =  xy;
    BaseClass::m_differential_functions[19] =  y - xy;
    BaseClass::m_differential_functions[20] =  - 1.0f + y + x - xy;
    BaseClass::m_differential_functions[21] =  - x + xy;
    BaseClass::m_differential_functions[22] =  - xy;
    BaseClass::m_differential_functions[23] =  - y + xy;
}

template <typename T>
inline const kvs::Matrix33f HexahedralCell<T>::get_transposed_Jacobi_matrix( void ) const
{
    const float* dNdx = BaseClass::m_differential_functions;
    const float* dNdy = BaseClass::m_differential_functions + NumberOfNodes;
    const float* dNdz = BaseClass::m_differential_functions + NumberOfNodes * 2;
    const kvs::Vector3f* V = BaseClass::m_vertices;

    const float dXdx =
        dNdx[0]*V[0].x() + dNdx[1]*V[1].x() + dNdx[2]*V[2].x() + dNdx[3]*V[3].x() +
        dNdx[4]*V[4].x() + dNdx[5]*V[5].x() + dNdx[6]*V[6].x() + dNdx[7]*V[7].x() ;

    const float dYdx =
        dNdx[0]*V[0].y() + dNdx[1]*V[1].y() + dNdx[2]*V[2].y() + dNdx[3]*V[3].y() +
        dNdx[4]*V[4].y() + dNdx[5]*V[5].y() + dNdx[6]*V[6].y() + dNdx[7]*V[7].y() ;

    const float dZdx =
        dNdx[0]*V[0].z() + dNdx[1]*V[1].z() + dNdx[2]*V[2].z() + dNdx[3]*V[3].z() +
        dNdx[4]*V[4].z() + dNdx[5]*V[5].z() + dNdx[6]*V[6].z() + dNdx[7]*V[7].z() ;


    const float dXdy =
        dNdy[0]*V[0].x() + dNdy[1]*V[1].x() + dNdy[2]*V[2].x() + dNdy[3]*V[3].x() +
        dNdy[4]*V[4].x() + dNdy[5]*V[5].x() + dNdy[6]*V[6].x() + dNdy[7]*V[7].x() ;

    const float dYdy =
        dNdy[0]*V[0].y() + dNdy[1]*V[1].y() + dNdy[2]*V[2].y() + dNdy[3]*V[3].y() +
        dNdy[4]*V[4].y() + dNdy[5]*V[5].y() + dNdy[6]*V[6].y() + dNdy[7]*V[7].y() ;

    const float dZdy =
        dNdy[0]*V[0].z() + dNdy[1]*V[1].z() + dNdy[2]*V[2].z() + dNdy[3]*V[3].z() +
        dNdy[4]*V[4].z() + dNdy[5]*V[5].z() + dNdy[6]*V[6].z() + dNdy[7]*V[7].z() ;


    const float dXdz =
        dNdz[0]*V[0].x() + dNdz[1]*V[1].x() + dNdz[2]*V[2].x() + dNdz[3]*V[3].x() +
        dNdz[4]*V[4].x() + dNdz[5]*V[5].x() + dNdz[6]*V[6].x() + dNdz[7]*V[7].x() ;

    const float dYdz =
        dNdz[0]*V[0].y() + dNdz[1]*V[1].y() + dNdz[2]*V[2].y() + dNdz[3]*V[3].y() +
        dNdz[4]*V[4].y() + dNdz[5]*V[5].y() + dNdz[6]*V[6].y() + dNdz[7]*V[7].y() ;

    const float dZdz =
        dNdz[0]*V[0].z() + dNdz[1]*V[1].z() + dNdz[2]*V[2].z() + dNdz[3]*V[3].z() +
        dNdz[4]*V[4].z() + dNdz[5]*V[5].z() + dNdz[6]*V[6].z() + dNdz[7]*V[7].z() ;

    return( kvs::Matrix33f( dXdx, dYdx, dZdx, dXdy, dYdy, dZdy, dXdz, dYdz, dZdz ) );
}

template <typename T>
inline const kvs::Vector3f HexahedralCell<T>::convert_local_to_global( void ) const
{
    const float*         N = BaseClass::m_interpolation_functions;
    const kvs::Vector3f* V = BaseClass::m_vertices;

    const float X =
        N[0] * V[0].x() +
        N[1] * V[1].x() +
        N[2] * V[2].x() +
        N[3] * V[3].x() +
        N[4] * V[4].x() +
        N[5] * V[5].x() +
        N[6] * V[6].x() +
        N[7] * V[7].x() ;

    const float Y =
        N[0] * V[0].y() +
        N[1] * V[1].y() +
        N[2] * V[2].y() +
        N[3] * V[3].y() +
        N[4] * V[4].y() +
        N[5] * V[5].y() +
        N[6] * V[6].y() +
        N[7] * V[7].y() ;

    const float Z =
        N[0] * V[0].z() +
        N[1] * V[1].z() +
        N[2] * V[2].z() +
        N[3] * V[3].z() +
        N[4] * V[4].z() +
        N[5] * V[5].z() +
        N[6] * V[6].z() +
        N[7] * V[7].z() ;

    return( kvs::Vector3f( X, Y, Z ) );
}

} // end of namespace kvs

#endif // KVS_CORE_HEXAHEDRAL_CELL_H_INCLUDE
