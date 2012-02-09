/* DONT'T EDIT THIS FILE.
 * THIS IS GENERATED BY "Configure/configure_shader.py".
 */
#ifndef KVS__GLEW__GLSL__PointRenderer_H_INCLUDE
#define KVS__GLEW__GLSL__PointRenderer_H_INCLUDE

#include <string>

namespace kvs { namespace glew { namespace glsl {

namespace PointRenderer
{

namespace Vertex
{

const std::string shading =
    "varying vec3 position;\n"
    "varying vec3 normal;\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    gl_FrontColor = gl_Color;\n"
    "    gl_Position = ftransform();\n"
    "\n"
    "    position = vec3( gl_ModelViewMatrix * gl_Vertex );\n"
    "    normal = gl_NormalMatrix * gl_Normal.xyz;\n"
    "}\n"
;

} // end of namespace Vertex

namespace Geometry
{

} // end of namespace Geometry

namespace Fragment
{

const std::string shading =
    "struct Shading\n"
    "{\n"
    "    float Ka; // ambient\n"
    "    float Kd; // diffuse\n"
    "    float Ks; // specular\n"
    "    float S;  // shininess\n"
    "};\n"
    "\n"
    "vec3 ShadingNone( in Shading shading, in vec3 color )\n"
    "{\n"
    "    return( color );\n"
    "}\n"
    "\n"
    "vec3 ShadingLambert( in Shading shading, in vec3 color, in vec3 L, in vec3 N )\n"
    "{\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "#endif\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "\n"
    "    return( color * ( Ia + Id ) );\n"
    "}\n"
    "\n"
    "vec3 ShadingPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 R = reflect( -L, N );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( R, V ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( R, V ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "vec3 ShadingBlinnPhong( in Shading shading, in vec3 color, in vec3 L, in vec3 N, in vec3 V )\n"
    "{\n"
    "    vec3 H = normalize( L + V );\n"
    "#if defined( ENABLE_TWO_SIDE_LIGHTING )\n"
    "    float dd = abs( dot( N, L ) );\n"
    "    float ds = pow( abs( dot( H, N ) ), shading.S );\n"
    "#else\n"
    "    float dd = max( dot( N, L ), 0.0 );\n"
    "    float ds = pow( max( dot( H, N ), 0.0 ), shading.S );\n"
    "#endif\n"
    "    if ( dd <= 0.0 ) ds = 0.0;\n"
    "\n"
    "    float Ia = shading.Ka;\n"
    "    float Id = shading.Kd * dd;\n"
    "    float Is = shading.Ks * ds;\n"
    "\n"
    "    return( color * ( Ia + Id ) + Is );\n"
    "}\n"
    "\n"
    "varying vec3    position;\n"
    "varying vec3    normal;\n"
    "uniform Shading shading;\n"
    "\n"
    "\n"
    "void main( void )\n"
    "{\n"
    "    vec3 L = normalize( gl_LightSource[0].position.xyz - position );\n"
    "    vec3 N = normalize( normal );\n"
    "\n"
    "#if   defined( ENABLE_LAMBERT_SHADING )\n"
    "    vec3 shaded_color = ShadingLambert( shading, gl_Color.xyz, L, N );\n"
    "\n"
    "#elif defined( ENABLE_PHONG_SHADING )\n"
    "    vec3 V = normalize( -position );\n"
    "    vec3 shaded_color = ShadingPhong( shading, gl_Color.xyz, L, N, V );\n"
    "\n"
    "#elif defined( ENABLE_BLINN_PHONG_SHADING )\n"
    "    vec3 V = normalize( -position );\n"
    "    vec3 shaded_color = ShadingBlinnPhong( shading, gl_Color.xyz, L, N, V );\n"
    "\n"
    "#else // DISABLE SHADING\n"
    "    vec3 shaded_color = ShadingNone( shading, gl_Color.xyz );\n"
    "#endif\n"
    "\n"
    "    gl_FragColor.xyz = shaded_color;\n"
    "    gl_FragColor.w = 1.0;\n"
    "}\n"
;

} // end of namespace Fragment

} // end of namespace PointRenderer

} } } // end of namespace kvs, glew, glsl

#endif // KVS__GLEW__GLSL__PointRenderer_H_INCLUDE
