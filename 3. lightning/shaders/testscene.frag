#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

in vec3 Diffuse;
in vec3 Specular;
in vec3 Highlight;
in float Shininess;

void main()
{    
  FragColor = vec4(Diffuse, 1.0f);
}
