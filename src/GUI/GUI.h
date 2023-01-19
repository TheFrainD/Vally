#pragma once

#include <glm/glm.hpp>

#include "Base.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/Camera.h"
#include "Scene/Node.h"

struct GLFWwindow;

namespace Vally
{

	class GUI
	{
	public:
		GUI(GLFWwindow* pWindow, F32 frameWidth, F32 frameHeight);
		~GUI();

		GUI(const GUI&) = delete;
		GUI& operator=(const GUI&) = delete;
		GUI(GUI&&) = delete;
		GUI& operator=(GUI&&) = delete;

		void Render(F32 deltaTime) noexcept;

		void ShowSceneNode(Node* node) noexcept;

		void ShowNodeProperties() noexcept;

		[[nodiscard]] const Framebuffer& GetFramebuffer() const noexcept;

		[[nodiscard]] const Camera& GetCamera() const noexcept
		{
			return m_camera;
		}
	private:
		void Begin() noexcept;
		void End() noexcept;

		F32 m_frameWidth{};
		F32 m_frameHeight{};

		Framebuffer m_framebuffer;
		glm::vec2 m_viewportSize{ 0.0f, 0.0f };

		bool m_viewportActive = false;
		Camera m_camera;

		Node* m_selectedNode = nullptr;
		std::string m_modelPath;
	};

}