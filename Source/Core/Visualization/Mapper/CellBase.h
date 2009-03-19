/****************************************************************************/
/**
 *  @file CellBase.h
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
#ifndef KVS_CORE_CELL_BASE_H_INCLUDE
#define KVS_CORE_CELL_BASE_H_INCLUDE

#include <kvs/Type>
#include <kvs/Vector4>
#include <kvs/Matrix44>
#include <kvs/UnstructuredVolumeObject>

namespace kvs
{

template <typename T>
class CellBase
{
protected:

    kvs::Vector3f* m_vertices; ///< coordinates of the nodes
    T*             m_scalars; ///< scalar values of the nodes
    kvs::Real32*   m_interpolation_functions; ///< interpolation functions
    kvs::Real32*   m_differential_functions; ///< differential functions
    kvs::Vector3f  m_global_point; ///< sampling point in the global coordinate
    kvs::Vector3f  m_local_point;  ///< sampling point in the local coordinate

    const kvs::UnstructuredVolumeObject* m_reference_volume; ///< reference unstructured volume

public:

    CellBase( const kvs::UnstructuredVolumeObject* volume );

    virtual ~CellBase( void );

public:

    virtual void attachCell( const kvs::UInt32 cell_index ) = 0;

    virtual void attachPoint( const kvs::Vector3f& point ) = 0;

    virtual const kvs::Vector3f randomSampling( void ) = 0;

    virtual const kvs::Real32 volume( void ) = 0;

    virtual const kvs::Real32 averagedScalar( void ) = 0;

    virtual const kvs::Real32 scalar( void ) = 0;

    virtual const kvs::Vector3f gradient( void ) = 0;

protected:

    void set_local_point( const kvs::Vector3f& local_point );

    void set_global_point( const kvs::Vector3f& global_point );

protected:

    const float random_number( void ) const
    {
        // xorshift RGNs with period at least 2^128 - 1.
        static float t24 = 1.0/16777216.0; /* 0.5**24 */
        static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
        unsigned long t;
        t=(x^(x<<11));
        x=y;y=z;z=w;
        w=(w^(w>>19))^(t^(t>>8));

        return( t24*static_cast<float>(w>>8) );
    }
};

template <typename T>
inline CellBase<T>::CellBase(
    const kvs::UnstructuredVolumeObject* volume ):
    m_global_point( 0, 0, 0 ),
    m_local_point( 0, 0, 0 ),
    m_reference_volume( volume )
{
    const size_t dimension = 3;
    const size_t nnodes = volume->nnodes();
    try
    {
        m_vertices = new kvs::Vector3f [nnodes];
        if ( !m_vertices ) throw "Cannot allocate memory for 'm_vertices'";

        m_scalars  = new T [nnodes];
        if ( !m_scalars ) throw "Cannot allocate memory for 'm_scalars'";

        m_interpolation_functions = new kvs::Real32 [nnodes];
        if ( !m_interpolation_functions ) throw "Cannot allocate memory for 'm_interpolation_functions'";

        m_differential_functions  = new kvs::Real32 [nnodes*dimension];
        if ( !m_differential_functions ) throw "Cannot allocate memory for 'm_differential_functions'";
    }
    catch( char* error_message )
    {
        kvsMessageError( error_message );
        return;
    }
}

template <typename T>
inline CellBase<T>::~CellBase( void )
{
    if ( m_vertices ) delete [] m_vertices;
    if ( m_scalars ) delete [] m_scalars;
    if ( m_interpolation_functions ) delete [] m_interpolation_functions;
    if ( m_differential_functions ) delete [] m_differential_functions;
}

template <typename T>
inline void CellBase<T>::set_local_point( const kvs::Vector3f& local_point )
{
    m_local_point = local_point;
}

template <typename T>
inline void CellBase<T>::set_global_point( const kvs::Vector3f& global_point )
{
    m_global_point = global_point;
}

} // end of namespace kvs

#endif // KVS_CORE_CELL_BASE_H_INCLUDE
