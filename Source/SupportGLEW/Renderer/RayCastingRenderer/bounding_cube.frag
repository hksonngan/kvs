varying float depth;

void main( void )
{
    gl_FragColor.rgb = gl_Color.rgb;
    gl_FragColor.a = depth;
}
