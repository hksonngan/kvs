varying vec3 position;
varying vec3 normal;

void main( void )
{
    gl_FrontColor = gl_Color;
    gl_Position = ftransform();

    position = vec3( gl_ModelViewMatrix * gl_Vertex );
    normal = gl_NormalMatrix * gl_Normal.xyz;
}
