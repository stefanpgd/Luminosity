#include "Star.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include <imgui.h>

Star::Star()
{
	model = new Model("Assets/Models/Sphere/Sphere.gltf", &transform);
	starShader = new ShaderProgram("color.vert", "sun.frag");

	starColor = glm::vec3(1.0f, 1.0f, 1.0f);
	starIntensity = 3.0f;
}

void Star::Update(float deltaTime)
{
	time += deltaTime;
}

void Star::Draw(Camera* camera)
{
	starShader->Bind();
	starShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	starShader->SetFloat("intensity", starIntensity);
	starShader->SetVec3("color", starColor);
	starShader->SetFloat("time", time);
	model->Draw(starShader);
}

void Star::ImGuiDraw()
{
	ImGui::Begin("Star");
	ImGui::DragFloat("Intensity", &starIntensity, 0.01f, 0.0, 10.0);
	ImGui::ColorEdit3("Color", &starColor[0]);
	ImGui::End();
}
