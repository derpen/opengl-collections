#version 460 core
out vec4 FragColor;

struct Material {
    float shininess;
    sampler2D diffuse;
    vec3 specular;
	vec3 ambient;
}; 
uniform float checkDiffuse;

struct PointLight { 
    float constant;
    float linear;
    float quadratic;
	
    vec3 position;
    vec3 lightColor;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform PointLight pointLight;
uniform DirLight dirLight;
uniform Material material;

uniform float ambientStrength;
uniform vec3 ambientColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Diffuse? I'm not sure, why is it black
    // I c, because I'm not binding any texture
    // There isn't any texture right now lol
	//FragColor = vec4(vec3(texture(material.diffuse, TexCoords)), 1.0);
    FragColor = vec4(material.ambient, 1.0); // Cringe hack

    // Ambient
    FragColor += vec4(ambientStrength * ambientColor,1.0);

    // Directional Light
    FragColor += vec4(CalcDirLight(dirLight, norm, viewDir), 1.0);

    //// Single point light
    //// Currently giga broken, very shit
    //vec3 result = CalcPointLight(pointLight, norm, FragPos, viewDir);
    //FragColor += vec4(result, 1.0);
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
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // No texture
    vec3 specular = light.specular * spec * material.specular;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fragPos);
  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
  // combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

  //vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)); // Not using texture for specular
  vec3 specular = light.specular * spec * material.specular;

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  return (ambient + diffuse + specular);
}
