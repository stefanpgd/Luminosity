#include "Planet.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"
#include "../Utilities.h"
#include <imgui.h>
#include <string>
#include "Star.h"
#include "Satellite.h"

Planet::Planet(Star* star)
{
	this->star = star;

	model = new Model("Assets/Models/Sphere/Sphere.gltf", &transform);
	planetShader = new ShaderProgram("color.vert", "planet.frag");

	Generate();
}

void Planet::Update(float deltaTime)
{
	angleFromStar += deltaTime * orbitalSpeed;

	float x = cosf(glm::radians(angleFromStar)) * distanceFromStar;
	//float y = cosf(glm::radians(angleFromStar)) * orbitYOffset;
	float y = 0.0f;
	float z = sinf(glm::radians(angleFromStar)) * distanceFromStar;

	transform.Position = glm::vec3(x, y, z);
}


void Planet::Draw(Camera* camera)
{
	planetShader->Bind();
	planetShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	planetShader->SetVec3("color", planetColor);
	planetShader->SetVec3("starColor", star->GetColor());

	model->Draw(planetShader);
}

void Planet::ImGuiDraw() {}

void Planet::Generate()
{
	planetName = "Planet X";
	planetColor = glm::vec3(Random01(), Random01(), Random01());

	earthMass = 1.0f;
	earthRadii = 1.0f;
	orbitalSpeed = 15.0f;
	angleFromStar = 0.0f;
	distanceFromStar = 15.0f + star->GetSolarRadii();
}