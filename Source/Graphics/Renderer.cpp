#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Framebuffer.h"
#include "ShaderProgram.h"
#include "ScreenQuad.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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

	HDRColorBuffer = new Framebuffer(windowWidth, windowHeight, true, 2);
	screenShader = new ShaderProgram("screen.vert", "screen.frag");
	screenQuad = new ScreenQuad();

	screenShader->Bind();
	screenShader->SetInt("screenTexture", 0);
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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	HDRColorBuffer->BindBuffer();

	ImGui::Begin("Screen Settings");
	ImGui::DragFloat("Exposure", &exposure, 0.01f, 0.01f);
	ImGui::End();
}

void Renderer::RenderFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	screenShader->Bind();
	screenShader->SetFloat("exposure", exposure);
	HDRColorBuffer->BindTexture(0, 1);
	screenQuad->Render();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}