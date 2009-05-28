/*****************************************************************************/
/**
 *  @file   LUSolver.h
 *  @author Naohisa Sakamoto
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
#ifndef KVS__LU_SOLVER_H_INCLUDE
#define KVS__LU_SOLVER_H_INCLUDE

#include "LUDecomposer.h"
#include <kvs/Vector>


namespace kvs
{

/*===========================================================================*/
/**
 *  @brief  LU decomposition solver.
 */
/*===========================================================================*/
template <typename T>
class LUSolver : public kvs::Vector<T>
{
protected:

    kvs::LUDecomposer<T> m_decomposer;

public:

    LUSolver( void )
    {
    }

    LUSolver( const kvs::LUDecomposer<T>& decomposer )
    {
        m_decomposer = decomposer;
    }

    LUSolver( const kvs::Matrix<T>& A, const kvs::Vector<T>& b )
    {
        this->solve( A, b );
    }

    virtual ~LUSolver( void )
    {
    }

public:

    LUSolver<T>& operator = ( const kvs::Vector<T>& v )
    {
        this->setSize( v.size() );
        for( size_t i = 0; i < this->size(); i++ ){ (*this)[i] = v[i]; }

        return( *this );
    }

    const kvs::Vector<T>& solve( const kvs::Vector<T>& b );

    const kvs::Vector<T>& solve( const kvs::Matrix<T>& A, const kvs::Vector<T>& b );
};

} // end of namespace kvs

#endif // KVS__LU_SOLVER_H_INCLUDE
