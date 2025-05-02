#version 460 core
out vec4 FragColor;

struct Material {
    float shininess;
    sampler2D diffuse;
    vec3 specular;
}; 

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

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform PointLight pointLight;
uniform Material material;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
  // Properties
  // No clue what this mean
  // Plz learn vector calculation

  vec3 checkDiffuse = vec3(texture(material.diffuse, TexCoords));

  if(checkDiffuse.x == 0.0){
    // There isn't any diffuse map
    // Probably a light, set it as its ambient color
	  FragColor = vec4(pointLight.lightColor, 1.0);
  } else {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcPointLight(pointLight, norm, FragPos, viewDir);

	  FragColor = vec4(result, 1.0);
  }
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
