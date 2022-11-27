#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class ShaderProgram;
class Framebuffer;

class Renderer
{
public: 
	Renderer(const std::string& windowName);

	GLFWwindow* GetWindow();
	unsigned int GetWindowWidth();
	unsigned int GetWindowHeight();

	void StartFrame();
	void RenderFrame();

private:
	void SetupScreenQuad();

	GLFWwindow* window;
	Framebuffer* HDRColorBuffer;
	Framebuffer* screenBuffer;
	ShaderProgram* screenShader;

	const unsigned int windowWidth = 1080;
	const unsigned int windowHeight = 720;

	float quadVertices[24] = { 
		// positions   // texCoords
		1.0f,  1.0f, 0.0f,	1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,	1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
	   -1.0f,  1.0f, 0.0f,	0.0f, 1.0f
	};

	unsigned int screenVAO;
};