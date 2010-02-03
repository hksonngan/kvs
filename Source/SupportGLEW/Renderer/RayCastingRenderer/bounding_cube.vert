void main( void )
{
    gl_FrontColor = gl_Vertex;
    gl_Position = ftransform();
}
