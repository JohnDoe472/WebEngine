precision mediump float;
varying vec3 fragPos;
varying vec2 texCoord;
varying vec3 normal;

struct Material
{
    sampler2D albedo;
    sampler2D normal;
    sampler2D metallic;
    sampler2D roughness;
    sampler2D ao;
    float shininess;
};

struct DirLight
{
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    vec3 attenuation;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[3];
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = vec3(texture2D(material.normal, texCoord));
    norm = normalize(norm * 2.0 - vec3(1.0));
    vec3 viewDir = normalize(viewPos - fragPos);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for (int i = 0; i < 3; ++i)
        result += CalcPointLight(pointLights[i], norm, fragPos, viewDir);

    gl_FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture2D(material.albedo, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.albedo, texCoord));
    //vec3 specular = light.specular * spec * vec3(texture2D(material.specTex, texCoord));
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * distance + light.attenuation.z * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture2D(material.albedo, texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.albedo, texCoord));
    //vec3 specular = light.specular * spec * vec3(texture2D(material.specTex, texCoord));
    vec3 specular = light.specular * spec;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
