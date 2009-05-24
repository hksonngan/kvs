/****************************************************************************/
/**
 *  @file TetrahedralCell.h
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
#ifndef KVS__TETRAHEDRAL_CELL_H_INCLUDE
#define KVS__TETRAHEDRAL_CELL_H_INCLUDE

#include <kvs/Type>
#include <kvs/Vector4>
#include <kvs/Matrix44>
#include <kvs/UnstructuredVolumeObject>
#include "CellBase.h"


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  Tetrahedral cell class.
 */
/*===========================================================================*/
template <typename T>
class TetrahedralCell : public kvs::CellBase<T>
{
public:

    enum { NumberOfNodes = kvs::UnstructuredVolumeObject::Tetrahedra };

public:

    typedef kvs::CellBase<T> BaseClass;

private:

    // interpolated scalar value: S(X) = P x + Q y + R z + C
    kvs::Vector3f m_coefficients; ///< coefficient values = {P,Q,R}
    kvs::Real32   m_constant;     ///< constant value = {C}

public:

    TetrahedralCell( const kvs::UnstructuredVolumeObject* volume );

    virtual ~TetrahedralCell( void );

public:

    void attachCell( const kvs::UInt32 cell );

    void attachPoint( const kvs::Vector3f& point );

    const kvs::Vector3f randomSampling( void );

    const kvs::Real32 volume( void );

    const kvs::Real32 averagedScalar( void );

    const kvs::Real32 scalar( void );

    const kvs::Vector3f gradient( void );
};

/*===========================================================================*/
/**
 *  @brief  Constructs a new TetrahedralCell class.
 *  @param  volume [in] pointer to the unstructured volume object
 */
/*===========================================================================*/
template <typename T>
inline TetrahedralCell<T>::TetrahedralCell( const kvs::UnstructuredVolumeObject* volume ):
    kvs::CellBase<T>( volume ),
    m_coefficients( 0, 0, 0 ),
    m_constant( 0 )
{
}

/*===========================================================================*/
/**
 *  @brief  Destructs the unstructured volume object.
 */
/*===========================================================================*/
template <typename T>
inline TetrahedralCell<T>::~TetrahedralCell( void )
{
}

/*===========================================================================*/
/**
 *  @brief  Attach a cell.
 *  @param  index [in] index of the cell
 */
/*===========================================================================*/
template <typename T>
inline void TetrahedralCell<T>::attachCell( const kvs::UInt32 index )
{
    const kvs::UnstructuredVolumeObject* volume = BaseClass::m_reference_volume;

    const kvs::UInt32* const connections = volume->connections().pointer();
    const kvs::Real32* const coords      = volume->coords().pointer();
    const T* const values = static_cast<const T*>( volume->values().pointer() );

    const kvs::UInt32 nnodes = NumberOfNodes;
    const kvs::UInt32 connection_index = nnodes * index;

    const kvs::UInt32 node_index[nnodes] =
    {
        connections[ connection_index     ],
        connections[ connection_index + 1 ],
        connections[ connection_index + 2 ],
        connections[ connection_index + 3 ]
    };

    const kvs::UInt32 coord_index[4] =
    {
        3 * node_index[0],
        3 * node_index[1],
        3 * node_index[2],
        3 * node_index[3]
    };

    BaseClass::m_vertices[0].set( coords[ coord_index[0] ], coords[ coord_index[0] + 1 ], coords[ coord_index[0] + 2 ] );
    BaseClass::m_vertices[1].set( coords[ coord_index[1] ], coords[ coord_index[1] + 1 ], coords[ coord_index[1] + 2 ] );
    BaseClass::m_vertices[2].set( coords[ coord_index[2] ], coords[ coord_index[2] + 1 ], coords[ coord_index[2] + 2 ] );
    BaseClass::m_vertices[3].set( coords[ coord_index[3] ], coords[ coord_index[3] + 1 ], coords[ coord_index[3] + 2 ] );

    BaseClass::m_scalars[0] = values[ node_index[0] ];
    BaseClass::m_scalars[1] = values[ node_index[1] ];
    BaseClass::m_scalars[2] = values[ node_index[2] ];
    BaseClass::m_scalars[3] = values[ node_index[3] ];

    // ***
    kvs::Matrix44<kvs::Real32> A(
        BaseClass::m_vertices[0].x(), BaseClass::m_vertices[0].y(), BaseClass::m_vertices[0].z(), 1.0f,
        BaseClass::m_vertices[1].x(), BaseClass::m_vertices[1].y(), BaseClass::m_vertices[1].z(), 1.0f,
        BaseClass::m_vertices[2].x(), BaseClass::m_vertices[2].y(), BaseClass::m_vertices[2].z(), 1.0f,
        BaseClass::m_vertices[3].x(), BaseClass::m_vertices[3].y(), BaseClass::m_vertices[3].z(), 1.0f );

    const kvs::Vector4f b(
        static_cast<float>( BaseClass::m_scalars[0] ),
        static_cast<float>( BaseClass::m_scalars[1] ),
        static_cast<float>( BaseClass::m_scalars[2] ),
        static_cast<float>( BaseClass::m_scalars[3] ) );

    const kvs::Vector4f weight( A.inverse() * b );

    m_coefficients.set( weight[0], weight[1], weight[2] );
    m_constant = weight[3];
}

/*===========================================================================*/
/**
 *  @brief  Attach a point in the global coordinate.
 *  @param  point [in] coordinate value in the global
 */
/*===========================================================================*/
template <typename T>
inline void TetrahedralCell<T>::attachPoint( const kvs::Vector3f& point )
{
    BaseClass::set_global_point( point );
}

/*===========================================================================*/
/**
 *  @brief  Returns a volume of the cell.
 *  @return volume of the cell
 */
/*===========================================================================*/
template <typename T>
inline const kvs::Real32 TetrahedralCell<T>::volume( void )
{
    const kvs::Vector3f v01( BaseClass::m_vertices[1] - BaseClass::m_vertices[0] );
    const kvs::Vector3f v02( BaseClass::m_vertices[2] - BaseClass::m_vertices[0] );
    const kvs::Vector3f v03( BaseClass::m_vertices[3] - BaseClass::m_vertices[0] );

    return( kvs::Math::Abs( ( v01.cross( v02 ) ).dot( v03 ) ) * 0.166666f );
}

/*===========================================================================*/
/**
 *  @brief  Returns an average of the scalar values on the nodes.
 *  @return average of the scalar values on the nodes
 */
/*===========================================================================*/
template <typename T>
inline const kvs::Real32 TetrahedralCell<T>::averagedScalar( void )
{
    const kvs::Real32 w = 1.0f / NumberOfNodes;

    return( static_cast<kvs::Real32>(
                BaseClass::m_scalars[0] +
                BaseClass::m_scalars[1] +
                BaseClass::m_scalars[2] +
                BaseClass::m_scalars[3] ) * w );
}

/*===========================================================================*/
/**
 *  @brief  Returns a global point in the cell randomly.
 *  @return global point
 */
/*===========================================================================*/
template <typename T>
const kvs::Vector3f TetrahedralCell<T>::randomSampling( void )
{
    const kvs::Vector3f v0( BaseClass::m_vertices[0] );

    const kvs::Vector3f v01( BaseClass::m_vertices[1] - v0 );
    const kvs::Vector3f v02( BaseClass::m_vertices[2] - v0 );
    const kvs::Vector3f v03( BaseClass::m_vertices[3] - v0 );

    // Generate a point in the local coordinate.
    const float s = BaseClass::random_number();
    const float t = BaseClass::random_number();
    const float u = BaseClass::random_number();

    if ( s + t + u <= 1.0f )
    {
        BaseClass::set_global_point( s * v01 + t * v02 + u * v03 + v0 );
    }

    else if ( s - t + u >= 1.0f )
    {
        // Revise the point.
        const float ss = -u + 1.0f;
        const float tt = -s + 1.0f;
        const float uu =  t;

        BaseClass::set_global_point( ss * v01 + tt * v02 + uu * v03 + v0 );
    }

    else if ( s + t - u >= 1.0f )
    {
        // Revise the point.
        const float ss = -s + 1.0f;
        const float tt = -t + 1.0f;
        const float uu =  u;

        BaseClass::set_global_point( ss * v01 + tt * v02 + uu * v03 + v0 );
    }

    else if ( -s + t + u >= 1.0f )
    {
        // Revise the point.
        const float ss = -u + 1.0f;
        const float tt =  s;
        const float uu = -t + 1.0f;

        BaseClass::set_global_point( ss * v01 + tt * v02 + uu * v03 + v0 );
    }

    else
    {
        // Revise the point.
        const float ss =   0.5f * s - 0.5f * t - 0.5f * u + 0.5f;
        const float tt = - 0.5f * s + 0.5f * t - 0.5f * u + 0.5f;
        const float uu = - 0.5f * s - 0.5f * t + 0.5f * u + 0.5f;

        BaseClass::set_global_point( ss * v01 + tt * v02 + uu * v03 + v0 );
    }

    return( BaseClass::m_global_point );
}

/*===========================================================================*/
/**
 *  @brief  Returns an interpolated scalar value at the attached point.
 *  @return interpolated scalar value
 */
/*===========================================================================*/
template <typename T>
inline const kvs::Real32 TetrahedralCell<T>::scalar( void )
{
    return( BaseClass::m_global_point.dot( m_coefficients ) + m_constant );
}

/*===========================================================================*/
/**
 *  @brief  Returns an interpolated gradient vector at the attached point.
 *  @return interpolated gradient vector
 */
/*===========================================================================*/
template <typename T>
inline const kvs::Vector3f TetrahedralCell<T>::gradient( void )
{
    return( m_coefficients );
}

} // end of namespace kvs

#endif // KVS__TETRAHEDRAL_CELL_H_INCLUDE
