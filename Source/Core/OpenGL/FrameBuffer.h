/****************************************************************************/
/**
 *  @file FrameBuffer.h
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
#ifndef KVS__FRAME_BUFFER_H_INCLUDE
#define KVS__FRAME_BUFFER_H_INCLUDE

#include <kvs/OpenGL>


namespace kvs
{

/*==========================================================================*/
/**
 *  Frame buffer class.
 */
/*==========================================================================*/
class FrameBuffer
{
protected:

    GLenum m_format; ///< pixel data format
    GLenum m_type; ///< pixel data type

public:

    FrameBuffer();
    FrameBuffer( const GLenum format, const GLenum type );
    virtual ~FrameBuffer();

    void setFormat( const GLenum format );
    void setType( const GLenum type );

    void read(
        const int    width,
        const int    height,
        void**       pixels,
        const GLenum buffer = 0 );

    void read(
        const int    x,
        const int    y,
        const int    width,
        const int    height,
        void**       pixels,
        const GLenum buffer = 0 );

    static void read(
        const int    x,
        const int    y,
        const int    width,
        const int    height,
        const GLenum format,
        const GLenum type,
        void**       pixels,
        const GLenum buffer = 0 );

    void draw(
        const int    width,
        const int    height,
        const void*  pixels,
        const GLenum buffer = 0 );

    void draw(
        const int    width,
        const int    height,
        const int*   viewport,
        const void*  pixels,
        const GLenum buffer = 0 );

    void draw(
        const int    x,
        const int    y,
        const int    width,
        const int    height,
        const void*  pixels,
        const GLenum buffer = 0 );

    void draw(
        const int    x,
        const int    y,
        const int    width,
        const int    height,
        const int*   viewport,
        const void*  pixels,
        const GLenum buffer = 0 );

    void draw(
        const int    x,
        const int    y,
        const int    width,
        const int    height,
        const GLenum format,
        const GLenum type,
        const int*   viewport,
        const void*  pixels,
        const GLenum buffer = 0 );
};

} // end of namespace kvs

#endif // KVS__FRAME_BUFFER_H_INCLUDE
