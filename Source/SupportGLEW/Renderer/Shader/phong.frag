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


float lambertShading( in vec3 L, in vec3 N )
{
    float dd = max( dot( N, L ), 0.0 );

    float Ia = shader.Ka;
    float Id = shader.Kd * dd;

    return( Ia + Id );
}

float phongShading( in vec3 L, in vec3 N )
{
    vec3 R = 2.0 * dot( N, L ) * N - L;
    float dd = max( dot( N, L ), 0.0 );
    float ds = pow( max( dot( N, R ), 0.0 ), shader.S );

    float Ia = shader.Ka;
    float Id = shader.Kd * dd;
    float Is = shader.Ks * ds;

    return( Ia + Id + Is );
}

float blinnPhongShading( in vec3 L, in vec3 N, in vec3 C )
{
    vec3 H = normalize( L + C );
    float dd = max( dot( N, L ), 0.0 );
    float ds = pow( max( dot( H, N ), 0.0 ), shader.S );

    float Ia = shader.Ka;
    float Id = shader.Kd * dd;
    float Is = shader.Ks * ds;

    return( Ia + Id + Is );
}

void main( void )
{
    vec3 L = normalize( gl_LightSource[0].position.xyz - position );
    vec3 N = normalize( normal );

#if   defined( ENABLE_LAMBERT_SHADING )
    float attenuate = lambertShading( L, N );
#elif defined( ENABLE_PHONG_SHADING )
    float attenuate = phongShading( L, N );
#elif defined( ENABLE_BLINN_PHONG_SHADING )
    vec3 C = normalize( position );
    float attenuate = phongShading( L, N, C );
#else // NO SHADING
    float attenuate = 1.0;
#endif

    gl_FragColor.xyz = gl_Color.xyz * attenuate;
    gl_FragColor.w = 1.0;
}
