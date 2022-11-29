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

	star->Update(deltaTime);
	for(Planet* planet : planets)
	{
		planet->Update(deltaTime);
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

	if (glfwGetKey(window, GLFW_KEY_F))
	{
		flipSystem = true;
	}
	else
	{
		if (flipSystem)
		{
			flipSystem = false;
			for (Planet* planet : planets)
			{
				planet->FlipOrientation();
			}
		}
	}
}

void GameManager::Draw()
{
	star->Draw(camera);
	for(Planet* planet : planets)
	{
		planet->Draw(camera);
	}
}

void GameManager::ImGuiDraw()
{
	star->ImGuiDraw();
	for(Planet* planet : planets)
	{
		planet->ImGuiDraw();
	}
}

void GameManager::SetupSystem()
{
	planets.clear();

	star = new Star();

	int planetCount = RandomInRange(3, 7);
	for(int i = 0; i < planetCount; i++)
	{
		planets.push_back(new Planet(star));
	}
}
