#version 460 core
out vec4 FragColor;

uniform float modelIndex;

void main()
{    
  float redChannel = modelIndex / 255.0;
  FragColor = vec4(redChannel, 0.0f, 0.0f, 1.0f);
}


