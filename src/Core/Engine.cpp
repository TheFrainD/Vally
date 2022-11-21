#include "Engine.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>

#include "Core/Log.h"
#include "Core/Input.h"
#include "Core/ResourceManager.h"
#include "Event/EventManager.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;
constexpr auto WINDOW_TITLE = "Vally";

namespace Vally
{
	Engine::Engine()
		: m_window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
		, m_gui(m_window.GetHandle(), WINDOW_WIDTH, WINDOW_HEIGHT)
		, m_running(false)
	{
	}

	void Engine::Run()
	{
		m_running = true;

		EventManager::Subscribe<WindowCloseEvent>(VALLY_EVENT_TCALLBACK(OnWindowClose, WindowCloseEvent));
		EventManager::Subscribe<KeyPressedEvent>(VALLY_EVENT_TCALLBACK(OnKeyPressed, KeyPressedEvent));

		ResourceManager::Load<Shader>("Standard shader", "assets/shaders/standard.glsl");
		ResourceManager::Load<Texture>("Bricks texture", "assets/textures/Bricks/Bricks_Albedo.png");

		const std::vector<Vertex> vertices = {
			{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec2(1.0f, 1.0f)},
			{glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec2(1.0f, 0.0f)},
			{glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec2(0.0f, 0.0f)},
			{glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec2(0.0f, 1.0f)},
		};

		const std::vector<U32> indices = {
			0, 1, 3,
			1, 2, 3
		};

		auto bricksMaterial = std::make_shared<Material>();
		bricksMaterial->m_textures.m_albedo = ResourceManager::Get<Texture>("Bricks texture");
		bricksMaterial->m_shader = ResourceManager::Get<Shader>("Standard shader");

		ResourceManager::Load<Material>("Brick material", bricksMaterial);

		Mesh quad("Quad");
		quad.m_material = ResourceManager::Get<Material>("Brick material");
		quad.m_vertices = vertices;
		quad.m_indices = indices;
		quad.UpdateMesh();

		ResourceManager::Load<Model>("Backpack", "assets/models/container/Container.obj", true);
		ResourceManager::Get<Model>("Backpack")->Scale(glm::vec3(0.02f));

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

			quad.m_material->m_shader->SetUniformMatrix4("uProjection", m_gui.GetCamera().GetProjection());
			quad.m_material->m_shader->SetUniformMatrix4("uView", m_gui.GetCamera().GetView());
			quad.m_material->m_shader->SetUniformMatrix4("uModel", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

			//quad.Draw();

			ResourceManager::Get<Model>("Backpack")->Draw(m_gui.GetCamera());

			Framebuffer::Unbind();

			m_gui.Render(deltaTime);

			m_window.Update();
		}

		ResourceManager::UnloadAll();
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
