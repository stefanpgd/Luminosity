#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;
class ShaderProgram;
class Texture;

class Planet : public GameObject
{
public:
	Planet(glm::vec3 starColor);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	Model* model;
	ShaderProgram* planetShader;

	glm::vec3 planetColor;
	glm::vec3 starColor;

	float orbitAngle = 0.0f;
	float orbitSpeed = 0.0f;
	float orbitSize = 0.0f;
};