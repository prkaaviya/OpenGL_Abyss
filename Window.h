#pragma once

#include "cstdio"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	int Initialise();

	[[nodiscard]] GLint getBufferWidth() const { return bufferWidth; }
	[[nodiscard]] GLint getBufferHeight() const { return bufferHeight; }

	[[nodiscard]] bool getShouldClose() const { return glfwWindowShouldClose(mainWindow); }

	void swapBuffers() const { glfwSwapBuffers(mainWindow); }

	~Window();

private:
	GLFWwindow* mainWindow{};

	GLint width, height;
	GLint bufferWidth{}, bufferHeight{};
};