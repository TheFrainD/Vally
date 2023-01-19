#include "Engine.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/ResourceManager.h"
#include "Event/EventManager.h"
#include "glm/gtc/type_ptr.hpp"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/UniformBuffer.h"
#include "Scene/SceneManager.h"

constexpr auto WINDOW_WIDTH = 1280;
constexpr auto WINDOW_HEIGHT = 720;
constexpr auto WINDOW_TITLE = "Vally";

namespace Vally
{
	Engine::Engine()
		: m_window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
		, m_gui(m_window.GetHandle(), WINDOW_WIDTH, WINDOW_HEIGHT)
		, m_running(false)
	{
		Renderer::InitData();
	}

	void Engine::Run()
	{
		m_running = true;

		EventManager::Subscribe<WindowCloseEvent>(VALLY_EVENT_TCALLBACK(OnWindowClose, WindowCloseEvent));
		EventManager::Subscribe<KeyPressedEvent>(VALLY_EVENT_TCALLBACK(OnKeyPressed, KeyPressedEvent));

		ResourceManager::Load<Shader>("Standard shader", "assets/shaders/standard.glsl");
		ResourceManager::Load<Model>("Container", "assets/models/container/Container.obj", true);

		Scene* mainScene = SceneManager::CreateScene("MainScene");

		Node* container = mainScene->AddNode("root", "Container");
		container->m_model = ResourceManager::Get<Model>("Container");
		container->m_transform.m_scale = glm::vec3(0.025f);
		container->m_transform.m_rotation.x = 90.0f;
		container->m_transform.m_position.z = 2.0f;

		Node* container1 = mainScene->AddNode("Container", "Container1");
		container1->m_model = ResourceManager::Get<Model>("Container");
		container1->m_transform.m_position.x = 8.0f;

		F32 lastTime = 0.0f;
		while (m_running)
		{
			const F32 currentTime = glfwGetTime();
			const F32 deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			m_gui.GetFramebuffer().Bind();

			Renderer::Prepare();
			Renderer::SetClearColor({ 0.1f, 0.2f, 0.4f, 1.0f });
			Renderer::Clear();

			SceneManager::Render();

			Framebuffer::Unbind();

			m_gui.Render(deltaTime);

			m_window.Update();

			SceneManager::Update(deltaTime);
		}

		ResourceManager::UnloadAll();
		Renderer::DestroyData();
	}

	void Engine::OnWindowClose(WindowCloseEvent& event)
	{
		m_running = false;
		event.SetHandled();
	}

	void Engine::OnKeyPressed(KeyPressedEvent& event)
	{
		if (event.GetKey() == Key::Escape)
		{
			m_running = false;
			event.SetHandled();
		}
	}
}
