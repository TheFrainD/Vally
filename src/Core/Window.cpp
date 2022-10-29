#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Log.h"
#include "Core/Assert.h"

namespace Vally
{
	Window::Window(U32 width, U32 height, const std::string& title) :
		m_pWindow(nullptr), m_data({width, height, title})
	{
		VALLY_ASSERT(width > 0, "Window width must be greater than zero");
		VALLY_ASSERT(height > 0, "Window width must be greater than zero");
		Initialize();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_pWindow);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_pWindow);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::Initialize()
	{
		I32 success = glfwInit();
		VALLY_ASSERT(success, "Could not initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef VALLY_DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

		m_pWindow = glfwCreateWindow(
			static_cast<I32>(m_data.m_width),
			static_cast<I32>(m_data.m_height),
			m_data.m_title.c_str(), 
			nullptr, 
			nullptr);

		glfwSetWindowUserPointer(m_pWindow, &m_data);

		glfwMakeContextCurrent(m_pWindow);
		glfwSwapInterval(1);

		success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		VALLY_ASSERT(success, "Could not initialize GLAD!");

		glViewport(
			0, 0,
			static_cast<GLsizei>(m_data.m_width),
			static_cast<GLsizei>(m_data.m_height));
	}
}
