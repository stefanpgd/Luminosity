#include "Engine.h"

// Graphics 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Graphics/Renderer.h"

// STD
#include <iostream>
#include <string>

#include "Graphics/Model.h"
#include "Graphics/Transform.h"
#include "Graphics/ShaderProgram.h"

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

	Transform transform;
	Model model("Assets/Models/Sphere/sphere.gltf", &transform);
	ShaderProgram shader("color.vert", "color.frag");

	while (isRunning)
	{
		renderer->StartFrame();

		// Input // 
		glfwPollEvents();

		if (glfwWindowShouldClose(window))
		{
			isRunning = false;
		}

		shader.Bind();
		model.Draw(&shader);

		renderer->RenderFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}