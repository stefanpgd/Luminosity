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
	glm::vec3 atmosphereColor;
};