/****************************************************************************/
/**
 *  @file Vector4.h
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
#ifndef KVS__VECTOR_4_H_INCLUDE
#define KVS__VECTOR_4_H_INCLUDE

#include <iostream>
#include <kvs/Assert>
#include <kvs/Math>
#include <kvs/Vector2>
#include <kvs/Vector3>


namespace kvs
{

/*==========================================================================*/
/**
 *  4D vector class.
 */
/*==========================================================================*/
template <typename T>
class Vector4
{
private:
    T m_elements[4]; ///< Elements.

public:
    static const Vector4 Zero();
    static const Vector4 All( const T x );

public:
    Vector4();
    Vector4( const T x, const T y, const T z, const T w );
    Vector4( const Vector2<T>& other, const T z , const T w );
    Vector4( const Vector3<T>& other, const T w );
    explicit Vector4( const T elements[4] );

public:
    void set( const T x, const T y, const T z, const T w );
    void set( const Vector2<T>& other, const T z, const T w );
    void set( const Vector3<T>& other, const T w );
    void set( const T elements[4] );

    void zero();
    void swap( Vector4& other );

public:
    T& x();
    const T& x() const;
    T& y();
    const T& y() const;
    T& z();
    const T& z() const;
    T& w();
    const T& w() const;
    const Vector2<T> xy() const;
    const Vector3<T> xyz() const;

public:
    const Vector4 normalized() const;
    void          normalize();

public:
    void print() const;
    double length() const;
    double length2() const;
    T dot( const Vector4& other ) const;

public:
    const T& operator [] ( const size_t index ) const;
    T&       operator [] ( const size_t index );

public:
    Vector4& operator += ( const Vector4& rhs );
    Vector4& operator -= ( const Vector4& rhs );
    Vector4& operator *= ( const Vector4& rhs );
    Vector4& operator *= ( const T rhs );
    Vector4& operator /= ( const Vector4& rhs );
    Vector4& operator /= ( const T rhs );

    const Vector4 operator -() const;

public:
    friend bool operator ==( const Vector4& lhs, const Vector4& rhs )
    {
        return kvs::Math::Equal( lhs[0], rhs[0] ) &&
               kvs::Math::Equal( lhs[1], rhs[1] ) &&
               kvs::Math::Equal( lhs[2], rhs[2] ) &&
               kvs::Math::Equal( lhs[3], rhs[3] );
    }

    friend bool operator !=( const Vector4& lhs, const Vector4& rhs )
    {
        return !( lhs == rhs );
    }

    friend const Vector4 operator +( const Vector4& lhs, const Vector4& rhs )
    {
        return Vector4( lhs ) += rhs;
    }

    friend const Vector4 operator -( const Vector4& lhs, const Vector4& rhs )
    {
        return Vector4( lhs ) -= rhs;
    }

    friend const Vector4 operator *( const Vector4& lhs, const Vector4& rhs )
    {
        return Vector4( lhs ) *= rhs;
    }

    friend const Vector4 operator *( const Vector4& lhs, const T rhs )
    {
        return Vector4( lhs ) *= rhs;
    }

    friend const Vector4 operator *( const T lhs, const Vector4& rhs )
    {
        return rhs * lhs;
    }

    friend const Vector4 operator /( const Vector4& lhs, const Vector4& rhs )
    {
        return Vector4( lhs ) /= rhs;
    }

    friend const Vector4 operator /( const Vector4& lhs, const T rhs )
    {
        return Vector4( lhs ) /= rhs;
    }

    friend std::ostream& operator <<( std::ostream& os, const Vector4& rhs )
    {
        return os << rhs[0] << " " << rhs[1] << " " << rhs[2] << " " << rhs[3];
    }

public:
    // Will be removed.
    explicit Vector4( const T x )
    {
        *this = All( x );
    }

    void set( const T x )
    {
        *this = All( x );
    }
};

/*==========================================================================*/
/**
 *  Type definition.
 */
/*==========================================================================*/
typedef Vector4<int>           Vector4i;
typedef Vector4<unsigned int>  Vector4ui;
typedef Vector4<float>         Vector4f;
typedef Vector4<double>        Vector4d;
typedef Vector4<float>         Vec4;
typedef Vector4<int>           Vec4i;


template <typename T>
inline const Vector4<T> Vector4<T>::Zero()
{
    return Vector4( 0, 0, 0, 0 );
}

template <typename T>
inline const Vector4<T> Vector4<T>::All( const T x )
{
    return Vector4( x, x, x, x );
}

/*==========================================================================*/
/**
 *  Constructs a new Vector4.
 */
/*==========================================================================*/
template<typename T>
inline Vector4<T>::Vector4()
{
    this->zero();
};

/*==========================================================================*/
/**
 *  Constructs a new Vector4.
 *
 *  @param x [in] Element.
 *  @param y [in] Element.
 *  @param z [in] Element.
 *  @param w [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline Vector4<T>::Vector4( const T x, const T y, const T z, const T w )
{
    this->set( x, y, z, w );
};

/*==========================================================================*/
/**
 *  Constructs a new Vector4.
 *
 *  @param other [in] Vector2.
 *  @param z     [in] Element.
 *  @param w     [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline Vector4<T>::Vector4( const Vector2<T>& other, const T z , const T w )
{
    this->set( other, z, w );
};

/*==========================================================================*/
/**
 *  Constructs a new Vector4.
 *
 *  @param other [in] Vector3.
 *  @param w     [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline Vector4<T>::Vector4( const Vector3<T>& other, const T w )
{
    this->set( other, w );
};

/*==========================================================================*/
/**
 *  Constructs a new Vector4.
 *
 *  @param elements [in] Array of elements.
 */
/*==========================================================================*/
template<typename T>
inline Vector4<T>::Vector4( const T elements[4] )
{
    this->set( elements );
};

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param x [in] Element.
 *  @param y [in] Element.
 *  @param z [in] Element.
 *  @param w [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::set( const T x, const T y, const T z, const T w )
{
    m_elements[0] = x;
    m_elements[1] = y;
    m_elements[2] = z;
    m_elements[3] = w;
}

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param other [in] Vector2.
 *  @param z     [in] Element.
 *  @param w     [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::set( const Vector2<T>& other, const T z, const T w )
{
    m_elements[0] = other[0];
    m_elements[1] = other[1];
    m_elements[2] = z;
    m_elements[3] = w;
}

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param other [in] Vector3.
 *  @param w     [in] Element.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::set( const Vector3<T>& other, const T w )
{
    m_elements[0] = other[0];
    m_elements[1] = other[1];
    m_elements[2] = other[2];
    m_elements[3] = w;
}

/*==========================================================================*/
/**
 *  Sets the elements.
 *
 *  @param elements [in] Array of elements.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::set( const T elements[4] )
{
    m_elements[0] = elements[0];
    m_elements[1] = elements[1];
    m_elements[2] = elements[2];
    m_elements[3] = elements[3];
}

/*==========================================================================*/
/**
 *  Sets the elements to zero.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::zero()
{
    m_elements[0] = T( 0 );
    m_elements[1] = T( 0 );
    m_elements[2] = T( 0 );
    m_elements[3] = T( 0 );
}

/*==========================================================================*/
/**
 *  Swaps this and other.
 *
 *  @param other [in,out] Vector4.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::swap( Vector4& other )
{
    std::swap( m_elements[0], other[0] );
    std::swap( m_elements[1], other[1] );
    std::swap( m_elements[2], other[2] );
    std::swap( m_elements[3], other[3] );
}

/*==========================================================================*/
/**
 *  Returns the first element.
 *
 *  @return Reference of the first element.
 */
/*==========================================================================*/
template<typename T>
inline T& Vector4<T>::x()
{
    return m_elements[0];
}

/*==========================================================================*/
/**
 *  Returns the first element.
 *
 *  @return Reference of the first element.
 */
/*==========================================================================*/
template<typename T>
inline const T& Vector4<T>::x() const
{
    return m_elements[0];
}

/*==========================================================================*/
/**
 *  Returns the second element.
 *
 *  @return Reference of the second element.
 */
/*==========================================================================*/
template<typename T>
inline T& Vector4<T>::y()
{
    return m_elements[1];
}

/*==========================================================================*/
/**
 *  Returns the second element.
 *
 *  @return Reference of the second element.
 */
/*==========================================================================*/
template<typename T>
inline const T& Vector4<T>::y() const
{
    return m_elements[1];
}

/*==========================================================================*/
/**
 *  Returns the third element.
 *
 *  @return Reference of the third element.
 */
/*==========================================================================*/
template<typename T>
inline T& Vector4<T>::z()
{
    return m_elements[2];
}

/*==========================================================================*/
/**
 *  Returns the third element.
 *
 *  @return Reference of the third element.
 */
/*==========================================================================*/
template<typename T>
inline const T& Vector4<T>::z() const
{
    return m_elements[2];
}

/*==========================================================================*/
/**
 *  Returns the forth element.
 *
 *  @return Reference of the forth element.
 */
/*==========================================================================*/
template<typename T>
inline T& Vector4<T>::w()
{
    return m_elements[3];
}

/*==========================================================================*/
/**
 *  Returns the forth element.
 *
 *  @return Reference of the forth element.
 */
/*==========================================================================*/
template<typename T>
inline const T& Vector4<T>::w() const
{
    return m_elements[3];
}

template <typename T>
inline const Vector2<T> Vector4<T>::xy() const
{
    return Vector2<T>( m_elements[0], m_elements[1] );
}

template <typename T>
inline const Vector3<T> Vector4<T>::xyz() const
{
    return Vector3<T>( m_elements[0], m_elements[1], m_elements[2] );
}

template<typename T>
inline const Vector4<T> Vector4<T>::normalized() const
{
    const double length = this->length();
    const T normalize_factor = length > 0.0 ? static_cast<T>( 1.0 / length ) : T( 0 );
    return *this * normalize_factor;
}

/*==========================================================================*/
/**
 *  Normalizes this.
 *
 *  @return Normalized Vector4.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::normalize()
{
    const double length = this->length();
    const T normalize_factor = length > 0.0 ? static_cast<T>( 1.0 / length ) : T( 0 );
    *this *= normalize_factor;
}

/*==========================================================================*/
/**
 *  Prints the elements of this.
 */
/*==========================================================================*/
template<typename T>
inline void Vector4<T>::print() const
{
    std::cout << *this << std::endl;
}

/*==========================================================================*/
/**
 *  Calculates a length of this.
 *
 *  @return Length of this.
 */
/*==========================================================================*/
template<typename T>
inline double Vector4<T>::length() const
{
    return std::sqrt( this->length2() );
}

/*==========================================================================*/
/**
 *  Calculates a square of a length of this.
 *
 *  @return Square of a length of this.
 */
/*==========================================================================*/
template<typename T>
inline double Vector4<T>::length2() const
{
    double result = 0.0;
    result += (double)m_elements[0] * (double)m_elements[0];
    result += (double)m_elements[1] * (double)m_elements[1];
    result += (double)m_elements[2] * (double)m_elements[2];
    result += (double)m_elements[3] * (double)m_elements[3];
    return result;
}

/*==========================================================================*/
/**
 *  Calculates a dot product.
 *
 *  @param other [in] Vector4.
 *  @return Dot product.
 */
/*==========================================================================*/
template<typename T>
inline T Vector4<T>::dot( const Vector4& other ) const
{
    T result( 0 );
    result += m_elements[0] * other[0];
    result += m_elements[1] * other[1];
    result += m_elements[2] * other[2];
    result += m_elements[3] * other[3];
    return result;
}

template<typename T>
inline const T& Vector4<T>::operator []( const size_t index ) const
{
    KVS_ASSERT( index < 4 );
    return m_elements[ index ];
}

template<typename T>
inline T& Vector4<T>::operator []( const size_t index )
{
    KVS_ASSERT( index < 4 );
    return m_elements[ index ];
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator +=( const Vector4& rhs )
{
    m_elements[0] += rhs[0];
    m_elements[1] += rhs[1];
    m_elements[2] += rhs[2];
    m_elements[3] += rhs[3];
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator -=( const Vector4& rhs )
{
    m_elements[0] -= rhs[0];
    m_elements[1] -= rhs[1];
    m_elements[2] -= rhs[2];
    m_elements[3] -= rhs[3];
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator *=( const Vector4& rhs )
{
    m_elements[0] *= rhs[0];
    m_elements[1] *= rhs[1];
    m_elements[2] *= rhs[2];
    m_elements[3] *= rhs[3];
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator *=( const T rhs )
{
    m_elements[0] *= rhs;
    m_elements[1] *= rhs;
    m_elements[2] *= rhs;
    m_elements[3] *= rhs;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator /=( const Vector4& rhs )
{
    m_elements[0] /= rhs[0];
    m_elements[1] /= rhs[1];
    m_elements[2] /= rhs[2];
    m_elements[3] /= rhs[3];
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator /=( const T rhs )
{
    m_elements[0] /= rhs;
    m_elements[1] /= rhs;
    m_elements[2] /= rhs;
    m_elements[3] /= rhs;
    return *this;
}

template<typename T>
inline const Vector4<T> Vector4<T>::operator -() const
{
    return Vector4( *this ) *= T( -1 );
}

} // end of namespace kvs

#endif // KVS__VECTOR_4_H_INCLUDE
