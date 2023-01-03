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
	starShader->SetFloat("intensity", starBightness);
	starShader->SetVec3("color", starColor);
	starShader->SetFloat("time", timer);
	starBlur->Bind(starShader);

	model->Draw(starShader);
}

void Star::ImGuiDraw()
{
}

void Star::Generate()
{
	// Maybe match the actual fraction of all main-sequence stars instead of 1/7 chance
	//classification = classifications[RandomInRange(0, 7)]; 
	classification = 'G'; // classification for Sol
	printf(&classification);

	switch(classification)
	{
	case 'O':
		solarMass = RandomInRange(16.0f, 20.0f);
		solarRadii = RandomInRange(6.6f, 8.5f);
		luminosity = RandomInRange(30000.0f, 40000.0f);
		starBightness = RandomInRange(2.5f, 4.0f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(0.60784, 0.69020f, 1.0f),
			glm::vec3(0.57255, 0.70980f, 1.0f), Random01());
		break;

	case 'B':
		solarMass = RandomInRange(2.1f, 16.0f);
		solarRadii = RandomInRange(1.8f, 6.6f);
		luminosity = RandomInRange(25.0f, 30000.0f);
		starBightness = RandomInRange(2.5f, 4.0f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(0.66667f, 0.74902f, 1.0f),
			glm::vec3(0.63529f, 0.75294f, 1.0f), Random01());
		break;

	case 'A':
		solarMass = RandomInRange(1.4f, 2.1f);
		solarRadii = RandomInRange(1.4f, 1.8f);
		luminosity = RandomInRange(5.0f, 25.0f);
		starBightness = RandomInRange(2.5f, 4.0f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(0.79216f, 0.84314f, 1.0f),
			glm::vec3(0.83529f, 0.87843f, 1.0f), Random01());
		break;

	case 'F':
		solarMass = RandomInRange(1.04f, 1.4f);
		solarRadii = RandomInRange(1.15f, 1.4f);
		luminosity = RandomInRange(1.5f, 5.0f);
		starBightness = RandomInRange(2.0f, 3.5f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(0.97255f, 0.96863f, 1.0f),
			glm::vec3(0.97647f, 0.96078f, 1.0f), Random01());
		break;

	case 'G':
		solarMass = RandomInRange(0.8f, 1.04f);
		solarRadii = RandomInRange(0.96f, 1.15f);
		luminosity = RandomInRange(0.6f, 1.5f);
		starBightness = RandomInRange(1.75f, 3.25f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(1.0f, 0.9568f, 0.91765f),
			glm::vec3(1.0f, 0.92941f, 0.89020f), Random01());
		break;

	case 'K':
		solarMass = RandomInRange(0.45f, 0.8f);
		solarRadii = RandomInRange(0.7f, 0.96f);
		luminosity = RandomInRange(0.08f, 0.6f);
		starBightness = RandomInRange(1.5f, 3.0f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(1.0f, 0.82353f, 0.63137f),
			glm::vec3(1.0f, 0.85490f, 0.70980f), Random01());
		break;

	case 'M':
		solarMass = RandomInRange(0.08f, 0.45f);
		solarRadii = RandomInRange(0.03f, 0.7f);
		luminosity = RandomInRange(0.01f, 0.08f);
		starBightness = RandomInRange(1.0f, 2.5f);

		transform.Scale = glm::vec3(solarRadii, solarRadii, solarRadii);
		starColor = glm::mix(glm::vec3(1.0f, 0.80000f, 0.43529f),
			glm::vec3(1.0f,  0.70980f,  0.42353f), Random01());
		break;
	}

	starName = "Star - " + classification;
}

glm::vec3& Star::GetColor() { return starColor; }
float Star::GetSolarRadii() { return solarRadii; }
