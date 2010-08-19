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
#ifndef KVS_CORE_FRAME_BUFFER_H_INCLUDE
#define KVS_CORE_FRAME_BUFFER_H_INCLUDE

#include "OpenGL.h"
#include <kvs/ClassName>


namespace kvs
{

/*==========================================================================*/
/**
 *  Frame buffer class.
 */
/*==========================================================================*/
class FrameBuffer
{
    kvsClassName( FrameBuffer );

protected:

    GLenum m_format; ///< pixel data format
    GLenum m_type;   ///< pixel data type

public:

    FrameBuffer( void );

    FrameBuffer( const GLenum format, const GLenum type );

    virtual ~FrameBuffer( void );

public:

    void setFormat( const GLenum format );

    void setType( const GLenum type );

public:

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

#endif // KVS_CORE_FRAME_BUFFER_H_INCLUDE
