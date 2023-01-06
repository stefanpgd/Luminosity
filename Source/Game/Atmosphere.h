#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;
class ShaderProgram;
class Texture;
class Planet;

class Atmosphere : public GameObject
{
public:
	Atmosphere(Planet* planet);

	virtual void Update(float simulationTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	Planet* planet;
	Model* model;
	ShaderProgram* atmosphereShader;

	float atmosphereRadius;
	float atmosphereDensity = 0.2f;
	float bloomIntensity = 0.1f;
	float cutoff = 0.12f;
	float max = 1.0f;

	glm::vec3 atmosphereColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 atmosphereColor2 = glm::vec3(1.0f, 1.0f, 1.0f);
};