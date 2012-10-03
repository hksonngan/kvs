/****************************************************************************/
/**
 *  @file Matrix22.h
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
#ifndef KVS__MATRIX_22_H_INCLUDE
#define KVS__MATRIX_22_H_INCLUDE

#include <iostream>
#include <kvs/Assert>
#include <kvs/Math>
#include <kvs/Vector2>


namespace kvs
{

/*==========================================================================*/
/**
 *  2x2 matrix class.
 */
/*==========================================================================*/
template<typename T>
class Matrix22
{
private:
    Vector2<T> m_rows[2]; ///< Row vectors.

public:
    static const Matrix22 Zero();
    static const Matrix22 Identity();
    static const Matrix22 Diagonal( const T x );
    static const Matrix22 All( const T x );

public:
    Matrix22();
    Matrix22(
        const T a00, const T a01,
        const T a10, const T a11 );
    Matrix22(
        const Vector2<T>& v0,
        const Vector2<T>& v1 );
    explicit Matrix22( const T elements[4] );

public:
    void set(
        const T a00, const T a01,
        const T a10, const T a11 );
    void set(
        const Vector2<T>& v0,
        const Vector2<T>& v1 );
    void set( const T elements[4] );

    void zero();
    void identity();
    void swap( Matrix22& other );

public:
    const Matrix22 transpose() const;
    Matrix22&      transpose();

    const Matrix22 inverse( T* determinant = 0 ) const;
    Matrix22&      inverse( T* determinant = 0 );

public:
    void print() const;
    T trace() const;
    T determinant() const;

public:
    const Vector2<T>& operator []( const size_t index ) const;
    Vector2<T>&       operator []( const size_t index );

public:
    Matrix22& operator +=( const Matrix22& rhs );
    Matrix22& operator -=( const Matrix22& rhs );
    Matrix22& operator *=( const Matrix22& rhs );
    Matrix22& operator *=( const T rhs );
    Matrix22& operator /=( const T rhs );

    const Matrix22 operator -() const;

public:
    friend bool operator ==( const Matrix22& lhs, const Matrix22& rhs )
    {
        return lhs[0] == rhs[0] &&
               lhs[1] == rhs[1];
    }

    friend bool operator !=( const Matrix22& lhs, const Matrix22& rhs )
    {
        return !( lhs == rhs );
    }

    friend const Matrix22 operator +( const Matrix22& lhs, const Matrix22& rhs )
    {
        return Matrix22( lhs ) += rhs;
    }

    friend const Matrix22 operator -( const Matrix22& lhs, const Matrix22& rhs )
    {
        return Matrix22( lhs ) -= rhs;
    }

    friend const Matrix22 operator *( const Matrix22& lhs, const Matrix22& rhs )
    {
        return Matrix22( lhs ) *= rhs;
    }

    friend const Vector2<T> operator *( const Matrix22& lhs, const Vector2<T>& rhs )
    {
        return Vector2<T>(
            lhs[0].dot( rhs ),
            lhs[1].dot( rhs ) );
    }

    friend const Vector2<T> operator *( const Vector2<T>& lhs, const Matrix22& rhs )
    {
        return Vector2<T>(
            lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0],
            lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1] );
    }

    friend const Matrix22 operator *( const Matrix22& lhs, const T rhs )
    {
        return Matrix22( lhs ) *= rhs;
    }

    friend const Matrix22 operator *( const T lhs, const Matrix22& rhs )
    {
        return rhs * lhs;
    }

    friend const Matrix22 operator /( const Matrix22& lhs, const T rhs )
    {
        return Matrix22( lhs ) /= rhs;
    }

    friend std::ostream& operator <<( std::ostream& os, const Matrix22& rhs )
    {
        return os << rhs[0] << "\n" << rhs[1];
    }

public:
    // Will be removed.
    explicit Matrix22( const T a )
    {
        *this = All( a );
    }

    void set( const T a )
    {
        *this = All( a );
    }
};

/*==========================================================================*/
/**
 *  Type definition.
 */
/*==========================================================================*/
typedef Matrix22<float>  Matrix22f;
typedef Matrix22<double> Matrix22d;
typedef Matrix22<float>  Mat2;


template<typename T>
const Matrix22<T> Matrix22<T>::Identity()
{
    return Matrix22( 1, 0,
                     0, 1 );
}

template<typename T>
const Matrix22<T> Matrix22<T>::Zero()
{
    return Matrix22( 0, 0,
                     0, 0 );
}

template<typename T>
const Matrix22<T> Matrix22<T>::All( const T x )
{
    return Matrix22( x, x,
                     x, x );
}

template<typename T>
const Matrix22<T> Matrix22<T>::Diagonal( const T x )
{
    return Identity() * x;
}

/*==========================================================================*/
/**
 *  Constructs a new Matrix22.
 */
/*==========================================================================*/
template<typename T>
inline Matrix22<T>::Matrix22()
{
    this->zero();
};

/*==========================================================================*/
/**
 *  Constructs a new Matrix22.
 *
 *  @param a00 [in] Element.
 *  @param a01 [in] Element.
 *  @param a10 [in] Element.
 *  @param a11 [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline Matrix22<T>::Matrix22(
    const T a00, const T a01,
    const T a10, const T a11 )
{
    this->set(
        a00, a01,
        a10, a11 );
}

/*==========================================================================*/
/**
 *  Constructs a new Matrix22.
 *
 *  @param v0 [in] Vector2.
 *  @param v1 [in] Vector2.
 */
/*==========================================================================*/
template<typename T>
inline Matrix22<T>::Matrix22(
    const Vector2<T>& v0,
    const Vector2<T>& v1 )
{
    this->set( v0, v1 );
}

/*==========================================================================*/
/**
 *  Constructs a new Matrix22.
 *
 *  @param elements [in] Array of elements.
 */
/*==========================================================================*/
template<typename T>
inline Matrix22<T>::Matrix22( const T elements[4] )
{
    this->set( elements );
}

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param a00 [in] Element.
 *  @param a01 [in] Element.
 *  @param a10 [in] Element.
 *  @param a11 [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::set(
    const T a00, const T a01,
    const T a10, const T a11 )
{
    m_rows[0].set( a00, a01 );
    m_rows[1].set( a10, a11 );
}

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param v0 [in] Vector2.
 *  @param v1 [in] Vector2.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::set(
    const Vector2<T>& v0,
    const Vector2<T>& v1 )
{
    m_rows[0] = v0;
    m_rows[1] = v1;
}

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param elements [in] Array of elements.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::set( const T elements[4] )
{
    m_rows[0].set( elements     );
    m_rows[1].set( elements + 2 );
}

/*==========================================================================*/
/**
 *  Sets the elements to zero.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::zero()
{
    *this = Zero();
}

/*==========================================================================*/
/**
 *  Sets this matrix to an identity matrix.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::identity()
{
    *this = Identity();
}

/*==========================================================================*/
/**
 *  Swaps this and other.
 *
 *  @param other [in,out] Matrix22.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::swap( Matrix22& other )
{
    m_rows[0].swap( other[0] );
    m_rows[1].swap( other[1] );
}

/*==========================================================================*/
/**
 *  Copies this and transposes it.
 *
 *  @return Transposed matrix.
 */
/*==========================================================================*/
template<typename T>
inline const Matrix22<T> Matrix22<T>::transpose() const
{
    Matrix22 result( *this );
    result.transpose();
    return result;
}

/*==========================================================================*/
/**
 *  Transposes this matrix.
 *
 *  @return Transposed matrix.
 */
/*==========================================================================*/
template<typename T>
inline Matrix22<T>& Matrix22<T>::transpose()
{
    std::swap( m_rows[0][1], m_rows[1][0] );
    return *this;
}

/*==========================================================================*/
/**
 *  Copies this and inverts it.
 *  @param  determinant [out] calculated determinant
 *  @return Inverse matrix.
 */
/*==========================================================================*/
template<typename T>
inline const Matrix22<T> Matrix22<T>::inverse( T* determinant ) const
{
    Matrix22 result( *this );
    result.inverse( determinant );
    return result;
}

/*==========================================================================*/
/**
 *  Inverts this matrix.
 *  @param  determinant [out] calculated determinant
 *  @return Inverse matrix.
 */
/*==========================================================================*/
template<typename T>
inline Matrix22<T>& Matrix22<T>::inverse( T* determinant )
{
    const T det22 = m_rows[0][0] * m_rows[1][1] - m_rows[0][1] * m_rows[1][0];

    if ( determinant ) *determinant = det22;

    // Inverse.
    this->set(
        +m_rows[1][1], -m_rows[0][1],
        -m_rows[1][0], +m_rows[0][0] );

    const T det_inverse = static_cast<T>( 1.0 / det22 );
    ( *this ) *= det_inverse;
    return *this;
}

/*==========================================================================*/
/**
 *  Prints the elements of this.
 */
/*==========================================================================*/
template<typename T>
inline void Matrix22<T>::print() const
{
    std::cout << *this << std::endl;
}

/*==========================================================================*/
/**
 *  Calculates the trace of this matrix.
 *
 *  @return Trace of this matrix.
 */
/*==========================================================================*/
template<typename T>
inline T Matrix22<T>::trace() const
{
    return m_rows[0][0] + m_rows[1][1];
}

/*==========================================================================*/
/**
 *  Calculates the determinant of this matrix.
 *
 *  @return Determinant of this matrix.
 */
/*==========================================================================*/
template<typename T>
inline T Matrix22<T>::determinant() const
{
    const T det22 = m_rows[0][0] * m_rows[1][1] - m_rows[0][1] * m_rows[1][0];
    return det22;
}

template<typename T>
inline const Vector2<T>& Matrix22<T>::operator []( const size_t index ) const
{
    KVS_ASSERT( index < 2 );
    return m_rows[ index ];
}

template<typename T>
inline Vector2<T>& Matrix22<T>::operator []( const size_t index )
{
    KVS_ASSERT( index < 2 );
    return m_rows[ index ];
}

template<typename T>
inline Matrix22<T>& Matrix22<T>::operator +=( const Matrix22& rhs )
{
    m_rows[0] += rhs[0];
    m_rows[1] += rhs[1];
    return *this;
}

template<typename T>
inline Matrix22<T>& Matrix22<T>::operator -=( const Matrix22& rhs )
{
    m_rows[0] -= rhs[0];
    m_rows[1] -= rhs[1];
    return *this;
}

template<typename T>
inline Matrix22<T>& Matrix22<T>::operator *=( const Matrix22& rhs )
{
    this->set(
        m_rows[0][0] * rhs[0][0] + m_rows[0][1] * rhs[1][0],
        m_rows[0][0] * rhs[0][1] + m_rows[0][1] * rhs[1][1],
        m_rows[1][0] * rhs[0][0] + m_rows[1][1] * rhs[1][0],
        m_rows[1][0] * rhs[0][1] + m_rows[1][1] * rhs[1][1] );
    return *this;
}

template<typename T>
inline Matrix22<T>& Matrix22<T>::operator *=( const T rhs )
{
    m_rows[0] *= rhs;
    m_rows[1] *= rhs;
    return *this;
}

template<typename T>
inline Matrix22<T>& Matrix22<T>::operator /=( const T rhs )
{
    m_rows[0] /= rhs;
    m_rows[1] /= rhs;
    return *this;
}

template<typename T>
inline const Matrix22<T> Matrix22<T>::operator -() const
{
    return Matrix22( *this ) *= T( -1 );
}

} // end of namespace kvs

#endif // KVS__MATRIX_22_H_INCLUDE
