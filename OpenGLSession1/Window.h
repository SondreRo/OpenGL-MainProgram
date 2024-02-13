#pragma once
#include "GLFW/glfw3.h"

class Window
{
public:
	GLFWwindow* window;
	GLFWwindow* Setup(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, const char* title);
};
