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

	satelliteColor = glm::vec3(Random01(), Random01(), Random01());

	orbitAngle = RandomInRange(0.0, 500.0);
	orbitSpeed = RandomInRange(10, 25.0);
	orbitSize = RandomInRange(3, 8);
	orbitYOffset = RandomInRange(-0.4, 0.4);

	float scale = RandomInRange(0.15, 0.56);
	transform.Scale = glm::vec3(scale, scale, scale);

	float roll = Random01();

	if (roll > 0.5)
	{
		satellites.push_back(new Satellite(star, this));
	}
}

void Planet::FlipOrientation()
{
	drawFlipped = !drawFlipped;

	for (Satellite* satellite : satellites)
	{
		satellite->FlipOrientation();
	}
}

void Planet::Update(float deltaTime)
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

	transform.Position = glm::vec3(x, y, z);

	for (Satellite* satellite : satellites)
	{
		satellite->Update(deltaTime);
	}
}

void Planet::Draw(Camera* camera)
{
	planetShader->Bind();
	planetShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	planetShader->SetVec3("color", satelliteColor);
	//planetShader->SetVec3("starColor", star->starColor);

	model->Draw(planetShader);

	for (Satellite* satellite : satellites)
	{
		satellite->Draw(camera);
	}
}

void Planet::ImGuiDraw()
{
}

glm::vec3& Planet::GetPosition()
{
	return transform.Position;
}
