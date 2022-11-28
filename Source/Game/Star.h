#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

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

	glm::vec3 starColor;

private:
	Model* model;
	ShaderProgram* starShader;
	Texture* starBlur;

	float starIntensity;
	float time = 0.0f;
};