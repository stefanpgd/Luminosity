#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;
class ShaderProgram;
class Texture;
class Star;

class Planet : public GameObject
{
public:
	Planet(Star* star);

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	Model* model;
	ShaderProgram* planetShader;
	Star* star;

	glm::vec3 planetColor;
	glm::vec3 starColor;

	float orbitAngle = 0.0f;
	float orbitSpeed = 0.0f;
	float orbitSize = 0.0f;
	float orbitYOffset = 0.0f;
};