/****************************************************************************/
/**
 *  @file Xform.cpp
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
#include "Xform.h"


namespace kvs
{

/*==========================================================================*/
/**
 *  Default constructor.
 */
/*==========================================================================*/
Xform::Xform( void )
{
    m_rotation.identity();
    m_scaling.set( 1.0, 1.0, 1.0 );
    m_translation.set( 0.0, 0.0, 0.0 );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param translation [in] translation vector
 *  @param scaling [in] scaling vector
 *  @param rotation [in] rotation matrix
 */
/*==========================================================================*/
Xform::Xform(
    const kvs::Vector3f&  translation,
    const kvs::Vector3f&  scaling,
    const kvs::Matrix33f& rotation )
{
    this->set( translation, scaling, rotation );
}

/*==========================================================================*/
/**
 *  Constructor.
 *  @param m [in] xform matrix
 */
/*==========================================================================*/
Xform::Xform( const kvs::Matrix44f& m )
{
    kvs::Vector3f vx( m[0][0], m[1][0], m[2][0] );
    kvs::Vector3f vy( m[0][1], m[1][1], m[2][1] );
    kvs::Vector3f vz( m[0][2], m[1][2], m[2][2] );

    m_scaling.set( (float)vx.length(), (float)vy.length(), (float)vz.length() );
    m_rotation[0] = vx.normalizedVector();
    m_rotation[1] = vy.normalizedVector();
    m_rotation[2] = vz.normalizedVector();
    m_rotation.transpose();

    m_translation.set( m[0][3], m[1][3], m[2][3] );
}

/*==========================================================================*/
/**
 *  Set the transformation parameters.
 *  @param translation [in] translation vector
 *  @param scaling [in] scaling vector
 *  @param rotation [in] rotation matrix
 *
 *  Calculate the xform matrix \f${\bf X}\f$ by using the specified
 *  transformation parameters, which are the translation vector \f${\bf T}\f$,
 *  the scaling values \f${\bf s}=[s_{x},s_{y},s_{z}]^{t}\f$ and the rotation
 *  matrix \f${\bf R}\f$ as follows:
 *
 *  \f[
 *  {\bf X} = \left[ \begin{array}{cc}
 *                   diag({\bf s}) {\bf R}    & {\bf T} \\
 *                   {\bf 0}^{t}              & 1
 *                   \end{array}
 *            \right]
 *          = \left[ \begin{array}{cccc}
 *                   s_{x} r_{00} & s_{x} r_{01} & s_{x} r_{02} & t_{x} \\
 *                   s_{x} r_{10} & s_{x} r_{11} & s_{y} r_{12} & t_{y} \\
 *                   s_{x} r_{20} & s_{x} r_{21} & s_{z} r_{22} & t_{z} \\
 *                   0            & 0            & 0            & 1     \\
 *                   \end{array}
 *            \right]
 *  \f]
 */
/*==========================================================================*/
void Xform::set(
    const kvs::Vector3f&  translation,
    const kvs::Vector3f&  scaling,
    const kvs::Matrix33f& rotation )
{
    m_rotation = rotation;
    m_scaling = scaling;
    m_translation = translation;
}

/*==========================================================================*/
/**
 *  Get the translation vector.
 *  @return translation vector
 */
/*==========================================================================*/
const kvs::Vector3f& Xform::translation( void ) const
{
    return m_translation;
}

/*==========================================================================*/
/**
 *  Get the rotation matrix.
 *  @return rotation matrix
 */
/*==========================================================================*/
const kvs::Matrix33f& Xform::rotation( void ) const
{
    return( m_rotation );
}

/*==========================================================================*/
/**
 *  Get the scaled rotation matrix.
 *  @return scaled rotation matrix
 */
/*==========================================================================*/
const kvs::Matrix33f Xform::scaledRotation( void ) const
{
    const kvs::Matrix33f& R = this->rotation();
    const kvs::Vector3f& S = this->scaling();
    return kvs::Matrix33f( S[0] * R[0][0], S[1] * R[0][1], S[2] * R[0][2],
                           S[0] * R[1][0], S[1] * R[1][1], S[2] * R[1][2],
                           S[0] * R[2][0], S[1] * R[2][1], S[2] * R[2][2] );
}

/*==========================================================================*/
/**
 *  Get the scale vector.
 *  @return rotation matrix
 */
/*==========================================================================*/
const kvs::Vector3f& Xform::scaling( void ) const
{
    return( m_scaling );
}

kvs::Vector3f Xform::transform( const kvs::Vector3f& pos ) const
{
    return m_translation + m_rotation * ( m_scaling * pos );
}

kvs::Vector4f Xform::transform( const kvs::Vector4f& pos ) const
{
    kvs::Matrix44f m = this->toMat4();
    return m * pos;
}

kvs::Vector3f Xform::transformNormal( const kvs::Vector3f& normal ) const
{
    return m_rotation * ( m_scaling * normal );
}

kvs::Xform Xform::bindAfter( const kvs::Xform& x ) const
{
    return kvs::Xform( this->toMat4() * x.toMat4() );
}

kvs::Xform Xform::bindBefore( const kvs::Xform& x ) const
{
    return kvs::Xform( x.toMat4() * this->toMat4() );
}

kvs::Matrix44f Xform::toMat4() const
{
    const kvs::Matrix33f& R = this->rotation();
    const kvs::Vector3f& S = this->scaling();
    const kvs::Vector3f& T = this->translation();
    kvs::Matrix44f mat( S[0] * R[0][0], S[1] * R[0][1], S[2] * R[0][2], T[0],
                        S[0] * R[1][0], S[1] * R[1][1], S[2] * R[1][2], T[1],
                        S[0] * R[2][0], S[1] * R[2][1], S[2] * R[2][2], T[2],
                        0, 0, 0, 1 );
    return mat;
}

/*==========================================================================*/
/**
 *  Get the xform as array type.
 *  @param  array [i/o] xform array
 */
/*==========================================================================*/
void Xform::get( float (*array)[16] ) const
{
    kvs::Matrix44f mat = this->toMat4();

    (*array)[0]  = mat[0][0];
    (*array)[1]  = mat[1][0];
    (*array)[2]  = mat[2][0];
    (*array)[3]  = mat[3][0];

    (*array)[4]  = mat[0][1];
    (*array)[5]  = mat[1][1];
    (*array)[6]  = mat[2][1];
    (*array)[7]  = mat[3][1];

    (*array)[8]  = mat[0][2];
    (*array)[9]  = mat[1][2];
    (*array)[10] = mat[2][2];
    (*array)[11] = mat[3][2];

    (*array)[12] = mat[0][3];
    (*array)[13] = mat[1][3];
    (*array)[14] = mat[2][3];
    (*array)[15] = mat[3][3];
}

} // end of namepsace kvs
