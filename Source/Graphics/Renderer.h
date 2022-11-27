#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer;
class PostProcessor;

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
	Framebuffer* sceneBuffer;
	PostProcessor* postProcessor;

	const unsigned int windowWidth = 1080;
	const unsigned int windowHeight = 720;
};