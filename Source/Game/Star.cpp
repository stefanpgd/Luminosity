#include "Star.h"
#include "../Graphics/Model.h"
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Texture.h"
#include "../Utilities.h"

#include <imgui.h>
#include <string>

Star::Star()
{
	model = new Model("Assets/Models/Sphere/Sphere.gltf", &transform);
	starShader = new ShaderProgram("color.vert", "sun.frag");

	std::string path = "Assets/Textures/starFade.png";
	starBlur = new Texture(path, TextureType::Albedo, true);

	Generate();
}

void Star::Update(float deltaTime)
{
	timer += deltaTime;
}

void Star::Draw(Camera* camera)
{
	starShader->Bind();
	starShader->SetMat4("VPMatrix", camera->GetViewProjectionMatrix());
	starShader->SetFloat("intensity", luminosity);
	starShader->SetVec3("color", starColor);
	starShader->SetFloat("time", timer);
	starBlur->Bind(starShader);

	model->Draw(starShader);
}

void Star::ImGuiDraw()
{
	ImGui::Begin("Star");
	ImGui::DragFloat("Intensity", &luminosity, 0.01f, 0.0, 10.0);
	ImGui::ColorEdit3("Color", &starColor[0]);
	ImGui::End();
}

void Star::Generate()
{
	// Generation with parameters of a class G star
	starName = "Star - A";
	classification = 'G'; // classification for Sol

	luminosity = RandomInRange(0.6f, 1.5f);
	solarMass = RandomInRange(0.8f, 1.04f);
	solarRadii = RandomInRange(0.98, 1.15f);
	transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);

	glm::vec3 yellow = glm::vec3(1.0f, 0.9568f, 0.91765f);
	glm::vec3 yellowWhite = glm::vec3(1.0f, 0.92941f, 0.89020f);

	starColor = glm::mix(yellow, yellowWhite, Random01());
}