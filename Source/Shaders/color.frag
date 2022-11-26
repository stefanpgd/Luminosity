#version 460 core
in vec3 Normal;

out vec4 FragColor;

void main()
{
	vec3 color = vec3(1.0, 0.21, 0.12);
	vec3 lightDir = normalize(vec3(0.2, -1.0, 0.1));
	vec3 norm = normalize(Normal);

	float diff = max(dot(norm, -lightDir), 0.0);
	vec3 diffuseColor = color * diff;
    FragColor = vec4(diffuseColor, 1.0);
}