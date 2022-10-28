#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Vally
{
	Window::Window(int width, int height, const std::string& title) :
		mWindow(nullptr), mData({width, height, title})
	{
		Initialize();
	}

	Window::~Window()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(mWindow);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(mWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::Initialize()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(
			mData.Width, 
			mData.Height, 
			mData.Title.c_str(), 
			nullptr, 
			nullptr);

		glfwSetWindowUserPointer(mWindow, &mData);

		glfwMakeContextCurrent(mWindow);
		glfwSwapInterval(1);

		gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

		glViewport(0, 0, mData.Width, mData.Height);
	}
}
