#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
}

Window::Window(const GLint windowWidth, const GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
}

int Window::Initialise()
{
	if (!glfwInit())
	{
		printf("ERROR: Failed to initialise GLFW.\n");
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Abyss", nullptr, nullptr);
	if (!mainWindow)
	{
		printf("ERROR: Failed to create GLFW window.\n");
		glfwTerminate();
		return -2;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	glewExperimental = GL_TRUE;

	if (const GLenum error = glewInit(); error != GLEW_OK)
	{
		printf("ERROR: %p\n", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return -3;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	return 0;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
