struct Volume
{
    vec3      ratio;     // ratio of the volume resolution (256x256x128 => 1:1:0.5)
    float     min_range; // min. range
    float     max_range; // max. range
    float     min_value; // min. scalar value
    float     max_value; // max. scalar value
    sampler3D data;      // volume data (scalar field)
};

struct Shader
{
    float Ka; // ambient
    float Kd; // diffuse
    float Ks; // specular
    float S;  // shininess
};

struct TransferFunction
{
    sampler1D data; // transfer function data
};

uniform sampler2D        entry_points;      // entry points (front face)
uniform sampler2D        exit_points;       // exit points (back face)
uniform vec3             offset;            // offset width for the gradient
uniform float            dt;                // sampling step
uniform float            opaque;            // opaque value
uniform vec3             light_position;    // light position
uniform Volume           volume;            // volume data
uniform Shader           shader;            // shading method
uniform TransferFunction transfer_function; // 1D transfer function


vec3 estimateGradient( in sampler3D v, in vec3 p, in vec3 o )
{
    float s0 = texture3D( v, p + vec3( o.x, 0.0, 0.0 ) ).w;
    float s1 = texture3D( v, p + vec3( 0.0, o.y, 0.0 ) ).w;
    float s2 = texture3D( v, p + vec3( 0.0, 0.0, o.z ) ).w;
    float s3 = texture3D( v, p - vec3( o.x, 0.0, 0.0 ) ).w;
    float s4 = texture3D( v, p - vec3( 0.0, o.y, 0.0 ) ).w;
    float s5 = texture3D( v, p - vec3( 0.0, 0.0, o.z ) ).w;

    return( vec3( s3 - s0, s4 - s1, s5 - s2 ) );
}

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
    // Entry and exit point.
    vec3 entry_point = volume.ratio * texture2D( entry_points, gl_TexCoord[0].st ).xyz;
    vec3 exit_point = volume.ratio * texture2D( exit_points, gl_TexCoord[0].st ).xyz;
    if ( entry_point == exit_point ) { discard; } // out of cube

    // Ray direction.
    vec3 direction = dt * normalize( exit_point - entry_point );
    float segment = distance( exit_point, entry_point );
    int nsteps = int( floor( segment / dt ) );

    // Ray traversal.
    vec3 position = entry_point;
    vec4 dst = vec4( 0.0, 0.0, 0.0, 0.0 );

    // Transfer function scale.
    float tfunc_scale = 1.0 / ( volume.max_value - volume.min_value );

    for ( int i = 0; i < nsteps; i++ )
    {
        // Get the scalar value from the 3D texture.
        vec3 volume_index = vec3( position / volume.ratio );
        vec4 value = texture3D( volume.data, volume_index );
        float scalar = mix( volume.min_range, volume.max_range, value.w );

        // Get the source color from the transfer function.
        float tfunc_index = ( scalar - volume.min_value ) * tfunc_scale;
        vec4 src = texture1D( transfer_function.data, tfunc_index );
        if ( src.a != 0.0 )
        {
            vec3 offset_index = vec3( offset / volume.ratio );
            vec3 normal = estimateGradient( volume.data, volume_index, offset_index );
            vec3 L = normalize( light_position - position );
            vec3 N = normalize( gl_NormalMatrix * normal );

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

            // Front-to-back composition.
            dst.rgb += ( 1.0 - dst.a ) * src.a * attenuate * src.rgb;
            dst.a += ( 1.0 - dst.a ) * src.a;

            // Early ray termination.
            if ( dst.a > opaque )
            {
                dst.a = 1.0;
                i = nsteps; // break
            }
        }

        position += direction;
    }

    gl_FragColor = dst;
}
