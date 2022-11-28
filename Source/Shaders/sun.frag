#version 460 core
in vec3 Normal;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color;
uniform float intensity;

void main()
{
	vec3 col = color * intensity;
	FragColor = vec4(col, 1.0);
	BrightColor = vec4(col, 1.0);
}