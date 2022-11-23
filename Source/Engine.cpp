#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void GLFWErrorCallback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}