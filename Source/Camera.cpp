#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& front, const glm::vec3& up, float windowWidth, float windowHeight) :
	position(position), front(front), up(up), windowWidth(windowWidth), windowHeight(windowHeight)
{
	viewMatrix = glm::lookAt(position, position + front, up);
	projectionMatrix = glm::perspective(glm::radians(FOV), windowWidth / windowHeight, nearClip, farClip);
}

void Camera::Update(GLFWwindow* window, float deltaTime)
{
	viewMatrix = glm::lookAt(position, position + front, up);
	viewProjectionMatrix = projectionMatrix * viewMatrix;

	ProcessInput(window, deltaTime);
	ProcessMouse(window, deltaTime);
}

glm::mat4& Camera::GetViewProjectionMatrix()
{
	return viewProjectionMatrix;
}

glm::vec3& Camera::GetPosition()
{
	return position;
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime)
{
	float speed = cameraMovespeed * deltaTime;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += speed * front;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= speed * front;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(front, up)) * speed;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::ProcessMouse(GLFWwindow* window, float deltaTime)
{

}