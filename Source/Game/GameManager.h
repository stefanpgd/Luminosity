#pragma once
#include <vector>
#include <GLFW/glfw3.h>

class GameObject;
class Camera;
class Star;
class Planet;

class GameManager
{
public:
	GameManager(GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight);

	void Update(float deltaTime);
	void Draw();
	void ImGuiDraw();

private:
	void SetupSystem();

	GLFWwindow* window;
	Camera* camera;
	Star* star;
	std::vector<Planet*> planets;
	bool regenerateSystem = false;
	bool flipSystem = false;
};