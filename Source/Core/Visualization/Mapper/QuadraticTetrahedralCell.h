/****************************************************************************/
/**
 *  @file QuadraticTetrahedralCell.h
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
#ifndef KVS_CORE_QUADRATIC_TETRAHEDRAL_CELL_H_INCLUDE
#define KVS_CORE_QUADRATIC_TETRAHEDRAL_CELL_H_INCLUDE

#include <kvs/Type>
#include <kvs/Vector4>
#include <kvs/Matrix44>
#include <kvs/UnstructuredVolumeObject>
#include "CellBase.h"


namespace kvs
{

template <typename T>
class QuadraticTetrahedralCell : public kvs::CellBase<T>
{
public:

    enum { NumberOfNodes = kvs::UnstructuredVolumeObject::QuadraticTetrahedra };

public:

    typedef kvs::CellBase<T> BaseClass;

public:

    QuadraticTetrahedralCell( const kvs::UnstructuredVolumeObject* volume );

    virtual ~QuadraticTetrahedralCell( void );

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
inline QuadraticTetrahedralCell<T>::QuadraticTetrahedralCell(
    const kvs::UnstructuredVolumeObject* volume ):
    kvs::CellBase<T>( volume )
{
}

template <typename T>
inline QuadraticTetrahedralCell<T>::~QuadraticTetrahedralCell( void )
{
}

template <typename T>
inline void QuadraticTetrahedralCell<T>::attachCell( const kvs::UInt32 index )
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
        connections[ connection_index + 9 ]
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
        3 * node_index[7],
        3 * node_index[8],
        3 * node_index[9]
    };

    BaseClass::m_vertices[0].set( coords[ coord_index[0] ], coords[ coord_index[0] + 1 ], coords[ coord_index[0] + 2 ] );
    BaseClass::m_vertices[1].set( coords[ coord_index[1] ], coords[ coord_index[1] + 1 ], coords[ coord_index[1] + 2 ] );
    BaseClass::m_vertices[2].set( coords[ coord_index[2] ], coords[ coord_index[2] + 1 ], coords[ coord_index[2] + 2 ] );
    BaseClass::m_vertices[3].set( coords[ coord_index[3] ], coords[ coord_index[3] + 1 ], coords[ coord_index[3] + 2 ] );
    BaseClass::m_vertices[4].set( coords[ coord_index[4] ], coords[ coord_index[4] + 1 ], coords[ coord_index[4] + 2 ] );
    BaseClass::m_vertices[5].set( coords[ coord_index[5] ], coords[ coord_index[5] + 1 ], coords[ coord_index[5] + 2 ] );
    BaseClass::m_vertices[6].set( coords[ coord_index[6] ], coords[ coord_index[6] + 1 ], coords[ coord_index[6] + 2 ] );
    BaseClass::m_vertices[7].set( coords[ coord_index[7] ], coords[ coord_index[7] + 1 ], coords[ coord_index[7] + 2 ] );
    BaseClass::m_vertices[8].set( coords[ coord_index[8] ], coords[ coord_index[8] + 1 ], coords[ coord_index[8] + 2 ] );
    BaseClass::m_vertices[9].set( coords[ coord_index[9] ], coords[ coord_index[9] + 1 ], coords[ coord_index[9] + 2 ] );

    BaseClass::m_scalars[0] = values[ node_index[0] ];
    BaseClass::m_scalars[1] = values[ node_index[1] ];
    BaseClass::m_scalars[2] = values[ node_index[2] ];
    BaseClass::m_scalars[3] = values[ node_index[3] ];
    BaseClass::m_scalars[4] = values[ node_index[4] ];
    BaseClass::m_scalars[5] = values[ node_index[5] ];
    BaseClass::m_scalars[6] = values[ node_index[6] ];
    BaseClass::m_scalars[7] = values[ node_index[7] ];
    BaseClass::m_scalars[8] = values[ node_index[8] ];
    BaseClass::m_scalars[9] = values[ node_index[9] ];
}

template <typename T>
inline void QuadraticTetrahedralCell<T>::attachPoint( const kvs::Vector3f& point )
{
    BaseClass::set_global_point( point );
}

template <typename T>
const kvs::Vector3f QuadraticTetrahedralCell<T>::randomSampling( void )
{
    // Generate a point in the local coordinate.
    const float s = BaseClass::random_number();
    const float t = BaseClass::random_number();
    const float u = BaseClass::random_number();

    kvs::Vector3f local_point;

    if ( s + t + u <= 1.0f )
    {
        BaseClass::set_local_point( kvs::Vector3f( s, t, u ) );
    }

    else if ( s - t + u >= 1.0f )
    {
        // Revise the point.
        const float ss = -u + 1.0f;
        const float tt = -s + 1.0f;
        const float uu =  t;

        BaseClass::set_local_point( kvs::Vector3f( ss, tt, uu ) );
    }

    else if ( s + t - u >= 1.0f )
    {
        // Revise the point.
        const float ss = -s + 1.0f;
        const float tt = -t + 1.0f;
        const float uu =  u;

        BaseClass::set_local_point( kvs::Vector3f( ss, tt, uu ) );
    }

    else if ( -s + t + u >= 1.0f )
    {
        // Revise the point.
        const float ss = -u + 1.0f;
        const float tt =  s;
        const float uu = -t + 1.0f;

        BaseClass::set_local_point( kvs::Vector3f( ss, tt, uu ) );
    }

    else
    {
        // Revise the point.
        const float ss =   0.5f * s - 0.5f * t - 0.5f * u + 0.5f;
        const float tt = - 0.5f * s + 0.5f * t - 0.5f * u + 0.5f;
        const float uu = - 0.5f * s - 0.5f * t + 0.5f * u + 0.5f;

        BaseClass::set_local_point( kvs::Vector3f( ss, tt, uu ) );
    }

    this->calculate_interpolation_function();
    BaseClass::set_global_point( this->convert_local_to_global() );

    return( BaseClass::m_global_point );
}

template <typename T>
inline const kvs::Real32 QuadraticTetrahedralCell<T>::volume( void )
{
    const kvs::Vector3f v0(   0,  0,  0 );
    const kvs::Vector3f v1(   1,  0,  0 );
    const kvs::Vector3f v2(   0,  0,  1 );
    const kvs::Vector3f v3(   0,  1,  0 );
    const kvs::Vector3f v4( 0.5,  0,  0 );
    const kvs::Vector3f v5(   0,  0,0.5 );
    const kvs::Vector3f v6(   0,0.5,  0 );
    const kvs::Vector3f v7( 0.5,  0,0.5 );
    const kvs::Vector3f v8(   0,0.5,0.5 );
    const kvs::Vector3f v9( 0.5,0.5,  0 );

    const kvs::Vector3f c[8] = {
        ( v0 + v4 + v5 + v6 ) * 0.25,
        ( v4 + v1 + v7 + v9 ) * 0.25,
        ( v5 + v7 + v2 + v8 ) * 0.25,
        ( v6 + v9 + v8 + v3 ) * 0.25,
        ( v4 + v7 + v5 + v6 ) * 0.25,
        ( v4 + v9 + v7 + v6 ) * 0.25,
        ( v8 + v6 + v5 + v7 ) * 0.25,
        ( v8 + v7 + v9 + v6 ) * 0.25 };

    float sum_metric = 0;
    for( size_t i = 0 ; i < 8 ; i++ )
    {
        BaseClass::set_local_point( c[i] );
        this->calculate_differential_function();

        const kvs::Matrix33f J = this->get_transposed_Jacobi_matrix();
        const float metric_element = J.determinant();

        sum_metric += kvs::Math::Abs<float>( metric_element );
    }

    return( sum_metric / ( 6.0f * 8.0f ) );
}

template <typename T>
inline const kvs::Real32 QuadraticTetrahedralCell<T>::averagedScalar( void )
{
    const kvs::Real32 w = 1.0f / QuadraticTetrahedralCell::NumberOfNodes;

    return( static_cast<kvs::Real32>(
                BaseClass::m_scalars[0] +
                BaseClass::m_scalars[1] +
                BaseClass::m_scalars[2] +
                BaseClass::m_scalars[3] +
                BaseClass::m_scalars[4] +
                BaseClass::m_scalars[5] +
                BaseClass::m_scalars[6] +
                BaseClass::m_scalars[7] +
                BaseClass::m_scalars[8] +
                BaseClass::m_scalars[9] ) * w );
}

template <typename T>
inline const kvs::Real32 QuadraticTetrahedralCell<T>::scalar( void )
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
                I[7]*s[7] +
                I[8]*s[8] +
                I[9]*s[9] ) );
}

template <typename T>
inline const kvs::Vector3f QuadraticTetrahedralCell<T>::gradient( void )
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
            s[0]*dIdx[0] + s[1]*dIdx[1] + s[2]*dIdx[2] + s[3]*dIdx[3] + s[4]*dIdx[4] +
            s[5]*dIdx[5] + s[6]*dIdx[6] + s[7]*dIdx[7] + s[8]*dIdx[8] + s[9]*dIdx[9] );

    const float dsdy =
        static_cast<float>(
            s[0]*dIdy[0] + s[1]*dIdy[1] + s[2]*dIdy[2] + s[3]*dIdy[3] + s[4]*dIdy[4] +
            s[5]*dIdy[5] + s[6]*dIdy[6] + s[7]*dIdy[7] + s[8]*dIdy[8] + s[9]*dIdy[9] );

    const float dsdz =
        static_cast<float>(
            s[0]*dIdz[0] + s[1]*dIdz[1] + s[2]*dIdz[2] + s[3]*dIdz[3] + s[4]*dIdz[4] +
            s[5]*dIdz[5] + s[6]*dIdz[6] + s[7]*dIdz[7] + s[8]*dIdz[8] + s[9]*dIdz[9] );

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
inline void QuadraticTetrahedralCell<T>::calculate_interpolation_function( void )
{
    const float x = BaseClass::m_local_point[0];
    const float y = BaseClass::m_local_point[1];
    const float z = BaseClass::m_local_point[2];

    const float xy = x * y;
    const float yz = y * z;
    const float zx = z * x;

    BaseClass::m_interpolation_functions[0] = 2.0f * ( 1.0f - x - y - z ) * ( 0.5f - x - y - z );
    BaseClass::m_interpolation_functions[1] = 2.0f *  x * ( x - 0.5f );
    BaseClass::m_interpolation_functions[2] = 2.0f *  z * ( z - 0.5f );
    BaseClass::m_interpolation_functions[3] = 2.0f *  y * ( y - 0.5f );
    BaseClass::m_interpolation_functions[4] = 4.0f *  x * ( 1.0f - x - y - z );
    BaseClass::m_interpolation_functions[5] = 4.0f *  z * ( 1.0f - x - y - z );
    BaseClass::m_interpolation_functions[6] = 4.0f *  y * ( 1.0f - x - y - z );
    BaseClass::m_interpolation_functions[7] = 4.0f * zx;
    BaseClass::m_interpolation_functions[8] = 4.0f * yz;
    BaseClass::m_interpolation_functions[9] = 4.0f * xy;
}

/*==========================================================================*/
/**
 *  Calculates the differential functions in the local coordinate.
 */
/*==========================================================================*/
template <typename T>
inline void QuadraticTetrahedralCell<T>::calculate_differential_function( void )
{
    const float x = BaseClass::m_local_point[0];
    const float y = BaseClass::m_local_point[1];
    const float z = BaseClass::m_local_point[2];

    // dNdx
    BaseClass::m_differential_functions[0] =  4 * ( x + y + z ) - 3;
    BaseClass::m_differential_functions[1] =  4 * x - 1;
    BaseClass::m_differential_functions[2] =  0;
    BaseClass::m_differential_functions[3] =  0;
    BaseClass::m_differential_functions[4] =  4 * ( 1 - 2 * x - y - z );
    BaseClass::m_differential_functions[5] = -4 * z;
    BaseClass::m_differential_functions[6] = -4 * y;
    BaseClass::m_differential_functions[7] =  4 * z;
    BaseClass::m_differential_functions[8] =  0;
    BaseClass::m_differential_functions[9] =  4 * y;

    // dNdy
    BaseClass::m_differential_functions[10] =  4 * ( x + y + z ) - 3;
    BaseClass::m_differential_functions[11] =  0;
    BaseClass::m_differential_functions[12] =  0;
    BaseClass::m_differential_functions[13] =  4 * y - 1;
    BaseClass::m_differential_functions[14] = -4 * x;
    BaseClass::m_differential_functions[15] = -4 * z;
    BaseClass::m_differential_functions[16] =  4 * ( 1 - x - 2 * y - z );
    BaseClass::m_differential_functions[17] =  0;
    BaseClass::m_differential_functions[18] =  4 * z;
    BaseClass::m_differential_functions[19] =  4 * x;

    // dNdz
    BaseClass::m_differential_functions[20] =  4 * ( x + y + z ) - 3;
    BaseClass::m_differential_functions[21] =  0;
    BaseClass::m_differential_functions[22] =  4 * z - 1;
    BaseClass::m_differential_functions[23] =  0;
    BaseClass::m_differential_functions[24] = -4 * x;
    BaseClass::m_differential_functions[25] =  4 * ( 1 - x - y - 2 * z );
    BaseClass::m_differential_functions[26] = -4 * y;
    BaseClass::m_differential_functions[27] =  4 * x;
    BaseClass::m_differential_functions[28] =  4 * y;
    BaseClass::m_differential_functions[29] =  0;
}

template <typename T>
inline const kvs::Matrix33f QuadraticTetrahedralCell<T>::get_transposed_Jacobi_matrix( void ) const
{
    const kvs::UInt32 nnodes = NumberOfNodes;
    const float* dNdx = BaseClass::m_differential_functions;
    const float* dNdy = BaseClass::m_differential_functions + nnodes;
    const float* dNdz = BaseClass::m_differential_functions + nnodes * 2;
    const kvs::Vector3f* V = BaseClass::m_vertices;

    const float dXdx =
        dNdx[0]*V[0].x() + dNdx[1]*V[1].x() + dNdx[2]*V[2].x() + dNdx[3]*V[3].x() + dNdx[4]*V[4].x() +
        dNdx[5]*V[5].x() + dNdx[6]*V[6].x() + dNdx[7]*V[7].x() + dNdx[8]*V[8].x() + dNdx[9]*V[9].x();

    const float dYdx =
        dNdx[0]*V[0].y() + dNdx[1]*V[1].y() + dNdx[2]*V[2].y() + dNdx[3]*V[3].y() + dNdx[4]*V[4].y() +
        dNdx[5]*V[5].y() + dNdx[6]*V[6].y() + dNdx[7]*V[7].y() + dNdx[8]*V[8].y() + dNdx[9]*V[9].y();

    const float dZdx =
        dNdx[0]*V[0].z() + dNdx[1]*V[1].z() + dNdx[2]*V[2].z() + dNdx[3]*V[3].z() + dNdx[4]*V[4].z() +
        dNdx[5]*V[5].z() + dNdx[6]*V[6].z() + dNdx[7]*V[7].z() + dNdx[8]*V[8].z() + dNdx[9]*V[9].z();


    const float dXdy =
        dNdy[0]*V[0].x() + dNdy[1]*V[1].x() + dNdy[2]*V[2].x() + dNdy[3]*V[3].x() + dNdy[4]*V[4].x() +
        dNdy[5]*V[5].x() + dNdy[6]*V[6].x() + dNdy[7]*V[7].x() + dNdy[8]*V[8].x() + dNdy[9]*V[9].x();

    const float dYdy =
        dNdy[0]*V[0].y() + dNdy[1]*V[1].y() + dNdy[2]*V[2].y() + dNdy[3]*V[3].y() + dNdy[4]*V[4].y() +
        dNdy[5]*V[5].y() + dNdy[6]*V[6].y() + dNdy[7]*V[7].y() + dNdy[8]*V[8].y() + dNdy[9]*V[9].y();

    const float dZdy =
        dNdy[0]*V[0].z() + dNdy[1]*V[1].z() + dNdy[2]*V[2].z() + dNdy[3]*V[3].z() + dNdy[4]*V[4].z() +
        dNdy[5]*V[5].z() + dNdy[6]*V[6].z() + dNdy[7]*V[7].z() + dNdy[8]*V[8].z() + dNdy[9]*V[9].z();


    const float dXdz =
        dNdz[0]*V[0].x() + dNdz[1]*V[1].x() + dNdz[2]*V[2].x() + dNdz[3]*V[3].x() + dNdz[4]*V[4].x() +
        dNdz[5]*V[5].x() + dNdz[6]*V[6].x() + dNdz[7]*V[7].x() + dNdz[8]*V[8].x() + dNdz[9]*V[9].x();

    const float dYdz =
        dNdz[0]*V[0].y() + dNdz[1]*V[1].y() + dNdz[2]*V[2].y() + dNdz[3]*V[3].y() + dNdz[4]*V[4].y() +
        dNdz[5]*V[5].y() + dNdz[6]*V[6].y() + dNdz[7]*V[7].y() + dNdz[8]*V[8].y() + dNdz[9]*V[9].y();

    const float dZdz =
        dNdz[0]*V[0].z() + dNdz[1]*V[1].z() + dNdz[2]*V[2].z() + dNdz[3]*V[3].z() + dNdz[4]*V[4].z() +
        dNdz[5]*V[5].z() + dNdz[6]*V[6].z() + dNdz[7]*V[7].z() + dNdz[8]*V[8].z() + dNdz[9]*V[9].z();

    return( kvs::Matrix33f( dXdx, dYdx, dZdx, dXdy, dYdy, dZdy, dXdz, dYdz, dZdz ) );
}

template <typename T>
inline const kvs::Vector3f QuadraticTetrahedralCell<T>::convert_local_to_global( void ) const
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
        N[7] * V[7].x() +
        N[8] * V[8].x() +
        N[9] * V[9].x();

    const float Y =
        N[0] * V[0].y() +
        N[1] * V[1].y() +
        N[2] * V[2].y() +
        N[3] * V[3].y() +
        N[4] * V[4].y() +
        N[5] * V[5].y() +
        N[6] * V[6].y() +
        N[7] * V[7].y() +
        N[8] * V[8].y() +
        N[9] * V[9].y();

    const float Z =
        N[0] * V[0].z() +
        N[1] * V[1].z() +
        N[2] * V[2].z() +
        N[3] * V[3].z() +
        N[4] * V[4].z() +
        N[5] * V[5].z() +
        N[6] * V[6].z() +
        N[7] * V[7].z() +
        N[8] * V[8].z() +
        N[9] * V[9].z();

    return( kvs::Vector3f( X, Y, Z ) );
}

} // end of namespace kvs

#endif // KVS_CORE_QUADRATIC_TETRAHEDRAL_CELL_H_INCLUDE
