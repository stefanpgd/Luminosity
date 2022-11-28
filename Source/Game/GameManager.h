#pragma once
#include <vector>
#include <GLFW/glfw3.h>

class GameObject;
class Camera;

class GameManager
{
public:
	GameManager(GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight);

	void Update(float deltaTime);
	void Draw();
	void ImGuiDraw();

private:
	void SetupSystem();

	Camera* camera;
	std::vector<GameObject*> gameObjects;
};