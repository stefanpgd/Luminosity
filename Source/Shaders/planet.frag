#version 460 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color;
uniform float time;
uniform vec3 starColor;

uniform sampler2D texture_albedo;

void main()
{
	float diff = dot(Normal, -FragPos);
	vec3 ambient = (color * 0.05);
	vec3 diffuse;

	if(diff > 0)
	{
		diffuse = (color * starColor) * diff;
	}

	vec3 col = ambient + diffuse;
	FragColor = vec4(col, 1.0);

	float brightness = dot(FragColor.rgb, vec3(0.8, 0.8, 0.8));
	if(brightness > 1.0)
	{
		BrightColor = vec4(col, 1.0) * 0.05;
	}
	else
	{
		BrightColor = vec4(0, 0, 0, 1.0);
	}
}