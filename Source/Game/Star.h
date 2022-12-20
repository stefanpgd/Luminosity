#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>
#include <string>

class Model;
class ShaderProgram;
class Texture;

class Star : public GameObject
{
public:
	Star();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;


private:
	void Generate();

	Model* model;
	ShaderProgram* starShader;
	Texture* starBlur;

	float timer = 0.0f;
	float starBightness;

	// Statistics //
	// Based on actual parameters of stellar objects
	// https://en.wikipedia.org/wiki/Stellar_classification
	std::string starName;
	glm::vec3 starColor;
	char classification; 
	float solarMass;
	float solarRadii;
	float luminosity;

	int index = 0;
	char classifications[7]
	{
		'O', 'B', 'A', 'F', 'G', 'K', 'M'
	};
};