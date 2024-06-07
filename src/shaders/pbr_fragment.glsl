#extension GL_OES_standard_derivatives : enable

precision mediump float;
varying vec3 fragPos;
varying vec2 texCoords;
varying vec3 normal;
varying mat3 tbn;

struct Material
{
    sampler2D albedo;
    sampler2D normal;
    sampler2D metallic;
    sampler2D roughness;
    sampler2D ao;
};

struct PointLight
{
    vec3 position;
    vec3 color;
    
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform PointLight pointLights[3];
uniform vec3 camPos;

const float PI = 3.14159265359;

vec4 getTexture( sampler2D texture, vec2 texCoords )
{
    vec4 color = texture2D( texture, texCoords );
    if ( color.r == 0.0 && color.g == 0.0 && color.b == 0.0 && color.a == 0.0 )
    {
        return vec4( 1.0 );
    }

    return color;
}

vec3 getNormalFromMap()
{
    vec4 color = texture2D( material.normal, texCoords );

    if ( color.r == 0.0 && color.g == 0.0 && color.b == 0.0 && color.a == 0.0 )
    {
        return normalize( normal );
    }

    vec3 tangentNormal = color.xyz * 2.0 - 1.0;
    return normalize( tbn * tangentNormal );
}

float getPBRComponent( sampler2D texture, vec2 texCoords )
{
    vec4 color = texture2D( texture, texCoords );
    if ( color.r == 0.0 && color.g == 0.0 && color.b == 0.0 && color.a != 0.0 )
    {
        return color.a;
    }

    return color.r;
}

float luminosityFromAttenuation( PointLight light )
{
    float distance    = length( light.position - fragPos );
    float attenuation = light.constant + light.linear * distance + light.quadratic * ( distance * distance );
    return 1.0 / attenuation;
}

float distributionGGX( vec3 N, vec3 H, float roughness )
{
    float a      = roughness * roughness;
    float a2     = a * a;
    float NdotH  = max( dot( N, H ), 0.0 );
    float NdotH2 = NdotH * NdotH;
	
    float num   = a2;
    float denom = ( NdotH2 * ( a2 - 1.0 ) + 1.0 );
    denom = PI * denom * denom;
	
    return num / denom;
}

float geometrySchlickGGX( float NdotV, float roughness )
{
    float r = ( roughness + 1.0 );
    float k = ( r * r ) / 8.0;

    float num   = NdotV;
    float denom = NdotV * ( 1.0 - k ) + k;

    return num / denom;
}

float geometrySmith( vec3 N, vec3 V, vec3 L, float roughness )
{
    float NdotV = max( dot( N, V ), 0.0 );
    float NdotL = max( dot( N, L ), 0.0 );
    float ggx2 = geometrySchlickGGX( NdotV, roughness );
    float ggx1 = geometrySchlickGGX( NdotL, roughness );

    return ggx1 * ggx2;
}

vec3 fresnelSchlick( float cosTheta, vec3 F0 )
{
    return F0 + ( 1.0 - F0 ) * pow( 1.0 - cosTheta, 5.0 );
}

void main()
{
    vec4 albedoRGBA = getTexture( material.albedo, texCoords );
    vec3 albedo     = pow( albedoRGBA.rgb, vec3( 2.2 ) );
    float metallic  = getPBRComponent( material.metallic, texCoords );
    float roughness = getPBRComponent( material.roughness, texCoords );
    float ao        = getPBRComponent( material.ao, texCoords );
    
    vec3 N = normalize( getNormalFromMap() );
    vec3 V = normalize( camPos - fragPos );

    vec3 F0 = vec3( 0.04 ); 
    F0 = mix( F0, albedo, metallic );
	           
    // reflectance equation
    vec3 Lo = vec3( 0.0 );

    for ( int i = 0; i < 3; ++i )
    {
        vec3 L = normalize( pointLights[ i ].position - fragPos );
        vec3 H = normalize( V + L );
        float lightCoeff = luminosityFromAttenuation( pointLights[ i ] ) * pointLights[ i ].intensity;
        vec3 radiance = pointLights[ i ].color * lightCoeff;

        // cook-torrance brdf
        float NDF = distributionGGX( N, H, roughness );
        float G   = geometrySmith( N, V, L, roughness );
        vec3 F    = fresnelSchlick( max( dot( H, V ), 0.0 ), F0 );
        
        vec3 kS = F;
        vec3 kD = vec3( 1.0 ) - kS;
        kD *= 1.0 - metallic;
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max( dot( N, V ), 0.0 ) * max( dot( N, L ), 0.0 );
        vec3 specular     = numerator / max( denominator, 0.0001 );
            
        // add to outgoing radiance Lo
        float NdotL = max( dot( N, L ), 0.0 );
        Lo += ( kD * albedo / PI + specular ) * radiance * NdotL;
    }

    vec3 ambient = vec3( 0.03 ) * albedo * ao;
    vec3 color = ambient + Lo;

    color = color / ( color + vec3( 1.0 ) );
    color = pow( color, vec3( 1.0 / 2.2 ) ); 

    gl_FragColor = vec4( color, albedoRGBA.a );
}
