#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform vec3 Diffuse;
uniform vec3 Specular;
uniform vec3 Highlight;
uniform float Shininess;

void main()
{    
  FragColor = vec4(Diffuse, 1.0f);
}
