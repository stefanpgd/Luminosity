#include "GameManager.h"
#include "GameObject.h"
#include "../Camera.h"

#include "Star.h"
#include "Planet.h"
#include "../Utilities.h"

GameManager::GameManager(GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight)
{
	this->window = window;
	camera = new Camera(window, glm::vec3(0.0, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f), windowWidth, windowHeight);

	SetupSystem();
}

void GameManager::Update(float deltaTime)
{
	camera->Update(deltaTime);

	for(GameObject* gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	if(glfwGetKey(window, GLFW_KEY_R))
	{
		regenerateSystem = true;
	}
	else
	{
		if(regenerateSystem)
		{
			regenerateSystem = false;
			SetupSystem();
		}
	}
}

void GameManager::Draw()
{
	for(GameObject* gameObject : gameObjects)
	{
		gameObject->Draw(camera);
	}
}

void GameManager::ImGuiDraw()
{
	for(GameObject* gameObject : gameObjects)
	{
		gameObject->ImGuiDraw();
	}
}

void GameManager::SetupSystem()
{
	gameObjects.clear();

	Star* star = new Star();
	gameObjects.push_back(star);

	int planetCount = RandomInRange(3, 7);
	for(int i = 0; i < planetCount; i++)
	{
		gameObjects.push_back(new Planet(star->starColor));
	}
}
