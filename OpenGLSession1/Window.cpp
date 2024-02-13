#include "Window.h"
#include "iostream"

GLFWwindow* Window::Setup(unsigned SCR_WIDTH, unsigned SCR_HEIGHT, const char* title)
{
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	return window;
}
