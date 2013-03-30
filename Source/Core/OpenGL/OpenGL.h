/****************************************************************************/
/**
 *  @file   OpenGL.h
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
#ifndef KVS__OPEN_GL_H_INCLUDE
#define KVS__OPEN_GL_H_INCLUDE

#include <sstream>
#include <string>
#include <kvs/GL>
#include <kvs/StringList>


namespace kvs
{

namespace OpenGL
{

std::string Description();
std::string Version();
std::string GLSLVersion();
std::string GLUVersion();
std::string GLEWVersion();
std::string Vendor();
std::string Renderer();
kvs::StringList ExtensionList();
GLenum ErrorCode();
bool HasError();
std::string ErrorString( const GLenum error_code );

void GetBooleanv( GLenum pname, GLboolean* params );
void GetDoublev( GLenum pname, GLdouble* params );
void GetFloatv( GLenum pname, GLfloat* params );
void GetIntegerv( GLenum pname, GLint* params );
GLboolean Boolean( GLenum pname );
GLdouble Double( GLenum pname );
GLfloat Float( GLenum pname );
GLint Integer( GLenum pname );

GLint MaxTextureSize();
GLint Max3DTextureSize();
GLint MaxTextureImageUnits();
GLint MaxCombinedTextureImageUnits();
GLint MaxColorAttachments();
GLint MaxRenderBufferSize();

void Enable( GLenum cap );
void Disable( GLenum cap );
void ActivateTextureUnit( GLint unit );

/*KVS_DEPRECATED*/ inline std::string ShaderVersion() { return GLSLVersion(); }
/*KVS_DEPRECATED*/ inline bool CheckError() { return !HasError(); }

} // end of namespace OpenGL

} // end of namespace kvs

#endif // KVS__OPEN_GL_H_INCLUDE
