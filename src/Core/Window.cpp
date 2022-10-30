#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Log.h"
#include "Core/Assert.h"
#include "Core/Input.h"
#include "Event/WindowEvent.h"
#include "Event/EventManager.h"
#include "Event/InputEvent.h"

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

		VALLY_INFO("Window destroyed!");
	}

	void Window::Update() const
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_pWindow);
	}

	GLFWwindow* Window::GetHandle() const
	{
		return m_pWindow;
	}

	void Window::SetSwapInterval(bool toggle)
	{
		if (toggle)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	void Window::Initialize()
	{
		I32 success = glfwInit();
		VALLY_ASSERT(success, "Could not initialize GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

		glfwSetFramebufferSizeCallback(m_pWindow, [](GLFWwindow* window, I32 width, I32 height)
		{
			auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data->m_width = width;
			data->m_height = height;

			glViewport(0, 0, width, height);

			EventManager::Post<WindowResizeEvent>(static_cast<U32>(width), static_cast<U32>(height));
		});

		glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow*)
		{
			EventManager::Post<WindowCloseEvent>();
		});

		glfwSetKeyCallback(m_pWindow, [](GLFWwindow*, I32 key, I32, I32 action, I32)
		{
			Input::s_keyboard.m_keys[key] = action;

			if (action == GLFW_PRESS || action == GLFW_REPEAT)
			{
				EventManager::Post<KeyPressedEvent>(static_cast<Key>(key));
			}
			else
			{
				EventManager::Post<KeyReleasedEvent>(static_cast<Key>(key));
			}
		});

		glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow*, I32 button, I32 action, I32)
		{
			Input::s_mouse.m_buttons[button] = action;

			if (action == GLFW_PRESS)
			{
				EventManager::Post<MouseButtonPressedEvent>(static_cast<MouseButton>(button));
			}
			else
			{
				EventManager::Post<MouseButtonReleasedEvent>(static_cast<MouseButton>(button));
			}
		});

		glfwSetScrollCallback(m_pWindow, [](GLFWwindow*, F64 xOffset, F64 yOffset)
		{
			EventManager::Post<MouseScrolledEvent>(glm::vec2(
				static_cast<F32>(xOffset),
				static_cast<F32>(yOffset)));
		});

		glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow*, F64 xPos, F64 yPos)
		{
			Input::s_mouse.m_previousPosition = Input::s_mouse.m_position;
			Input::s_mouse.m_position = glm::vec2(
				static_cast<F32>(xPos),
				static_cast<F32>(yPos)
			);

			EventManager::Post<MouseMovedEvent>(Input::s_mouse.m_position, Input::s_mouse.m_previousPosition);
		});

		glfwMakeContextCurrent(m_pWindow);
		SetSwapInterval(true);

		success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		VALLY_ASSERT(success, "Could not initialize GLAD!");

		glViewport(
			0, 0,
			static_cast<GLsizei>(m_data.m_width),
			static_cast<GLsizei>(m_data.m_height));

		VALLY_INFO("Window initialized!");
	}
}
