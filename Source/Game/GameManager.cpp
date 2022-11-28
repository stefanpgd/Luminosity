#include "GameManager.h"
#include "GameObject.h"
#include "../Camera.h"

#include "Star.h"

GameManager::GameManager(GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight)
{
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
	gameObjects.push_back(new Star());
}
