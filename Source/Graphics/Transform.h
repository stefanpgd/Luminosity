#pragma once
#include <glm/glm.hpp>
#include <string>

class Transform
{
public:
	Transform();

	glm::mat4& GetModelMatrix();

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

private:
	glm::mat4 model;
};