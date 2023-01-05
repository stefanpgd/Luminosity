#include <glad/glad.h>

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

	model = new Model("Assets/Models/Cube/Cube.gltf", &transform);
	planetShader = new ShaderProgram("color.vert", "atmosphere.frag");

	Generate();
}

void Planet::Update(float simulationTime)
{
	angleFromStar += simulationTime * orbitalSpeed;
	planetRotation += 360.0f * simulationTime;

	float x = cosf(glm::radians(angleFromStar)) * distanceFromStar;
	float y = 0.0f;
	float z = sinf(glm::radians(angleFromStar)) * distanceFromStar;

	transform.Position = glm::vec3(x, y, z);
	transform.Rotation = glm::vec3(0.0f, planetRotation, 0.0f);
}


void Planet::Draw(Camera* camera)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	//glDisable(GL_CULL_FACE);

	planetShader->Bind();
	planetShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	planetShader->SetVec3("color", planetColor);
	planetShader->SetVec3("cameraPosition", camera->GetPosition());
	planetShader->SetVec3("starColor", star->GetColor());
	planetShader->SetFloat("radius", earthRadii);
	planetShader->SetVec3("sphereOrigin", transform.Position);

	model->Draw(planetShader);
}

void Planet::ImGuiDraw() {}

void Planet::Generate()
{
	planetName = "Planet X";
	planetColor = glm::vec3(Random01(), Random01(), Random01());

	earthMass = 1.0f;
	earthRadii = 1.0f / 10.0f;
	transform.Scale = glm::vec3(earthRadii);

	orbitalSpeed = 1.0f;
	angleFromStar = 90.0f;
	distanceFromStar = star->GetSolarRadii() + 5.0f;
}