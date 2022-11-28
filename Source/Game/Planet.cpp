#include "Planet.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"
#include <imgui.h>
#include <string>
#include "../Utilities.h"

Planet::Planet()
{
	model = new Model("Assets/Models/Sphere/Sphere.gltf", &transform);
	planetShader = new ShaderProgram("color.vert", "planet.frag");

	planetColor = glm::vec3(Random01(), Random01(), Random01());

	orbitAngle = RandomInRange(0.0, 500.0);
	orbitSpeed = RandomInRange(1.0, 4.0);
	orbitSize = RandomInRange(3, 8);

	float scale = RandomInRange(0.15, 0.56);
	transform.Scale = glm::vec3(scale, scale, scale);
}

void Planet::Update(float deltaTime)
{
	orbitAngle += deltaTime * orbitSpeed;

	float x = cosf(glm::radians(orbitAngle)) * orbitSize;
	float y = sinf(glm::radians(orbitAngle)) * orbitSize;

	transform.Position = glm::vec3(x, y, 0.0);
}

void Planet::Draw(Camera* camera)
{
	planetShader->Bind();
	planetShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	planetShader->SetVec3("color", planetColor);

	model->Draw(planetShader);
}

void Planet::ImGuiDraw()
{
}
