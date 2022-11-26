#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
public: 
	Renderer(const std::string& windowName);

	GLFWwindow* GetWindow();

	void StartFrame();
	void RenderFrame();

private:
	const unsigned int windowWidth = 1080;
	const unsigned int windowHeight = 720;

	GLFWwindow* window;
};