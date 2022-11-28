#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class Model;
class ShaderProgram;

class Star : public GameObject
{
public:
	Star();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Camera* camera) override;
	virtual void ImGuiDraw() override;

private:
	Model* model;
	ShaderProgram* starShader;

	glm::vec3 starColor;
	float starIntensity;
	float time = 0.0f;
};