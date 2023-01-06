#version 460 core
in vec3 Normal;
in vec2 UV;
in vec3 FragPos;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

uniform vec3 color;
uniform float time;
uniform vec3 starColor;

uniform vec3 cameraPosition;
uniform float radius;
uniform vec3 sphereOrigin;

uniform sampler2D texture_albedo;

bool raySphereIntersection(vec3 ro, vec3 rd, vec3 so, float sr)
{
	float t = dot(so - ro, rd);
	vec3 P = ro + rd * t;
	float y = length(so - P);

	return y <= sr;
}

void main()
{
	vec3 rayDir = normalize(FragPos - cameraPosition);

	if(!raySphereIntersection(cameraPosition, rayDir, sphereOrigin, radius))
	{
		discard;
	}

	FragColor = vec4(1.0, 0.2, 0.1, 1.0);
	BrightColor = vec4(0, 0, 0, 1.0);
}