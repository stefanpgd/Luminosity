#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const int windowWidth = 1080;
const int windowHeight = 720;

static void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(void)
{
	bool running = true;

	glfwSetErrorCallback(GLFWErrorCallback);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Luminosity", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Initialize GLAD // 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Error: Failed to initialize GLAD!\n");
		return 0;
	}

	glViewport(0, 0, windowWidth, windowHeight);

	while (running)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window))
		{
			running = false;
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}