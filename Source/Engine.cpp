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
#include "Camera.h"

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
	Model model("Assets/Models/Sphere/Sphere.gltf", &transform);
	ShaderProgram shader("color.vert", "color.frag");
	Camera camera(glm::vec3(0.0, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 
		renderer->GetWindowWidth(), renderer->GetWindowHeight());

	while (isRunning)
	{
		renderer->StartFrame();

		// Input // 
		glfwPollEvents();
		if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			isRunning = false;
		}

		camera.Update(renderer->GetWindow(), 0.016);
		shader.Bind();
		shader.SetMat4("VPMatrix", camera.GetViewProjectionMatrix());
		model.Draw(&shader);

		renderer->RenderFrame();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}