#include <glad/glad.h>

#include "Atmosphere.h"
#include "Planet.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"

Atmosphere::Atmosphere(Planet* planet)
{
	this->planet = planet;
	model = new Model("Assets/Models/Cube/Cube.gltf", &transform);
	atmosphereShader = new ShaderProgram("color.vert", "atmosphere.frag");
	atmosphereRadius = 0.12f;
}

void Atmosphere::Update(float simulationTime)
{
	transform.Position = planet->transform.Position;
}

void Atmosphere::Draw(Camera* camera)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	atmosphereShader->Bind();
	atmosphereShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	atmosphereShader->SetVec3("cameraPosition", camera->GetPosition());
	atmosphereShader->SetFloat("radius", atmosphereRadius);
	atmosphereShader->SetVec3("sphereOrigin", transform.Position);
	model->Draw(atmosphereShader);

	glDisable(GL_CULL_FACE);
}

void Atmosphere::ImGuiDraw()
{
}
