#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, TexCoord);
}
