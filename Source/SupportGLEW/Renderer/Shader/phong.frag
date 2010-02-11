struct Shader
{
    float Ka; // ambient
    float Kd; // diffuse
    float Ks; // specular
    float S;  // shininess
};

varying vec3 position;
varying vec3 normal;

uniform Shader shader;


vec3 noShading( in vec3 color )
{
    return( color );
}

vec3 lambertShading( in vec3 color, in vec3 L, in vec3 N )
{
    float dd = max( dot( N, L ), 0.0 );

    float Ia = shader.Ka;
    float Id = shader.Kd * dd;

    return( color * ( Ia + Id ) );
}

vec3 phongShading( in vec3 color, in vec3 L, in vec3 N )
{
    vec3 R = reflect( -L, N );
    float dd = max( dot( N, L ), 0.0 );
    float ds = pow( max( dot( N, R ), 0.0 ), shader.S );
    if ( dd <= 0.0 ) ds = 0.0;

    float Ia = shader.Ka;
    float Id = shader.Kd * dd;
    float Is = shader.Ks * ds;

    return( color * ( Ia + Id ) + Is );
}

vec3 blinnPhongShading( in vec3 color, in vec3 L, in vec3 N, in vec3 C )
{
    vec3 H = normalize( L + C );
    float dd = max( dot( N, L ), 0.0 );
    float ds = pow( max( dot( H, N ), 0.0 ), shader.S );
    if ( dd <= 0.0 ) ds = 0.0;

    float Ia = shader.Ka;
    float Id = shader.Kd * dd;
    float Is = shader.Ks * ds;

    return( color * ( Ia + Id ) + Is );
}

void main( void )
{
    vec3 L = normalize( gl_LightSource[0].position.xyz - position );
    vec3 N = normalize( normal );

#if   defined( ENABLE_LAMBERT_SHADING )
    vec3 shaded_color = lambertShading( gl_Color.xyz, L, N );

#elif defined( ENABLE_PHONG_SHADING )
    vec3 shaded_color = phongShading( gl_Color.xyz, L, N );

#elif defined( ENABLE_BLINN_PHONG_SHADING )
    vec3 C = normalize( -position );
    vec3 shaded_color = blinnPhongShading( gl_Color.xyz, L, N, C );

#else // DISABLE SHADING
    vec3 shaded_color = noShading( gl_Color.xyz );
#endif

    gl_FragColor.xyz = shaded_color;
    gl_FragColor.w = 1.0;
}
