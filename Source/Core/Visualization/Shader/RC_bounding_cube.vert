varying float depth;

void main( void )
{
    gl_FrontColor = gl_Vertex;
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

    depth = ( 1.0 + gl_Position.z / gl_Position.w ) * 0.5;
}
