#include "Star.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"
#include <imgui.h>
#include <string>
#include "../Utilities.h"

Star::Star()
{
	model = new Model("Assets/Models/Sphere/Sphere.gltf", &transform);
	starShader = new ShaderProgram("color.vert", "sun.frag");

	std::string path = "Assets/Textures/starFade.png";
	starBlur = new Texture(path, TextureType::Albedo, true);

	starColor = glm::vec3(RandomInRange(0.85, 1.0), RandomInRange(0.1, 1.0), RandomInRange(0.1, 1.0));
	starIntensity = RandomInRange(1.25, 3.0f);
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
	starBlur->Bind(starShader);

	model->Draw(starShader);
}

void Star::ImGuiDraw()
{
	ImGui::Begin("Star");
	ImGui::DragFloat("Intensity", &starIntensity, 0.01f, 0.0, 10.0);
	ImGui::ColorEdit3("Color", &starColor[0]);
	ImGui::End();
}
