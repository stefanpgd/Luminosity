#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram;
class Framebuffer;
class ScreenQuad;

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
	GLFWwindow* window;
	Framebuffer* HDRColorBuffer;
	ShaderProgram* screenShader;
	ShaderProgram* blurShader;
	ScreenQuad* screenQuad;

	const unsigned int windowWidth = 1080;
	const unsigned int windowHeight = 720;
	float exposure = 1.0f;

	unsigned int pingpongFBO[2];
	unsigned int pingpongBuffer[2];
};