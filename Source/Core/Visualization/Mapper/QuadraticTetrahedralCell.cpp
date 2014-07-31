/****************************************************************************/
/**
 *  @file   QuadraticTetrahedralCell.cpp
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
/****************************************************************************/
#include "QuadraticTetrahedralCell.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Constructs a new QuadraticTetrahedralCell class.
 *  @param  volume [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
QuadraticTetrahedralCell::QuadraticTetrahedralCell(
    const kvs::UnstructuredVolumeObject* volume ):
    kvs::CellBase( volume )
{
    // Set the initial interpolation functions and differential functions.
    this->interpolationFunctions( BaseClass::localPoint() );
    this->differentialFunctions( BaseClass::localPoint() );
}

/*===========================================================================*/
/**
 *  @brief  Destroys the QuadraticTetrahedralCell class.
 */
/*===========================================================================*/
QuadraticTetrahedralCell::~QuadraticTetrahedralCell()
{
}

/*==========================================================================*/
/**
 *  @brief  Calculates the interpolation functions in the local coordinate.
 *  @return point [in] point in the local coordinate
 */
/*==========================================================================*/
const kvs::Real32* QuadraticTetrahedralCell::interpolationFunctions( const kvs::Vec3& point ) const
{
    const float x = point[0];
    const float y = point[1];
    const float z = point[2];

    const float xy = x * y;
    const float yz = y * z;
    const float zx = z * x;

    kvs::Real32* N = BaseClass::interpolationFunctions();
    N[0] = 2.0f * ( 1.0f - x - y - z ) * ( 0.5f - x - y - z );
    N[1] = 2.0f *  x * ( x - 0.5f );
    N[2] = 2.0f *  z * ( z - 0.5f );
    N[3] = 2.0f *  y * ( y - 0.5f );
    N[4] = 4.0f *  x * ( 1.0f - x - y - z );
    N[5] = 4.0f *  z * ( 1.0f - x - y - z );
    N[6] = 4.0f *  y * ( 1.0f - x - y - z );
    N[7] = 4.0f * zx;
    N[8] = 4.0f * yz;
    N[9] = 4.0f * xy;

    return N;
}

/*==========================================================================*/
/**
 *  @brief  Calculates the differential functions in the local coordinate.
 *  @return point [in] point in the local coordinate
 */
/*==========================================================================*/
const kvs::Real32* QuadraticTetrahedralCell::differentialFunctions( const kvs::Vec3& point ) const
{
    const float x = point.x();
    const float y = point.y();
    const float z = point.z();

    const size_t nnodes = BaseClass::numberOfCellNodes();
    kvs::Real32* dN = BaseClass::differentialFunctions();
    kvs::Real32* dNdx = dN;
    kvs::Real32* dNdy = dNdx + nnodes;
    kvs::Real32* dNdz = dNdy + nnodes;

    dNdx[0] =  4 * ( x + y + z ) - 3;
    dNdx[1] =  4 * x - 1;
    dNdx[2] =  0;
    dNdx[3] =  0;
    dNdx[4] =  4 * ( 1 - 2 * x - y - z );
    dNdx[5] = -4 * z;
    dNdx[6] = -4 * y;
    dNdx[7] =  4 * z;
    dNdx[8] =  0;
    dNdx[9] =  4 * y;

    dNdy[0] =  4 * ( x + y + z ) - 3;
    dNdy[1] =  0;
    dNdy[2] =  0;
    dNdy[3] =  4 * y - 1;
    dNdy[4] = -4 * x;
    dNdy[5] = -4 * z;
    dNdy[6] =  4 * ( 1 - x - 2 * y - z );
    dNdy[7] =  0;
    dNdy[8] =  4 * z;
    dNdy[9] =  4 * x;

    dNdz[20] =  4 * ( x + y + z ) - 3;
    dNdz[21] =  0;
    dNdz[22] =  4 * z - 1;
    dNdz[23] =  0;
    dNdz[24] = -4 * x;
    dNdz[25] =  4 * ( 1 - x - y - 2 * z );
    dNdz[26] = -4 * y;
    dNdz[27] =  4 * x;
    dNdz[28] =  4 * y;
    dNdz[29] =  0;

    return dN;
}

/*===========================================================================*/
/**
 *  @brief  Returns the sampled point randomly.
 *  @return coordinate value of the sampled point
 */
/*===========================================================================*/
const kvs::Vec3 QuadraticTetrahedralCell::randomSampling() const
{
    // Generate a point in the local coordinate.
    const float s = BaseClass::randomNumber();
    const float t = BaseClass::randomNumber();
    const float u = BaseClass::randomNumber();

    kvs::Vec3 point;
    if ( s + t + u <= 1.0f )
    {
        point[0] = s;
        point[1] = t;
        point[2] = u;
    }
    else if ( s - t + u >= 1.0f )
    {
        // Revise the point.
        point[0] = -u + 1.0f;
        point[1] = -s + 1.0f;
        point[2] =  t;
    }
    else if ( s + t - u >= 1.0f )
    {
        // Revise the point.
        point[0] = -s + 1.0f;
        point[1] = -t + 1.0f;
        point[2] =  u;
    }
    else if ( -s + t + u >= 1.0f )
    {
        // Revise the point.
        point[0] = -u + 1.0f;
        point[1] =  s;
        point[2] = -t + 1.0f;
    }
    else
    {
        // Revise the point.
        point[0] =   0.5f * s - 0.5f * t - 0.5f * u + 0.5f;
        point[1] = - 0.5f * s + 0.5f * t - 0.5f * u + 0.5f;
        point[2] = - 0.5f * s - 0.5f * t + 0.5f * u + 0.5f;
    }

    BaseClass::setLocalPoint( point );
    BaseClass::m_global_point = BaseClass::transformLocalToGlobal( point );

    return BaseClass::m_global_point;
}

/*===========================================================================*/
/**
 *  @brief  Returns the volume of the cell.
 *  @return volume of the cell
 */
/*===========================================================================*/
const kvs::Real32 QuadraticTetrahedralCell::volume() const
{
    const kvs::Vec3 v0(   0,  0,  0 );
    const kvs::Vec3 v1(   1,  0,  0 );
    const kvs::Vec3 v2(   0,  0,  1 );
    const kvs::Vec3 v3(   0,  1,  0 );
    const kvs::Vec3 v4( 0.5,  0,  0 );
    const kvs::Vec3 v5(   0,  0,0.5 );
    const kvs::Vec3 v6(   0,0.5,  0 );
    const kvs::Vec3 v7( 0.5,  0,0.5 );
    const kvs::Vec3 v8(   0,0.5,0.5 );
    const kvs::Vec3 v9( 0.5,0.5,  0 );

    const kvs::Vec3 c[8] = {
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
        BaseClass::setLocalPoint( c[i] );
        const kvs::Mat3 J = BaseClass::JacobiMatrix();
        const float metric_element = J.determinant();

        sum_metric += kvs::Math::Abs<float>( metric_element );
    }

    return sum_metric / ( 6.0f * 8.0f );
}

} // end of namespace kvs
