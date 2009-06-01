/*****************************************************************************/
/**
 *  @file   QuadraticTetrahedralCell.h
 *  @author Naohisa Sakamoto
 *  @brief  Quadratic tetrahedral cell class.
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright 2007 Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#ifndef KVS__QUADRATIC_HEXAHEDRAL_CELL_H_INCLUDE
#define KVS__QUADRATIC_HEXAHEDRAL_CELL_H_INCLUDE

#include <kvs/Type>
#include <kvs/Vector4>
#include <kvs/Matrix44>
#include <kvs/UnstructuredVolumeObject>
#include "CellBase.h"


namespace kvs
{

template <typename T>
class QuadraticHexahedralCell : public kvs::CellBase<T>
{
public:

    enum { NumberOfNodes = kvs::UnstructuredVolumeObject::QuadraticHexahedra };

public:

    typedef kvs::CellBase<T> BaseClass;

public:

    QuadraticHexahedralCell( const kvs::UnstructuredVolumeObject* volume );

    virtual ~QuadraticHexahedralCell( void );

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
inline QuadraticHexahedralCell<T>::QuadraticHexahedralCell(
    const kvs::UnstructuredVolumeObject* volume ):
    kvs::CellBase<T>( volume )
{
}

template <typename T>
inline QuadraticHexahedralCell<T>::~QuadraticHexahedralCell( void )
{
}

template <typename T>
inline void QuadraticHexahedralCell<T>::attachCell( const kvs::UInt32 index )
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
        connections[ connection_index + 7 ],
        connections[ connection_index + 8 ],
        connections[ connection_index + 9 ],
        connections[ connection_index +10 ],
        connections[ connection_index +11 ],
        connections[ connection_index +12 ],
        connections[ connection_index +13 ],
        connections[ connection_index +14 ],
        connections[ connection_index +15 ],
        connections[ connection_index +16 ],
        connections[ connection_index +17 ],
        connections[ connection_index +18 ],
        connections[ connection_index +19 ]
    };

    const kvs::UInt32 coord_index[nnodes] =
    {
        3 * node_index[ 0],
        3 * node_index[ 1],
        3 * node_index[ 2],
        3 * node_index[ 3],
        3 * node_index[ 4],
        3 * node_index[ 5],
        3 * node_index[ 6],
        3 * node_index[ 7],
        3 * node_index[ 8],
        3 * node_index[ 9],
        3 * node_index[10],
        3 * node_index[11],
        3 * node_index[12],
        3 * node_index[13],
        3 * node_index[14],
        3 * node_index[15],
        3 * node_index[16],
        3 * node_index[17],
        3 * node_index[18],
        3 * node_index[19]
    };

    BaseClass::m_vertices[ 0].set( coords[ coord_index[ 0] ], coords[ coord_index[ 0] + 1 ], coords[ coord_index[ 0] + 2 ] );
    BaseClass::m_vertices[ 1].set( coords[ coord_index[ 1] ], coords[ coord_index[ 1] + 1 ], coords[ coord_index[ 1] + 2 ] );
    BaseClass::m_vertices[ 2].set( coords[ coord_index[ 2] ], coords[ coord_index[ 2] + 1 ], coords[ coord_index[ 2] + 2 ] );
    BaseClass::m_vertices[ 3].set( coords[ coord_index[ 3] ], coords[ coord_index[ 3] + 1 ], coords[ coord_index[ 3] + 2 ] );
    BaseClass::m_vertices[ 4].set( coords[ coord_index[ 4] ], coords[ coord_index[ 4] + 1 ], coords[ coord_index[ 4] + 2 ] );
    BaseClass::m_vertices[ 5].set( coords[ coord_index[ 5] ], coords[ coord_index[ 5] + 1 ], coords[ coord_index[ 5] + 2 ] );
    BaseClass::m_vertices[ 6].set( coords[ coord_index[ 6] ], coords[ coord_index[ 6] + 1 ], coords[ coord_index[ 6] + 2 ] );
    BaseClass::m_vertices[ 7].set( coords[ coord_index[ 7] ], coords[ coord_index[ 7] + 1 ], coords[ coord_index[ 7] + 2 ] );
    BaseClass::m_vertices[ 8].set( coords[ coord_index[ 8] ], coords[ coord_index[ 8] + 1 ], coords[ coord_index[ 8] + 2 ] );
    BaseClass::m_vertices[ 9].set( coords[ coord_index[ 9] ], coords[ coord_index[ 9] + 1 ], coords[ coord_index[ 9] + 2 ] );
    BaseClass::m_vertices[10].set( coords[ coord_index[10] ], coords[ coord_index[10] + 1 ], coords[ coord_index[10] + 2 ] );
    BaseClass::m_vertices[11].set( coords[ coord_index[11] ], coords[ coord_index[11] + 1 ], coords[ coord_index[11] + 2 ] );
    BaseClass::m_vertices[12].set( coords[ coord_index[12] ], coords[ coord_index[12] + 1 ], coords[ coord_index[12] + 2 ] );
    BaseClass::m_vertices[13].set( coords[ coord_index[13] ], coords[ coord_index[13] + 1 ], coords[ coord_index[13] + 2 ] );
    BaseClass::m_vertices[14].set( coords[ coord_index[14] ], coords[ coord_index[14] + 1 ], coords[ coord_index[14] + 2 ] );
    BaseClass::m_vertices[15].set( coords[ coord_index[15] ], coords[ coord_index[15] + 1 ], coords[ coord_index[15] + 2 ] );
    BaseClass::m_vertices[16].set( coords[ coord_index[16] ], coords[ coord_index[16] + 1 ], coords[ coord_index[16] + 2 ] );
    BaseClass::m_vertices[17].set( coords[ coord_index[17] ], coords[ coord_index[17] + 1 ], coords[ coord_index[17] + 2 ] );
    BaseClass::m_vertices[18].set( coords[ coord_index[18] ], coords[ coord_index[18] + 1 ], coords[ coord_index[18] + 2 ] );
    BaseClass::m_vertices[19].set( coords[ coord_index[19] ], coords[ coord_index[19] + 1 ], coords[ coord_index[19] + 2 ] );



    BaseClass::m_scalars[ 0] = values[ node_index[ 0] ];
    BaseClass::m_scalars[ 1] = values[ node_index[ 1] ];
    BaseClass::m_scalars[ 2] = values[ node_index[ 2] ];
    BaseClass::m_scalars[ 3] = values[ node_index[ 3] ];
    BaseClass::m_scalars[ 4] = values[ node_index[ 4] ];
    BaseClass::m_scalars[ 5] = values[ node_index[ 5] ];
    BaseClass::m_scalars[ 6] = values[ node_index[ 6] ];
    BaseClass::m_scalars[ 7] = values[ node_index[ 7] ];
    BaseClass::m_scalars[ 8] = values[ node_index[ 8] ];
    BaseClass::m_scalars[ 9] = values[ node_index[ 9] ];
    BaseClass::m_scalars[10] = values[ node_index[10] ];
    BaseClass::m_scalars[11] = values[ node_index[11] ];
    BaseClass::m_scalars[12] = values[ node_index[12] ];
    BaseClass::m_scalars[13] = values[ node_index[13] ];
    BaseClass::m_scalars[14] = values[ node_index[14] ];
    BaseClass::m_scalars[15] = values[ node_index[15] ];
    BaseClass::m_scalars[16] = values[ node_index[16] ];
    BaseClass::m_scalars[17] = values[ node_index[17] ];
    BaseClass::m_scalars[18] = values[ node_index[18] ];
    BaseClass::m_scalars[19] = values[ node_index[19] ];
}

template <typename T>
inline void QuadraticHexahedralCell<T>::attachPoint( const kvs::Vector3f& point )
{
    BaseClass::set_global_point( point );
}

template <typename T>
const kvs::Vector3f QuadraticHexahedralCell<T>::randomSampling( void )
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
inline const kvs::Real32 QuadraticHexahedralCell<T>::volume( void )
{
    const size_t resolution = 3;
    const float sampling_length = 1.0f / (float)resolution;
    const float adjustment = sampling_length * 0.5f;

    kvs::Vector3f sampling_position( -adjustment );

    float sum_metric = 0;

    for( size_t k = 0 ; k < resolution ; k++ )
    {
        sampling_position[ 2 ] +=  sampling_length;

        for( size_t j = 0 ; j < resolution ; j++ )
        {
            sampling_position[ 1 ] += sampling_length;

            for( size_t i = 0 ; i < resolution ; i++ )
            {
                sampling_position[ 0 ] += sampling_length;

                BaseClass::set_local_point( sampling_position );
                this->calculate_differential_function();

                const kvs::Matrix33f J = this->get_transposed_Jacobi_matrix();
                const float metric_element = J.determinant();

                sum_metric += kvs::Math::Abs<float>( metric_element );
            }
            sampling_position[ 0 ] = -adjustment;
        }
        sampling_position[ 1 ] = -adjustment;
    }

    const float resolution3 = resolution * resolution * resolution;

    return( sum_metric / resolution3 );
}

template <typename T>
inline const kvs::Real32 QuadraticHexahedralCell<T>::averagedScalar( void )
{
    const kvs::Real32 w = 1.0f / QuadraticHexahedralCell::NumberOfNodes;

    return( static_cast<kvs::Real32>(
                BaseClass::m_scalars[ 0] +
                BaseClass::m_scalars[ 1] +
                BaseClass::m_scalars[ 2] +
                BaseClass::m_scalars[ 3] +
                BaseClass::m_scalars[ 4] +
                BaseClass::m_scalars[ 5] +
                BaseClass::m_scalars[ 6] +
                BaseClass::m_scalars[ 7] +
                BaseClass::m_scalars[ 8] +
                BaseClass::m_scalars[ 9] +
                BaseClass::m_scalars[10] +
                BaseClass::m_scalars[11] +
                BaseClass::m_scalars[12] +
                BaseClass::m_scalars[13] +
                BaseClass::m_scalars[14] +
                BaseClass::m_scalars[15] +
                BaseClass::m_scalars[16] +
                BaseClass::m_scalars[17] +
                BaseClass::m_scalars[18] +
                BaseClass::m_scalars[19] ) * w );
}

template <typename T>
inline const kvs::Real32 QuadraticHexahedralCell<T>::scalar( void )
{
    const float* I = BaseClass::m_interpolation_functions;
    const T* s = BaseClass::m_scalars;

    return( static_cast<kvs::Real32>(
                I[ 0]*s[ 0] +
                I[ 1]*s[ 1] +
                I[ 2]*s[ 2] +
                I[ 3]*s[ 3] +
                I[ 4]*s[ 4] +
                I[ 5]*s[ 5] +
                I[ 6]*s[ 6] +
                I[ 7]*s[ 7] +
                I[ 8]*s[ 8] +
                I[ 9]*s[ 9] +
                I[10]*s[10] +
                I[11]*s[11] +
                I[12]*s[12] +
                I[13]*s[13] +
                I[14]*s[14] +
                I[15]*s[15] +
                I[16]*s[16] +
                I[17]*s[17] +
                I[18]*s[18] +
                I[19]*s[19] ) );
}

template <typename T>
inline const kvs::Vector3f QuadraticHexahedralCell<T>::gradient( void )
{
    this->calculate_differential_function();

    // Calculate a gradient vector in the local coordinate.
    const kvs::UInt32 nnodes = NumberOfNodes;
    const float* dIdx = BaseClass::m_differential_functions;
    const float* dIdy = BaseClass::m_differential_functions + nnodes;
    const float* dIdz = BaseClass::m_differential_functions + nnodes * 2;
    const T*     s    = BaseClass::m_scalars;

    const float dsdx =
        static_cast<float>(
            s[ 0]*dIdx[ 0] + s[ 1]*dIdx[ 1] + s[ 2]*dIdx[ 2] + s[ 3]*dIdx[ 3] + s[ 4]*dIdx[ 4] +
            s[ 5]*dIdx[ 5] + s[ 6]*dIdx[ 6] + s[ 7]*dIdx[ 7] + s[ 8]*dIdx[ 8] + s[ 9]*dIdx[ 9] +
            s[10]*dIdx[10] + s[11]*dIdx[11] + s[12]*dIdx[12] + s[13]*dIdx[13] + s[14]*dIdx[14] +
            s[15]*dIdx[15] + s[16]*dIdx[16] + s[17]*dIdx[17] + s[18]*dIdx[18] + s[19]*dIdx[19] );

    const float dsdy =
        static_cast<float>(
            s[ 0]*dIdy[ 0] + s[ 1]*dIdy[ 1] + s[ 2]*dIdy[ 2] + s[ 3]*dIdy[ 3] + s[ 4]*dIdy[ 4] +
            s[ 5]*dIdy[ 5] + s[ 6]*dIdy[ 6] + s[ 7]*dIdy[ 7] + s[ 8]*dIdy[ 8] + s[ 9]*dIdy[ 9] +
            s[10]*dIdy[10] + s[11]*dIdy[11] + s[12]*dIdy[12] + s[13]*dIdy[13] + s[14]*dIdy[14] +
            s[15]*dIdy[15] + s[16]*dIdy[16] + s[17]*dIdy[17] + s[18]*dIdy[18] + s[19]*dIdy[19] );

    const float dsdz =
        static_cast<float>(
            s[ 0]*dIdz[ 0] + s[ 1]*dIdz[ 1] + s[ 2]*dIdz[ 2] + s[ 3]*dIdz[ 3] + s[ 4]*dIdz[ 4] +
            s[ 5]*dIdz[ 5] + s[ 6]*dIdz[ 6] + s[ 7]*dIdz[ 7] + s[ 8]*dIdz[ 8] + s[ 9]*dIdz[ 9] +
            s[10]*dIdz[10] + s[11]*dIdz[11] + s[12]*dIdz[12] + s[13]*dIdz[13] + s[14]*dIdz[14] +
            s[15]*dIdz[15] + s[16]*dIdz[16] + s[17]*dIdz[17] + s[18]*dIdz[18] + s[19]*dIdz[19] );

    const kvs::Vector3f g( dsdx, dsdy, dsdz );

    // Calculate a gradient vector in the global coordinate.
    const kvs::Matrix33f J = this->get_transposed_Jacobi_matrix();
    const kvs::Vector3f  G = J.inverse() * g;

    return( G );
}

/*===========================================================================*/
/**
 *  @brief  Calculates the interpolation functions in the local coordinate.
 */
/*===========================================================================*/
template <typename T>
inline void QuadraticHexahedralCell<T>::calculate_interpolation_function( void )
{
    const float x = BaseClass::m_local_point[0];
    const float y = BaseClass::m_local_point[1];
    const float z = BaseClass::m_local_point[2];

    const float xy = x * y;
    const float yz = y * z;
    const float zx = z * x;

    const float xyz = xy * z;

    BaseClass::m_interpolation_functions[ 0] = ( 1 - x )*( 1 - y )*z*( - 1 - 2*x - 2*y + 2*z );
    BaseClass::m_interpolation_functions[ 1] = x*( 1 - y )*z*( - 3 + 2*x - 2*y + 2*z );
    BaseClass::m_interpolation_functions[ 2] = xyz*( - 5 + 2*x + 2*y + 2*z );
    BaseClass::m_interpolation_functions[ 3] = ( 1 - x )*yz*( - 3 - 2*x + 2*y + 2*z );
    BaseClass::m_interpolation_functions[ 4] = ( 1 - x )*( 1 - y )*( 1 - z )*( 1 - 2*x - 2*y - 2*z );
    BaseClass::m_interpolation_functions[ 5] = x*( 1 - y )*( 1 - z )*( - 1 + 2*x - 2*y - 2*z );
    BaseClass::m_interpolation_functions[ 6] = xy*( 1 - z )*( - 3 + 2*x + 2*y - 2*z );
    BaseClass::m_interpolation_functions[ 7] = ( 1 - x )*y*( 1 - z )*( - 1 - 2*x + 2*y - 2*z );
    BaseClass::m_interpolation_functions[ 8] = 4*zx*( 1 - x )*( 1 - y );
    BaseClass::m_interpolation_functions[ 9] = 4*xyz*( 1 - y );
    BaseClass::m_interpolation_functions[10] = 4*xyz*( 1 - x );
    BaseClass::m_interpolation_functions[11] = ( 1 - x )*4*yz*( 1 - y );
    BaseClass::m_interpolation_functions[12] = 4*x*( 1 - x )*( 1 - y )*( 1 - z );
    BaseClass::m_interpolation_functions[13] = 4*xy*( 1 - y )*( 1 - z );
    BaseClass::m_interpolation_functions[14] = 4*xy*( 1 - x )*( 1 - z );
    BaseClass::m_interpolation_functions[15] = ( 1 - x )*4*y*( 1 - y )*( 1 - z );
    BaseClass::m_interpolation_functions[16] = ( 1 - x )*( 1 - y )*4*z*( 1 - z );
    BaseClass::m_interpolation_functions[17] = ( 1 - y )*4*zx*( 1 - z );
    BaseClass::m_interpolation_functions[18] = 4*xyz*( 1 - z );
    BaseClass::m_interpolation_functions[19] = ( 1 - x )*4*yz*( 1 - z );
}

/*===========================================================================*/
/**
 *  @brief  Calculates the differential functions in the local coordinate.
 */
/*===========================================================================*/
template <typename T>
inline void QuadraticHexahedralCell<T>::calculate_differential_function( void )
{
    const float x = BaseClass::m_local_point[0];
    const float y = BaseClass::m_local_point[1];
    const float z = BaseClass::m_local_point[2];

    //const float xy = x * y;
    //const float yz = y * z;
    //const float zx = z * x;

    // dNdx
    BaseClass::m_differential_functions[ 0] =  -(1-y)*z*(2*z-2*y-2*x-1)-2*(1-x)*(1-y)*z;
    BaseClass::m_differential_functions[ 1] =  (1-y)*z*(2*z-2*y+2*x-3)+2*x*(1-y)*z;
    BaseClass::m_differential_functions[ 2] =  y*z*(2*z+2*y+2*x-5)+2*x*y*z;
    BaseClass::m_differential_functions[ 3] =  -y*z*(2*z+2*y-2*x-3)-2*(1-x)*y*z;
    BaseClass::m_differential_functions[ 4] =  -(1-y)*(-2*z-2*y-2*x+1)*(1-z)-2*(1-x)*(1-y)*(1-z);
    BaseClass::m_differential_functions[ 5] =  (1-y)*(-2*z-2*y+2*x-1)*(1-z)+2*x*(1-y)*(1-z);
    BaseClass::m_differential_functions[ 6] =  y*(-2*z+2*y+2*x-3)*(1-z)+2*x*y*(1-z);
    BaseClass::m_differential_functions[ 7] =  -y*(-2*z+2*y-2*x-1)*(1-z)-2*(1-x)*y*(1-z);
    BaseClass::m_differential_functions[ 8] =  4*(1-x)*(1-y)*z-4*x*(1-y)*z;
    BaseClass::m_differential_functions[ 9] =  4*(1-y)*y*z;
    BaseClass::m_differential_functions[10] =  4*(1-x)*y*z-4*x*y*z;
    BaseClass::m_differential_functions[11] =  -4*(1-y)*y*z;
    BaseClass::m_differential_functions[12] =  4*(1-x)*(1-y)*(1-z)-4*x*(1-y)*(1-z);
    BaseClass::m_differential_functions[13] =  4*(1-y)*y*(1-z);
    BaseClass::m_differential_functions[14] =  4*(1-x)*y*(1-z)-4*x*y*(1-z);
    BaseClass::m_differential_functions[15] =  -4*(1-y)*y*(1-z);
    BaseClass::m_differential_functions[16] =  -4*(1-y)*(1-z)*z;
    BaseClass::m_differential_functions[17] =  4*(1-y)*(1-z)*z;
    BaseClass::m_differential_functions[18] =  4*y*(1-z)*z;
    BaseClass::m_differential_functions[19] =  -4*y*(1-z)*z;

    // dNdy
    BaseClass::m_differential_functions[20] =  -(1-x)*z*(2*z-2*y-2*x-1)-2*(1-x)*(1-y)*z;
    BaseClass::m_differential_functions[21] =  -x*z*(2*z-2*y+2*x-3)-2*x*(1-y)*z;
    BaseClass::m_differential_functions[22] =  x*z*(2*z+2*y+2*x-5)+2*x*y*z;
    BaseClass::m_differential_functions[23] =  (1-x)*z*(2*z+2*y-2*x-3)+2*(1-x)*y*z;
    BaseClass::m_differential_functions[24] =  -(1-x)*(-2*z-2*y-2*x+1)*(1-z)-2*(1-x)*(1-y)*(1-z);
    BaseClass::m_differential_functions[25] =  -x*(-2*z-2*y+2*x-1)*(1-z)-2*x*(1-y)*(1-z);
    BaseClass::m_differential_functions[26] =  x*(-2*z+2*y+2*x-3)*(1-z)+2*x*y*(1-z);
    BaseClass::m_differential_functions[27] =  (1-x)*(-2*z+2*y-2*x-1)*(1-z)+2*(1-x)*y*(1-z);
    BaseClass::m_differential_functions[28] =  -4*(1-x)*x*z;
    BaseClass::m_differential_functions[29] =  4*x*(1-y)*z-4*x*y*z;
    BaseClass::m_differential_functions[30] =  4*(1-x)*x*z;
    BaseClass::m_differential_functions[31] =  4*(1-x)*(1-y)*z-4*(1-x)*y*z;
    BaseClass::m_differential_functions[32] =  -4*(1-x)*x*(1-z);
    BaseClass::m_differential_functions[33] =  4*x*(1-y)*(1-z)-4*x*y*(1-z);
    BaseClass::m_differential_functions[34] =  4*(1-x)*x*(1-z);
    BaseClass::m_differential_functions[35] =  4*(1-x)*(1-y)*(1-z)-4*(1-x)*y*(1-z);
    BaseClass::m_differential_functions[36] =  -4*(1-x)*(1-z)*z;
    BaseClass::m_differential_functions[37] =  -4*x*(1-z)*z;
    BaseClass::m_differential_functions[38] =  4*x*(1-z)*z;
    BaseClass::m_differential_functions[39] =  4*(1-x)*(1-z)*z;

    // dNdz 
    BaseClass::m_differential_functions[40] =  (1-x)*(1-y)*(2*z-2*y-2*x-1)+2*(1-x)*(1-y)*z;
    BaseClass::m_differential_functions[41] =  x*(1-y)*(2*z-2*y+2*x-3)+2*x*(1-y)*z;
    BaseClass::m_differential_functions[42] =  x*y*(2*z+2*y+2*x-5)+2*x*y*z;
    BaseClass::m_differential_functions[43] =  (1-x)*y*(2*z+2*y-2*x-3)+2*(1-x)*y*z;
    BaseClass::m_differential_functions[44] =  -2*(1-x)*(1-y)*(1-z)-(1-x)*(1-y)*(-2*z-2*y-2*x+1);
    BaseClass::m_differential_functions[45] =  -2*x*(1-y)*(1-z)-x*(1-y)*(-2*z-2*y+2*x-1);
    BaseClass::m_differential_functions[46] =  -2*x*y*(1-z)-x*y*(-2*z+2*y+2*x-3);
    BaseClass::m_differential_functions[47] =  -2*(1-x)*y*(1-z)-(1-x)*y*(-2*z+2*y-2*x-1);
    BaseClass::m_differential_functions[48] =  4*(1-x)*x*(1-y);
    BaseClass::m_differential_functions[49] =  4*x*(1-y)*y;
    BaseClass::m_differential_functions[50] =  4*(1-x)*x*y;
    BaseClass::m_differential_functions[51] =  4*(1-x)*(1-y)*y;
    BaseClass::m_differential_functions[52] =  -4*(1-x)*x*(1-y);
    BaseClass::m_differential_functions[53] =  -4*x*(1-y)*y;
    BaseClass::m_differential_functions[54] =  -4*(1-x)*x*y;
    BaseClass::m_differential_functions[55] =  -4*(1-x)*(1-y)*y;
    BaseClass::m_differential_functions[56] =  4*(1-x)*(1-y)*(1-z)-4*(1-x)*(1-y)*z;
    BaseClass::m_differential_functions[57] =  4*x*(1-y)*(1-z)-4*x*(1-y)*z;
    BaseClass::m_differential_functions[58] =  4*x*y*(1-z)-4*x*y*z;
    BaseClass::m_differential_functions[59] =  4*(1-x)*y*(1-z)-4*(1-x)*y*z;
}

template <typename T>
inline const kvs::Matrix33f QuadraticHexahedralCell<T>::get_transposed_Jacobi_matrix( void ) const
{
    const kvs::UInt32 nnodes = NumberOfNodes;
    const float* dNdx = BaseClass::m_differential_functions;
    const float* dNdy = BaseClass::m_differential_functions + nnodes;
    const float* dNdz = BaseClass::m_differential_functions + nnodes * 2;
    const kvs::Vector3f* V = BaseClass::m_vertices;

    float dXdx = 0;
    for( size_t i = 0 ; i < 20 ; i++) dXdx += dNdx[i]*V[i].x();

    float dYdx = 0;
    for( size_t i = 0 ; i < 20 ; i++) dYdx += dNdx[i]*V[i].y();

    float dZdx = 0;
    for( size_t i = 0 ; i < 20 ; i++) dZdx += dNdx[i]*V[i].z();


    float dXdy = 0;
    for( size_t i = 0 ; i < 20 ; i++) dXdy += dNdy[i]*V[i].x();

    float dYdy = 0;
    for( size_t i = 0 ; i < 20 ; i++) dYdy += dNdy[i]*V[i].y();

    float dZdy = 0;
    for( size_t i = 0 ; i < 20 ; i++) dZdy += dNdy[i]*V[i].z();


    float dXdz = 0;    
    for( size_t i = 0 ; i < 20 ; i++) dXdz += dNdz[i]*V[i].x();

    float dYdz = 0;
    for( size_t i = 0 ; i < 20 ; i++) dYdz += dNdz[i]*V[i].y();

    float dZdz = 0;
    for( size_t i = 0 ; i < 20 ; i++) dZdz += dNdz[i]*V[i].z();

    return( kvs::Matrix33f( dXdx, dYdx, dZdx, dXdy, dYdy, dZdy, dXdz, dYdz, dZdz ) );
}

template <typename T>
inline const kvs::Vector3f QuadraticHexahedralCell<T>::convert_local_to_global( void ) const
{
    const float*         N = BaseClass::m_interpolation_functions;
    const kvs::Vector3f* V = BaseClass::m_vertices;

    float X = 0;
    for( size_t i = 0 ; i < 20 ; i++) X += N[i] * V[i].x();

    float Y = 0;
    for( size_t i = 0 ; i < 20 ; i++) Y += N[i] * V[i].y();

    float Z = 0;
    for( size_t i = 0 ; i < 20 ; i++) Z += N[i] * V[i].z();

    return( kvs::Vector3f( X, Y, Z ) );
}

} // end of namespace kvs

#endif // KVS__QUADRATIC_HEXAHEDRAL_CELL_H_INCLUDE
