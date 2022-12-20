#include "GameManager.h"
#include "GameObject.h"
#include "../Camera.h"

#include "../Utilities.h"
#include "StarSystem.h"

GameManager::GameManager(GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight)
{
	this->window = window;
	camera = new Camera(window, glm::vec3(0.0, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f), windowWidth, windowHeight);

	starSystem = new StarSystem();
}

void GameManager::Update(float deltaTime)
{
	camera->Update(deltaTime);
	starSystem->Update(deltaTime);
}

void GameManager::Draw()
{
	starSystem->Draw(camera);
}

void GameManager::ImGuiDraw()
{

}