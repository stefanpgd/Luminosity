#version 460 core
out vec4 FragColor;
  
in vec2 uv;

uniform sampler2D screenTexture;

void main()
{ 
    vec3 color = texture(screenTexture, uv).rgb;
    FragColor = vec4(color, 1.0);
}