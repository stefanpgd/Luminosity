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

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	void Generate();

	Star* star;
	Model* model;
	ShaderProgram* planetShader;

	float timer = 0.0f;

	// Statistics // 
	std::string planetName;
	glm::vec3 planetColor;
	float earthMass;
	float earthRadii;
	float orbitalSpeed;
	float angleFromStar;
	float distanceFromStar; // Expressed in AU (Astromincal Units)
};