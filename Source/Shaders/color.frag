#version 460 core
in vec3 Normal;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

void main()
{
	float intensity = 4;
	vec3 color = vec3(1.0, 0.51, 0.12);
	vec3 lightDir = normalize(vec3(0.2, -1.0, 0.1));
	vec3 norm = normalize(Normal);

	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuseColor = color * diff * intensity;
    FragColor = vec4(diffuseColor, 1.0);

	float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	if(brightness > 1.0)
	{
		BrightColor = vec4(FragColor.rgb, 1.0);
	}
	else 
	{
		BrightColor = vec4(0.0, 0.0, 0.0, 0.0);
	}
}