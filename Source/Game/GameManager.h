#pragma once
#include <vector>
#include <GLFW/glfw3.h>

class GameObject;
class Camera;
class StarSystem;

class GameManager
{
public:
	GameManager(GLFWwindow* window, unsigned int windowWidth, unsigned int windowHeight);

	void Update(float deltaTime);
	void Draw();
	void ImGuiDraw();

private:
	GLFWwindow* window;
	Camera* camera;
	StarSystem* starSystem;
	bool regenerateSystem = false;
};