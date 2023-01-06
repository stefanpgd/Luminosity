#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;
class ShaderProgram;
class Texture;
class Star;
class Atmosphere;

class Planet : public GameObject
{
public:
	Planet(Star* star);

	virtual void Update(float simulationTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	void Generate();

	Star* star;
	Atmosphere* atmosphere;

	Model* model;
	ShaderProgram* planetShader;

	float planetRotation = 0.0f;

	// Statistics // 
	std::string planetName;
	glm::vec3 planetColor;
	float earthMass;
	float earthRadii;
	float orbitalSpeed;
	float angleFromStar;
	float distanceFromStar; // Expressed in AU (Astromincal Units)
};