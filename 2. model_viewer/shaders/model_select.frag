#version 460 core
out vec4 FragColor;

uniform float modelIndex;

void main()
{    
  // TODO: 255 because pixel color can only go up to 255, and so far only using the Red channel
  // Can maybe made it so that other channel is also used if number is higher than 255 or whatever
  float redChannel = modelIndex / 255.0;
  FragColor = vec4(redChannel, 0.0f, 0.0f, 1.0f);
}


