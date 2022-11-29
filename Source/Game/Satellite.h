#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;
class ShaderProgram;
class Texture;
class Planet;
class Star;

class Satellite : public GameObject
{
public:
	Satellite(Star* star, Planet* planet);

	void FlipOrientation();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	Model* model;
	ShaderProgram* planetShader;
	Planet* planet;
	Star* star;

	glm::vec3 satelliteColor;

	float orbitAngle = 0.0f;
	float orbitSpeed = 0.0f;
	float orbitSize = 0.0f;
	float orbitYOffset = 0.0f;

	bool drawFlipped = false;
};