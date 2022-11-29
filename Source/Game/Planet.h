#pragma once
#include "GameObject.h"
#include <vector>
#include <glm/glm.hpp>

class Model;
class ShaderProgram;
class Texture;
class Star;
class Satellite;

class Planet : public GameObject
{
public:
	Planet(Star* star);

	void FlipOrientation();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

	glm::vec3& GetPosition();

private:
	Model* model;
	ShaderProgram* planetShader;
	Star* star;

	std::vector<Satellite*> satellites;

	glm::vec3 satelliteColor;
	glm::vec3 starColor;

	float orbitAngle = 0.0f;
	float orbitSpeed = 0.0f;
	float orbitSize = 0.0f;
	float orbitYOffset = 0.0f;

	bool drawFlipped = false;
};