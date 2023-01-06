#include <glad/glad.h>

#include "Atmosphere.h"
#include "Planet.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"

#include <imgui.h>

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

	ImGui::Begin("Atmosphere");
	ImGui::ColorEdit3("Color", &atmosphereColor[0]);
	ImGui::ColorEdit3("Color 2", &atmosphereColor2[0]);
	ImGui::DragFloat("Density", &atmosphereDensity, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Brightness", &bloomIntensity, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat("Radius", &atmosphereRadius, 0.001f);
	ImGui::DragFloat("Cutoff", &cutoff, 0.001f);
	ImGui::DragFloat("Max", &max, 0.001f);
	ImGui::End();
}

void Atmosphere::Draw(Camera* camera)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	atmosphereShader->Bind();
	atmosphereShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	atmosphereShader->SetVec3("cameraPosition", camera->GetPosition());
	atmosphereShader->SetVec3("sphereOrigin", transform.Position);
	atmosphereShader->SetVec3("color1", atmosphereColor);
	atmosphereShader->SetVec3("color2", atmosphereColor2);
	atmosphereShader->SetFloat("radius", atmosphereRadius);
	atmosphereShader->SetFloat("bloomIntensity", bloomIntensity);
	atmosphereShader->SetFloat("atmosphereDensity", atmosphereDensity);
	atmosphereShader->SetFloat("cutoff", cutoff);
	atmosphereShader->SetFloat("maxBright", max);
	model->Draw(atmosphereShader);

	glDisable(GL_CULL_FACE);
}

void Atmosphere::ImGuiDraw()
{
}
