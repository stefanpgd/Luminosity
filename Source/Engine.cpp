#include "Engine.h"

// Graphics 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD
#include <iostream>
#include <string>

#include "Renderer.h"

static void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Engine::Engine()
{
	glfwSetErrorCallback(GLFWErrorCallback);
	glfwInit();

	renderer = new Renderer("Luminosity");
}

void Engine::Run()
{
	bool isRunning = true;
	GLFWwindow* window = renderer->GetWindow();

	while (isRunning)
	{
		renderer->StartFrame();

		// Input // 
		glfwPollEvents();

		if (glfwWindowShouldClose(window))
		{
			isRunning = false;
		}

		renderer->RenderFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}