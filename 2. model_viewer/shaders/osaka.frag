#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform bool UseTexture;

void main()
{    
    if(UseTexture){
      FragColor = texture(texture_diffuse1, TexCoords);
    } else {
      FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}


