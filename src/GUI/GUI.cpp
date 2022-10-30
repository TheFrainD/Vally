#include "GUI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include <backends/imgui_impl_glfw.cpp>
#include <backends/imgui_impl_opengl3.cpp>

#include "Base.h"
#include "Core/Log.h"
#include "Core/Window.h"
#include "Event/EventManager.h"
#include "Event/WindowEvent.h"

namespace Vally
{
	GUI::GUI(GLFWwindow* pWindow, F32 frameWidth, F32 frameHeight) :
		m_frameWidth(frameWidth), m_frameHeight(frameHeight)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
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

		ImGui_ImplGlfw_InitForOpenGL(pWindow, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		EventManager::Subscribe<WindowResizeEvent>([this](Event& event)
		{
			const auto& windowResizeEvent = dynamic_cast<WindowResizeEvent&>(event);
			this->m_frameWidth = static_cast<F32>(windowResizeEvent.GetWidth());
			this->m_frameHeight = static_cast<F32>(windowResizeEvent.GetHeight());
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

	void GUI::Render()
	{
		
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
		ImGui::End();

		ImGui::Begin("Viewport");
		ImGui::End();

		ImGui::Begin("Scene");
		ImGui::PushID(0);
		bool opened = ImGui::TreeNodeEx("Node 1", ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth);
		ImGui::PopID();
		if (opened)
		{
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::Begin("Parameters");
		ImGui::End();

		ImGui::End();

		End();
	}

	void GUI::Begin()
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::End()
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
