#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Framebuffer.h"
#include "ShaderProgram.h"
#include "ScreenQuad.h"

Renderer::Renderer(const std::string& windowName)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLAD // 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Error: Failed to initialize GLAD!\n");
		return;
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);

	HDRColorBuffer = new Framebuffer(windowWidth, windowHeight, true);
	screenShader = new ShaderProgram("screen.vert", "screen.frag");
	screenQuad = new ScreenQuad();
}

GLFWwindow* Renderer::GetWindow()
{
	return window;
}

unsigned int Renderer::GetWindowWidth()
{
	return windowWidth;
}

unsigned int Renderer::GetWindowHeight()
{
	return windowHeight;
}

void Renderer::StartFrame()
{
	HDRColorBuffer->BindBuffer();
}

void Renderer::RenderFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	screenShader->Bind();
	screenShader->SetInt("screenTexture", 0);
	HDRColorBuffer->BindTexture(0);
	screenQuad->Render();

	glfwSwapBuffers(window);
}