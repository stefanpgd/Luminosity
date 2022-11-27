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
	blurShader = new ShaderProgram("screen.vert", "gaussianBlur.frag");
	screenQuad = new ScreenQuad();

	screenShader->Bind();
	screenShader->SetInt("screenTexture", 0);
	screenShader->SetInt("bloomTexture", 1);
	
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongBuffer);
	for(unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0
		);
	}
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

	bool horizontal = true, first_iteration = true;
	int amount = 10;
	blurShader->Bind();
	blurShader->SetInt("image", 0);
	for(unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
		blurShader->SetInt("horizontal", horizontal);

		if(first_iteration)
		{
			HDRColorBuffer->BindTexture(0, 1);
		} 
		else
		{
			glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
		}

		screenQuad->Render();

		horizontal = !horizontal;
		if(first_iteration)
			first_iteration = false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	screenShader->Bind();
	screenShader->SetFloat("exposure", exposure);
	HDRColorBuffer->BindTexture(0, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, pingpongBuffer[!horizontal]);
	screenQuad->Render();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}