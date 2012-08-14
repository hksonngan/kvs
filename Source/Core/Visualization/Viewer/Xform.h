/****************************************************************************/
/**
 *  @file Xform.h
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
#ifndef KVS__XFORM_H_INCLUDE
#define KVS__XFORM_H_INCLUDE

#include <kvs/Vector3>
#include <kvs/Matrix33>
#include <kvs/Matrix44>


namespace kvs
{

/*==========================================================================*/
/**
 *  Xform matrix class.
 *
 *  This xform matrix \f${\bf X}\f$ is a affine transformation matrix as follows:
 *
 *  \f[
 *  {\bf X} = \left[ \begin{array}{cc}
 *                   {\bf SR}    & {\bf T} \\
 *                   {\bf 0}^{t} & 1
 *                   \end{array}
 *            \right]
 *  \f]
 *
 * where, \f${\bf S}\f$ is a scaling matrix which is composed of three scaling
 * parameters \f${\bf s}=[s_{x},s_{y},s_{z}]^{t}\f$, \f${\bf T}\f$ is a translation
 * vector, and \f${\bf R}\f$ is a rotation matrix.
 *
 *  \f[
 *
 *  \begin{array}{ccl}
 *
 *  {\bf S} & = & diag({\bf s}) = \left[ \begin{array}{ccc}
 *                                       s_{x} & 0     & 0     \\
 *                                       0     & s_{y} & 0     \\
 *                                       0     & 0     & s_{z}
 *                                       \end{array}
 *                                \right]
 *
 *  \\
 *
 *  {\bf T} & = & [t_{x},t_{y},t_{z}]^{t}
 *
 *  \\
 *
 *  {\bf R} & = & \left[ \begin{array}{ccc}
 *                       r_{00} & r_{01} & r_{02} \\
 *                       r_{10} & r_{11} & r_{12} \\
 *                       r_{20} & r_{21} & r_{22}
 *                       \end{array}
 *                \right]
 *
 *  \end{array}
 *
 *  \f]
 */
/*==========================================================================*/
class Xform
{
private:
    kvs::Matrix44f m_matrix;

public:
    Xform( void );
    Xform(
        const kvs::Vector3f&  translation,
        const kvs::Vector3f&  scaling,
        const kvs::Matrix33f& rotation );
    explicit Xform( const kvs::Matrix44f& mat );

public:
#if KVS_ENABLE_DEPRECATED
    void initialize( void )
    {
        *this = kvs::Xform();
    }

    void clear( void )
    {
        this->set( kvs::Vector3f( 0, 0, 0 ),
                   kvs::Vector3f( 0, 0, 0 ),
                   kvs::Matrix33f( 0, 0, 0,
                                   0, 0, 0,
                                   0, 0, 0 ) );
    }

    void set(
        const kvs::Vector3f&  translation,
        const kvs::Vector3f&  scaling,
        const kvs::Matrix33f& rotation )
    {
        *this = kvs::Xform( translation, scaling, rotation );
    }

    void set( const Xform& xform )
    {
        *this = xform;
    }

    void updateRotation( const kvs::Matrix33f& rotation )
    {
        this->bind( kvs::Xform::Rotation( rotation ) );
    }

    void updateTranslation( const kvs::Vector3f& translation )
    {
        this->bind( kvs::Xform::Translation( translation ) );
    }

    void updateScaling( const kvs::Vector3f& scaling )
    {
        this->bind( kvs::Xform::Scaling( scaling ) );
    }

    void updateScaling( float scaling )
    {
        this->bind( kvs::Xform::Scaling( scaling ) );
    }
#endif
public:
    const kvs::Vector3f translation( void ) const;
    const kvs::Matrix33f rotation( void ) const;
    const kvs::Vector3f scaling( void ) const;
    const kvs::Matrix33f scaledRotation( void ) const;

public:
    const kvs::Vector3f transform( const kvs::Vector3f& pos ) const;
    const kvs::Vector3f transformNormal( const kvs::Vector3f& normal ) const;

    kvs::Xform& bind( const kvs::Xform& x );

    const kvs::Matrix44f toMatrix() const;
    void toArray( float array[16] ) const;

    static const kvs::Xform Translation( const kvs::Vector3f& t );
    static const kvs::Xform Rotation( const kvs::Matrix33f& r );
    static const kvs::Xform Scaling( const kvs::Vector3f& s );
    static const kvs::Xform Scaling( float s );

public:
#if KVS_ENABLE_DEPRECATED
    Xform get( void ) const
    {
        return *this;
    }

    void get( float (*array)[16] ) const
    {
        this->toArray( *array );
    }
#endif
};

} // end of namespace kvs

#endif // KVS__XFORM_H_INCLUDE
