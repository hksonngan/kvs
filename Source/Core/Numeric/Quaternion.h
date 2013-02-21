/****************************************************************************/
/**
 *  @file Quaternion.h
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
#ifndef KVS__QUATERNION_H_INCLUDE
#define KVS__QUATERNION_H_INCLUDE

#include <iostream>
#include <iomanip>
#include <kvs/Math>
#include <kvs/Assert>
#include <kvs/Vector4>
#include <kvs/Matrix33>
#include <kvs/Matrix44>


namespace kvs
{

/*==========================================================================*/
/**
*  Quaternion class
*/
/*==========================================================================*/

class Quaternion
{
private:

    /* Quaternion: Q
       Q = w + xi + yj + zk
         x = m_elements[0],
         y = m_elements[1],
         z = m_elements[2],
         w = m_elements[3]
     */
    kvs::Vector4<float> m_elements;

public:

    Quaternion();
    Quaternion( float x, float y, float z, float w );
    Quaternion( const Vector3<float>& axis, float angle );
    explicit Quaternion( const Matrix33<float>& mat );
    explicit Quaternion( const float elements[4] );

public:

    void set( float x, float y, float z, float w );

    float& x();
    float& y();
    float& z();
    float& w();
    const float& x() const;
    const float& y() const;
    const float& z() const;
    const float& w() const;

    Quaternion& zero();
    const Quaternion zero() const;
    Quaternion& identity();
    const Quaternion identity() const;
    Quaternion& conjugate();
    const Quaternion conjugate() const;
    Quaternion& normalize();
    const Quaternion normalize() const;
    Quaternion& inverse();
    const Quaternion inverse() const;
    Quaternion& log();
    const Quaternion log() const;
    Quaternion& exp();
    const Quaternion exp() const;
    double dot( const Quaternion& q ) const;
    double length() const;
    double length2() const;

public:

    float& operator [] ( size_t index );
    const float& operator [] ( size_t index ) const;

    Quaternion& operator += ( const Quaternion& q );
    Quaternion& operator -= ( const Quaternion& q );
    Quaternion& operator *= ( float a );
    Quaternion& operator /= ( float a );
    Quaternion& operator *= ( const Quaternion& q );

public:

    friend bool operator == ( const Quaternion& a, const Quaternion& b )
    {
        return a.m_elements == b.m_elements;
    }

    friend bool operator != ( const Quaternion& a, const Quaternion& b )
    {
        return !( a == b );
    }

    friend Quaternion operator - ( const Quaternion& a )
    {
        return Quaternion( -a[0], -a[1], -a[2], -a[3] );
    }

    friend Quaternion operator + ( const Quaternion& a, const Quaternion& b )
    {
        return Quaternion( a ) += b;
    }

    friend Quaternion operator - ( const Quaternion& a, const Quaternion& b )
    {
        return Quaternion( a ) -= b;
    }

    friend Quaternion operator * ( const Quaternion& q, float s )
    {
        return Quaternion( q ) *= s;
    }

    friend Quaternion operator * ( float s, const Quaternion& q )
    {
        return Quaternion( q ) *= s;
    }

    friend Quaternion operator / ( const Quaternion& q, float s )
    {
        return Quaternion( q ) /= s;
    }

    friend Quaternion operator * ( const Quaternion& a, const Quaternion& b )
    {
        return Quaternion( a ) *= b;
    }

public:

    const kvs::Matrix33<float> toMatrix() const;
    void toMatrix( kvs::Matrix33<float>& m ) const;
    void toMatrix( kvs::Matrix44<float>& m ) const;
    void toMatrix( float m[16] ) const;

public:

    friend std::ostream& operator << ( std::ostream& os, const Quaternion& q )
    {
        const size_t width     = 8;
        const size_t precision = 3;

        const std::ios_base::fmtflags original_flags( os.flags() );

        os.setf( std::ios::fixed );
        os.setf( std::ios::showpoint );

        os << std::setw(width) << std::setprecision(precision) << q.w() << " + ";
        os << std::setw(width) << std::setprecision(precision) << q.x() << " i + ";
        os << std::setw(width) << std::setprecision(precision) << q.y() << " j + ";
        os << std::setw(width) << std::setprecision(precision) << q.z() << " k";

        os.flags( original_flags );

        return os;
    }

public:

    Vector3<float> axis();
    float angle();

public:

    static Vector3<float> rotate( const Vector3<float>& pos, const Vector3<float>& axis, float rad );
    static Vector3<float> rotate( const Vector3<float>& pos, const Quaternion& q );
    static Quaternion rotationQuaternion( Vector3<float> v0, Vector3<float> v1 );

public:

    static Quaternion linearInterpolation(
        const Quaternion& q1,
        const Quaternion& q2,
        double t,
        bool for_rotation );

    static Quaternion sphericalLinearInterpolation(
        const Quaternion& q1,
        const Quaternion& q2,
        double t,
        bool invert,
        bool for_rotation );

    static Quaternion sphericalCubicInterpolation(
        const Quaternion& q1,
        const Quaternion& q2,
        const Quaternion& a,
        const Quaternion& b,
        double t,
        bool for_rotation );

    static Quaternion splineInterpolation(
        const Quaternion& q1,
        const Quaternion& q2,
        const Quaternion& q3,
        const Quaternion& q4,
        double t,
        bool for_rotation );

    static Quaternion spline(
        const Quaternion& qnm1,
        const Quaternion& qn,
        const Quaternion& qnp1 );
};

inline Quaternion::Quaternion()
{
}

inline Quaternion::Quaternion( float x, float y, float z, float w ) : 
    m_elements( x, y, z, w )
{
}

inline Quaternion::Quaternion( const kvs::Vector3<float>& axis, float angle )
{
    float s = static_cast<float>( std::sin( angle * 0.5 ) );
    float w = static_cast<float>( std::cos( angle * 0.5 ) );

    kvs::Vector3<float> n = axis.normalized();
    kvs::Vector3<float> v = s * n;
    m_elements.set( v, w );
}

inline Quaternion::Quaternion( const kvs::Matrix33<float>& m )
{
    double trace = double( m.trace() + 1.0 );

    float x, y, z, w;
    if ( trace >= 1.0 )
    {
        double sqrt_trace = std::sqrt( trace );

        x = float( ( m[1][2] - m[2][1] ) * 0.5 / sqrt_trace );
        y = float( ( m[2][0] - m[0][2] ) * 0.5 / sqrt_trace );
        z = float( ( m[0][1] - m[1][0] ) * 0.5 / sqrt_trace );
        w = float( sqrt_trace * 0.5 );
    }
    else
    {
        if ( m[0][0] > m[1][1] && m[0][0] > m[2][2] )
        {
            x = float( std::sqrt( double( m[0][0] - m[1][1] - m[2][2] ) + 1.0 ) * 0.5 );
            y = float( ( m[0][1] + m[1][0] ) * 0.25 / x );
            z = float( ( m[0][2] + m[2][0] ) * 0.25 / x );
            w = float( ( m[1][2] + m[2][1] ) * 0.25 / x );
        }
        else if ( m[1][1] > m[2][2] )
        {
            y = float( std::sqrt( double( m[1][1] - m[2][2] - m[0][0] ) + 1.0 ) * 0.5 );
            z = float( ( m[1][2] + m[2][1] ) * 0.25 / y );
            x = float( ( m[1][0] + m[0][1] ) * 0.25 / y );
            w = float( ( m[2][0] + m[0][2] ) * 0.25 / y );
        }
        else
        {
            z = float( std::sqrt( double( m[2][2] - m[0][0] - m[1][1] ) + 1.0 ) * 0.5 );
            x = float( ( m[2][0] + m[0][2] ) * 0.25 / z );
            y = float( ( m[2][1] + m[1][2] ) * 0.25 / z );
            w = float( ( m[0][1] + m[1][0] ) * 0.25 / z );
        }
    }
    m_elements.set( x, y, z, w );
}

inline Quaternion::Quaternion( const float elements[4] ) :
    m_elements( elements )
{
}

inline void Quaternion::set( float x, float y, float z, float w )
{
    m_elements.set( x, y, z, w );
}

inline float& Quaternion::x()
{
    return m_elements[0];
}

inline const float& Quaternion::x() const
{
    return m_elements[0];
}

inline float& Quaternion::y()
{
    return m_elements[1];
}

inline const float& Quaternion::y() const
{
    return m_elements[1];
}

inline float& Quaternion::z()
{
    return m_elements[2];
}

inline const float& Quaternion::z() const
{
    return m_elements[2];
}

inline float& Quaternion::w()
{
    return m_elements[3];
}

inline const float& Quaternion::w() const
{
    return m_elements[3];
}

inline Quaternion& Quaternion::zero()
{
    m_elements.set( 0, 0, 0, 0 );
    return *this;
}

inline const Quaternion Quaternion::zero() const
{
    Quaternion result;
    return result.zero();
}

inline Quaternion& Quaternion::identity()
{
    m_elements.set( 0, 0, 0, 1 );
    return *this;
}

inline const Quaternion Quaternion::identity() const
{
    Quaternion result;
    return result.identity();
}

inline Quaternion& Quaternion::conjugate()
{
    m_elements[0] *= float(-1);
    m_elements[1] *= float(-1);
    m_elements[2] *= float(-1);
    return *this;
}

inline const Quaternion Quaternion::conjugate() const
{
    Quaternion result( *this );
    return result.conjugate();
}

inline Quaternion& Quaternion::normalize()
{
    float n = static_cast<float>( this->length() );
    n = n > float(0) ? float(1) / n : float(0);
    m_elements *= n;
    return *this;
}

inline const Quaternion Quaternion::normalize() const
{
    Quaternion result( *this );
    return result.normalize();
}

inline Quaternion& Quaternion::inverse()
{
    float n = static_cast<float>( this->length2() );

    if ( n > 0 )
    {
        m_elements[0] /= -n;
        m_elements[1] /= -n;
        m_elements[2] /= -n;
        m_elements[3] /=  n;
    }
    return *this;
}

inline const Quaternion Quaternion::inverse() const
{
    Quaternion result( *this );
    return result.inverse();
}

inline Quaternion& Quaternion::log()
{
    double theta     = std::acos( double( m_elements[3] ) );
    double sin_theta = std::sin( theta );

    m_elements[3] = 0;

    if ( sin_theta > 0 )
    {
        m_elements[0] = float( theta * m_elements[0] / sin_theta );
        m_elements[1] = float( theta * m_elements[1] / sin_theta );
        m_elements[2] = float( theta * m_elements[2] / sin_theta );
    }
    else
    {
        m_elements[0] = 0;
        m_elements[1] = 0;
        m_elements[2] = 0;
    }
    return *this;
}

inline const Quaternion Quaternion::log() const
{
    Quaternion result( *this );
    return result.log();
}

inline Quaternion& Quaternion::exp()
{
    double theta2 = m_elements.xyz().length2();
    double theta     = std::sqrt( theta2 );
    double cos_theta = std::cos( theta );

    m_elements[3] = float( cos_theta );

    if ( theta > 0 )
    {
        double sin_theta = std::sin( theta );
        m_elements[0] = float( sin_theta * m_elements[0] / theta );
        m_elements[1] = float( sin_theta * m_elements[1] / theta );
        m_elements[2] = float( sin_theta * m_elements[2] / theta );
    }
    else
    {
        m_elements[0] = 0;
        m_elements[1] = 0;
        m_elements[2] = 0;
    }
    return *this;
}

inline const Quaternion Quaternion::exp() const
{
    Quaternion result( *this );
    return result.exp();
}

inline double Quaternion::dot( const Quaternion& q ) const
{
    double result = 0.0;
    result += this->x() * q.x();
    result += this->y() * q.y();
    result += this->z() * q.z();
    result += this->w() * q.w();
    return result;
}

inline double Quaternion::length() const
{
    return m_elements.length();
}

inline double Quaternion::length2() const
{
    return m_elements.length2();
}

inline float& Quaternion::operator [] ( size_t index )
{
    return m_elements[ index ];
}

inline const float& Quaternion::operator [] ( size_t index ) const
{
    return m_elements[ index ];
}

inline Quaternion& Quaternion::operator += ( const Quaternion& q )
{
    m_elements += q.m_elements;
    return *this;
}

inline Quaternion& Quaternion::operator -= ( const Quaternion& q )
{
    m_elements -= q.m_elements;
    return *this;
}

inline Quaternion& Quaternion::operator *= ( float a )
{
    m_elements *= a;
    return *this;
}

inline Quaternion& Quaternion::operator /= ( float a )
{
    m_elements /= a;
    return *this;
}

inline Quaternion& Quaternion::operator *= ( const Quaternion& q )
{
    float x = this->x();
    float y = this->y();
    float z = this->z();
    float w = this->w();

    this->set( w * q.x() + x * q.w() + y * q.z() - z * q.y(),
               w * q.y() - x * q.z() + y * q.w() + z * q.x(),
               w * q.z() + x * q.y() - y * q.x() + z * q.w(),
               w * q.w() - x * q.x() - y * q.y() - z * q.z() );

    return *this;
}

inline const kvs::Matrix33<float> Quaternion::toMatrix() const
{
    float length_2 = static_cast<float>( this->length2() );
    float s = ( length_2 > 0 ) ? float(2) / length_2 : 0;

    float xx = this->x() * this->x() * s;
    float yy = this->y() * this->y() * s;
    float zz = this->z() * this->z() * s;
    float xy = this->x() * this->y() * s;
    float xz = this->x() * this->z() * s;
    float yz = this->y() * this->z() * s;
    float wx = this->w() * this->x() * s;
    float wy = this->w() * this->y() * s;
    float wz = this->w() * this->z() * s;

    kvs::Matrix33<float> ret;
    ret[0][0] = 1.0f - ( yy + zz );
    ret[1][0] = xy + wz;
    ret[2][0] = xz - wy;

    ret[0][1] = xy - wz;
    ret[1][1] = 1.0f - ( xx + zz );
    ret[2][1] = yz + wx;

    ret[0][2] = xz + wy;
    ret[1][2] = yz - wx;
    ret[2][2] = 1.0f - ( xx + yy );

    return ret;
}


inline void Quaternion::toMatrix( kvs::Matrix33<float>& m ) const
{
    m = this->toMatrix();
}

inline void Quaternion::toMatrix( kvs::Matrix44<float>& m ) const
{
    float length_2 = static_cast<float>( this->length2() );
    float s = ( length_2 > float(0) ) ? float(2) / length_2 : float(0);

    float xx = this->x() * this->x() * s;
    float yy = this->y() * this->y() * s;
    float zz = this->z() * this->z() * s;
    float xy = this->x() * this->y() * s;
    float xz = this->x() * this->z() * s;
    float yz = this->y() * this->z() * s;
    float wx = this->w() * this->x() * s;
    float wy = this->w() * this->y() * s;
    float wz = this->w() * this->z() * s;

    m[0][0] = float(1) - ( yy + zz );
    m[1][0] = xy + wz;
    m[2][0] = xz - wy;
    m[3][0] = float(0);

    m[0][1] = xy - wz;
    m[1][1] = float(1) - ( xx + zz );
    m[2][1] = yz + wx;
    m[3][1] = float(0);

    m[0][2] = xz + wy;
    m[1][2] = yz - wx;
    m[2][2] = float(1) - ( xx + yy );
    m[3][2] = float(0);

    m[0][3] = float(0);
    m[1][3] = float(0);
    m[2][3] = float(0);
    m[3][3] = float(1);
}

inline void Quaternion::toMatrix( float m[16] ) const
{
    float length_2 = static_cast<float>( this->length2() );
    float s = ( length_2 > 0 ) ? float(2) / length_2 : float(0);

    float xx = this->x() * this->x() * s;
    float yy = this->y() * this->y() * s;
    float zz = this->z() * this->z() * s;
    float xy = this->x() * this->y() * s;
    float xz = this->x() * this->z() * s;
    float yz = this->y() * this->z() * s;
    float wx = this->w() * this->x() * s;
    float wy = this->w() * this->y() * s;
    float wz = this->w() * this->z() * s;

    m[0]  = float(1) - ( yy + zz );
    m[1]  = xy + wz;
    m[2]  = xz - wy;
    m[3]  = float(0);

    m[4]  = xy - wz;
    m[5]  = float(1) - ( xx + zz );
    m[6]  = yz + wx;
    m[7]  = float(0);

    m[8]  = xz + wy;
    m[9]  = yz - wx;
    m[10] = float(1) - ( xx + yy );
    m[11] = float(0);

    m[12] = float(0);
    m[13] = float(0);
    m[14] = float(0);
    m[15] = float(1);
}

inline kvs::Vector3<float> Quaternion::axis()
{
    float s = float( std::sin( double( this->angle() ) * 0.5 ) );
    return m_elements.xyz() / s;
}

inline float Quaternion::angle()
{
    return float( std::acos( double( this->w() ) ) * 2.0 );
}

inline kvs::Vector3<float> Quaternion::rotate( const kvs::Vector3<float>& pos, const kvs::Vector3<float>& axis, float rad )
{
    const Quaternion p( pos.x(), pos.y(), pos.z(), float(0) );
    const Quaternion rotate_quat( axis, rad );
    const Quaternion rotate_conj = rotate_quat.conjugate();
    const Quaternion rotate_pos = rotate_quat * p * rotate_conj;
    return rotate_pos.m_elements.xyz();
}

inline kvs::Vector3<float> Quaternion::rotate( const kvs::Vector3<float>& pos, const kvs::Quaternion& q )
{
    const Quaternion p( pos.x(), pos.y(), pos.z(), float(0) );
    const Quaternion rotate_conj = q.conjugate();
    const Quaternion rotate_pos = q * p * rotate_conj;
    return rotate_pos.m_elements.xyz();
}

inline Quaternion Quaternion::rotationQuaternion( Vector3<float> v0, Vector3<float> v1 )
{
    Quaternion q;

    v0.normalize();
    v1.normalize();

    kvs::Vector3<float> c = v0.cross( v1 );
    float               d = v0.x() * v1.x() + v0.y() * v1.y() + v0.z() * v1.z();
    double              s = std::sqrt( double( ( 1 + d ) * 2.0 ) );

    q.x() = float( c.x() / s );
    q.y() = float( c.y() / s );
    q.z() = float( c.z() / s );
    q.w() = float( s / 2.0 );

    return q;
}

inline Quaternion Quaternion::linearInterpolation(
    const Quaternion& q1,
    const Quaternion& q2,
    double            t,
    bool              for_rotation )
{
    Quaternion ret = q1 + float(t) * ( q2 - q1 );

    if ( for_rotation ) { ret.normalize(); }

    return ret;
}

inline Quaternion Quaternion::sphericalLinearInterpolation(
    const Quaternion& q1,
    const Quaternion& q2,
    double            t,
    bool              invert,
    bool              for_rotation )
{
    Quaternion tmp1 = q1; tmp1.normalize();
    Quaternion tmp2 = q2; tmp2.normalize();

    double dot = tmp1.dot( tmp2 );

    Quaternion q3;

    // dot = cos( theta )
    // if (dot < 0), q1 and q2 are more than 90 degrees apart,
    // so we can invert one to reduce spining

    if ( invert && dot < 0 )
    {
        dot = -dot;
        q3  = -q2;
    }
    else
    {
        q3 = q2;
    }

    if ( (  invert && dot < 0.95 ) ||
         ( !invert && dot > -0.95 && dot < 0.95 ) )
    {
        double angle   = std::acos( dot );
        double sina    = std::sin( angle );
        double sinat   = std::sin( angle * t );
        double sinaomt = std::sin( angle * (1-t) );

        return ( q1 * float( sinaomt ) + q3 * float( sinat ) ) / float( sina );
    }
    // if the angle is small, use linear interpolation
    else
    {
        return linearInterpolation( q1, q3, t, for_rotation );
    }
}

inline Quaternion Quaternion::sphericalCubicInterpolation(
    const Quaternion& q1,
    const Quaternion& q2,
    const Quaternion& a,
    const Quaternion& b,
    double            t,
    bool              for_rotation )
{
    Quaternion c = sphericalLinearInterpolation( q1, q2, t, false, for_rotation );
    Quaternion d = sphericalLinearInterpolation(  a,  b, t, false, for_rotation );

    return sphericalLinearInterpolation( c, d, 2.0 * t * (1-t), false, for_rotation );
}

inline Quaternion Quaternion::splineInterpolation(
    const Quaternion& q1,
    const Quaternion& q2,
    const Quaternion& q3,
    const Quaternion& q4,
    double               t,
    bool                 for_rotation )
{
    Quaternion a = spline( q1, q2, q3 );
    Quaternion b = spline( q2, q3, q4 );

    return sphericalCubicInterpolation( q2, q3, a, b, t, for_rotation );
}

inline Quaternion Quaternion::spline(
    const Quaternion& qnm1,
    const Quaternion& qn,
    const Quaternion& qnp1 )
{
    Quaternion tmpm1 = qnm1; tmpm1.normalize();
    Quaternion tmpp1 = qnp1; tmpp1.normalize();

    Quaternion qni = qn.conjugate(); qni.normalize();

    return qn * ( ( ( qni * tmpm1 ).log() + ( qni * tmpp1 ).log() ) / -4 ).exp();
}

} // end of namespace kvs

#endif // KVS__QUATERNION_H_INCLUDE
