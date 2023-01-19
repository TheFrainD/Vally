#include "GUI.h"

#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <backends/imgui_impl_glfw.cpp>
#include <backends/imgui_impl_opengl3.cpp>

#include "Base.h"
#include "Core/Log.h"
#include "Core/Window.h"
#include "Core/Input.h"
#include "Event/EventManager.h"
#include "Event/WindowEvent.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexArray.h"
#include "Event/InputEvent.h"
#include "Scene/SceneManager.h"
#include "GUI/VImGui.h"
#include "Core/ResourceManager.h"

namespace Vally
{
	GUI::GUI(GLFWwindow* pWindow, F32 frameWidth, F32 frameHeight)
		: m_frameWidth(frameWidth)
		, m_frameHeight(frameHeight)
		, m_framebuffer(frameWidth, frameHeight)
		, m_camera(60.0f, 0.015f)
	{
		IMGUI_CHECKVERSION();

		if (ImGui::CreateContext() == nullptr)
		{
			throw std::runtime_error{ "Could not create ImGui Context!" };
		}

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		if (!ImGui_ImplGlfw_InitForOpenGL(pWindow, true))
		{
			ImGui::DestroyContext();
			throw std::runtime_error{ "Could not initialize GLFW implementation for ImGui!" };
		}

		if (!ImGui_ImplOpenGL3_Init("#version 410"))
		{
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			throw std::runtime_error{ "Could not initialize OpenGL implementation for ImGui!" };
		}

		EventManager::Subscribe<WindowResizeEvent>([this](Event& event)
		{
			const auto& windowResizeEvent = dynamic_cast<WindowResizeEvent&>(event);
			this->m_frameWidth = static_cast<F32>(windowResizeEvent.GetWidth());
			this->m_frameHeight = static_cast<F32>(windowResizeEvent.GetHeight());
		});

		m_camera.SetPosition({ 0.0f, 0.0f, -3.0f });

		EventManager::Subscribe<MouseMovedEvent>([this](Event& event)
		{
			if (Input::IsMouseButtonPressed(MouseButton::ButtonRight) && m_viewportActive)
			{
				MouseMovedEvent& mouseEvent = dynamic_cast<MouseMovedEvent&>(event);
				m_camera.Rotate(mouseEvent.GetPosition() - mouseEvent.GetPreviousPosition());
			}
		});

		VALLY_INFO("GUI initialized!");
	}

	GUI::~GUI()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		VALLY_INFO("GUI destroyed!");
	}

	void GUI::Render(F32 deltaTime) noexcept
	{
		if (m_viewportSize.x > 0.0f && m_viewportSize.y > 0.0f)
		{
			m_framebuffer.Resize(m_viewportSize.x, m_viewportSize.y);
			m_camera.UpdateProjection(m_viewportSize);
		}

		Begin();

		static bool open = true;
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &open, windowFlags);
		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);

		ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					
				}

				if (ImGui::MenuItem("Open", "Ctrl+O"))
				{

				}

				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{

				}

				if (ImGui::MenuItem("Save As", "Ctrl+Shift+S"))
				{

				}

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "Alt+F4"))
				{

				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Scene"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Stats");
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("Frametime: %.2f ms", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Begin("Settings");

		static bool vsync = true;
		static bool vsyncPrev = true;
		ImGui::Checkbox("Vertical sync", &vsync);
		if (vsync != vsyncPrev)
		{
			Window::SetSwapInterval(vsync);
			vsyncPrev = vsync;
		}

		ImGui::Checkbox("Face culling", &Renderer::s_settings.m_faceCulling);
		ImGui::End();

		ImGui::Begin("Viewport");

		m_viewportActive = ImGui::IsWindowFocused();
		if (m_viewportActive)
		{
			if (Input::IsMouseButtonPressed(MouseButton::ButtonRight))
			{
				glm::vec3 direction{ 0.0f };
				constexpr F32 SPEED = 10.0f;

				if (Input::IsKeyPressed(Key::W))
				{
					m_camera.Translate(m_camera.GetFront() * SPEED * deltaTime);
				}
				else if (Input::IsKeyPressed(Key::S))
				{
					m_camera.Translate(-m_camera.GetFront() * SPEED * deltaTime);
				}

				if (Input::IsKeyPressed(Key::D))
				{
					m_camera.Translate(m_camera.GetRight() * SPEED * deltaTime);
				}
				else if (Input::IsKeyPressed(Key::A))
				{
					m_camera.Translate(-m_camera.GetRight() * SPEED * deltaTime);
				}
			}
			/*m_camera.Translate(glm::normalize(direction) * SPEED * deltaTime);*/
		}

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		ImGui::Image(reinterpret_cast<void*>(m_framebuffer.GetTextureID()), ImVec2{ m_viewportSize.x, m_viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		ImGui::End();

		ImGui::Begin("Scene");
		if (SceneManager::GetCurrentScene())
		{
			auto& nodes = SceneManager::GetCurrentScene()->GetRoot()->m_children;
			for (auto& node : nodes)
			{
				ShowSceneNode(&node);
			}
		}
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_selectedNode = nullptr;
		ImGui::End();

		ImGui::Begin("Properties");
		ShowNodeProperties();
		ImGui::End();

		ImGui::End();

		End();
	}

	void GUI::ShowSceneNode(Node* node) noexcept
	{
		bool opened = ImGui::TreeNodeEx(node->m_name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth);

		if (ImGui::IsItemClicked())
		{
			m_selectedNode = node;

			if (m_selectedNode->m_model)
			{
				m_modelPath = m_selectedNode->m_model->GetPath();
			}
			else
			{
				m_modelPath = "";
			}
		}

		bool nodeDeleted = false;
		bool nodeCreated = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Add child"))
			{
				nodeCreated = true;
			}
			
			if (ImGui::MenuItem("Delete"))
			{
				nodeDeleted = true;
			}

			ImGui::EndPopup();
		}

		if (opened)
		{	
			auto& children = node->m_children;
			for (auto& child : children)
			{
				ShowSceneNode(&child);
			}
			ImGui::TreePop();
		}

		if (nodeDeleted)
		{
			if (m_selectedNode == node)
			{
				m_selectedNode = nullptr;
			}
			SceneManager::GetCurrentScene()->QueueFreeNode(node);
		}

		if (nodeCreated)
		{
			SceneManager::GetCurrentScene()->AddNode(node->m_name, "New node");
		}
	}

	void GUI::ShowNodeProperties() noexcept
	{
		if (m_selectedNode)
		{
			ImGui::InputText(VImGui::LabelPrefix("Name").c_str(), &m_selectedNode->m_name);

			if (ImGui::CollapsingHeader("Transform"))
			{
				VImGui::InputVec3("Position", m_selectedNode->m_transform.m_position);
				VImGui::InputVec3("Scale", m_selectedNode->m_transform.m_scale);
				VImGui::InputVec3("Rotation", m_selectedNode->m_transform.m_rotation);
			}

			if (ImGui::CollapsingHeader("Model"))
			{
				ImGui::InputText(VImGui::LabelPrefix("Path").c_str(), &m_modelPath);
				if (ImGui::Button("Reset"))
				{
					if (m_selectedNode->m_model)
					{
						m_modelPath = m_selectedNode->m_model->GetPath();
					}
					else
					{
						m_modelPath = "";
					}
				}
				ImGui::SameLine();

				if (ImGui::Button("Load"))
				{
					if (ResourceManager::Load<Model>(m_modelPath, m_modelPath))
					{
						m_selectedNode->m_model = ResourceManager::Get<Model>(m_modelPath);
					}
				}
			}
		}
	}

	const Framebuffer& GUI::GetFramebuffer() const noexcept
	{
		return m_framebuffer;
	}

	void GUI::Begin() noexcept
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::End() noexcept
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(m_frameWidth, m_frameHeight);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}
}
