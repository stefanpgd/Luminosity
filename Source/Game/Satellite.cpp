#include "Satellite.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"
#include "../Utilities.h"
#include <imgui.h>
#include <string>
#include "Planet.h"
#include "Star.h"

Satellite::Satellite(Star* star, Planet* planet)
{
	this->star = star;
	this->planet = planet;

	model = new Model("Assets/Models/Sphere/Sphere.gltf", &transform);
	planetShader = new ShaderProgram("color.vert", "planet.frag");

	satelliteColor = glm::vec3(Random01(), Random01(), Random01());

	orbitAngle = RandomInRange(0.0, 500.0);
	orbitSpeed = RandomInRange(40, 80.0);
	orbitSize = RandomInRange(0.75, 1.5);
	orbitYOffset = RandomInRange(-1, 1);

	float scale = RandomInRange(0.05, 0.16);
	transform.Scale = glm::vec3(scale, scale, scale);
}

void Satellite::FlipOrientation()
{
	drawFlipped = !drawFlipped;
}

void Satellite::Update(float deltaTime)
{
	orbitAngle += deltaTime * orbitSpeed;

	float x = cosf(glm::radians(orbitAngle)) * orbitSize;
	float y = cosf(glm::radians(orbitAngle)) * orbitYOffset;
	float z = sinf(glm::radians(orbitAngle)) * orbitSize;

	if (drawFlipped)
	{
		float t = y;

		y = z;
		z = t;
	}

	transform.Position = glm::vec3(x, y, z) + planet->GetPosition();
}

void Satellite::Draw(Camera* camera)
{
	planetShader->Bind();
	planetShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	planetShader->SetVec3("color", satelliteColor);
	planetShader->SetVec3("starColor", star->starColor);

	model->Draw(planetShader);
}

void Satellite::ImGuiDraw()
{
}