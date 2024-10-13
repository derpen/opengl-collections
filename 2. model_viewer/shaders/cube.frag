#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D firstTexture;

void main(){
  //FragColor = vec4(0.2, 0.6, 1.0, 1.0); // Blue color
  FragColor = texture(firstTexture, TexCoord);
}
