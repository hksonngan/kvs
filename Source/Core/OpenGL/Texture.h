/****************************************************************************/
/**
 *  @file   Texture.h
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
#ifndef KVS__TEXTURE_H_INCLUDE
#define KVS__TEXTURE_H_INCLUDE

#include <cctype>
#include <kvs/GL>


namespace kvs
{

/*==========================================================================*/
/**
 *  Texture class.
 */
/*==========================================================================*/
class Texture
{
protected:

    GLenum m_target; ///< target
    GLuint m_id; ///< texture ID
    GLint m_internal_format; ///< internal pixel data format
    GLenum m_external_format; ///< external pixel data format
    GLenum m_external_type; ///< external pixel data type
    GLenum m_mag_filter; ///< filtering method for magnification
    GLenum m_min_filter; ///< filtering method for minification

public:

    Texture( const GLenum target );

    GLenum target() const;
    GLuint id() const;
    GLenum magFilter() const;
    GLenum minFilter() const;
    GLint internalFormat() const;
    GLenum externalFormat() const;
    GLenum externalType() const;
    bool isTexture() const;

    void setMagFilter( const GLenum mag_filter );
    void setMinFilter( const GLenum min_filter );
    void setPixelFormat( const GLint  internal_format, const GLenum external_format, const GLenum external_type );
    void setPixelFormat( const size_t nchannels, const size_t bytes_per_channel );

    void bind() const;
    void unbind() const;
    bool isValid() const;
    bool isBinding() const;

protected:

    void generateTexture();
    void deleteTexture();
    void setImage1D( GLsizei width, const GLvoid* data );
    void setImage2D( GLsizei width, GLsizei height, const GLvoid* data );
    void setImage3D( GLsizei width, GLsizei height, GLsizei depth, const GLvoid* data );
    void setImageRectangle( GLsizei width, GLsizei height, const GLvoid* data );
    void setSubImage1D( GLsizei width, const GLvoid* data, GLint xoffset = 0 );
    void setSubImage2D( GLsizei width, GLsizei height, const GLvoid* data, GLint xoffset = 0, GLint yoffset = 0 );
    void setSubImage3D( GLsizei width, GLsizei height, GLsizei depth, const GLvoid* data, GLint xoffset = 0, GLint yoffset = 0, GLint zoffset = 0 );
    void setSubImageRectangle( GLsizei width, GLsizei height, const GLvoid* data, GLint xoffset = 0, GLint yoffset = 0 );
    void setParameter( GLenum pname, GLfloat param );
    void setParameter( GLenum pname, GLint param );
    void setParameter( GLenum pname, GLenum param );
    void setParameters( GLenum pname, const GLfloat* params );
    void setParameters( GLenum pname, const GLint* params );
    void setPixelStorageMode( GLenum pname, GLfloat param );
    void setPixelStorageMode( GLenum pname, GLint param );

private:

    size_t get_nchannels( const GLenum external_format ) const;
    size_t get_channel_size( const GLenum external_type ) const;
    void estimate_pixel_format( const size_t nchannels, const size_t bytes_per_channel );
    void determine_pixel_format_for_1_channel( const size_t bytes_per_channel );
    void determine_pixel_format_for_2_channel( const size_t bytes_per_channel );
    void determine_pixel_format_for_3_channel( const size_t bytes_per_channel );
    void determine_pixel_format_for_4_channel( const size_t bytes_per_channel );
};

} // end of namespace kvs

#endif // KVS__TEXTURE_H_INCLUDE
