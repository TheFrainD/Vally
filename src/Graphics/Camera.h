#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Base.h"

namespace Vally
{
	class Camera
	{
	public:
		Camera(F32 fov, F32 sensitivity, F32 near = 0.1f, F32 far = 1000.0f) noexcept;

		void UpdateProjection(const glm::vec2& viewportSize) noexcept;
		void UpdateView() noexcept;

		void Rotate(glm::vec2 mouseDeltaPosition);

		[[nodiscard]] glm::mat4 GetView() const noexcept
		{
			return m_view;
		}

		[[nodiscard]] glm::mat4 GetProjection() const noexcept
		{
			return m_projection;
		}

		[[nodiscard]] glm::vec3 GetFront() const noexcept
		{
			return m_front;
		}

		[[nodiscard]] glm::vec3 GetUp() const noexcept
		{
			return m_up;
		}

		[[nodiscard]] glm::vec3 GetRight() const noexcept
		{
			return m_right;
		}

		[[nodiscard]] glm::vec3 GetPosition() const noexcept
		{
			return m_position;
		}

		void SetPosition(const glm::vec3& position) noexcept
		{
			m_position = position;
			UpdateView();
		}

		void Translate(const glm::vec3& translation) noexcept
		{
			SetPosition(m_position + translation);
		}
		
	private:
		glm::vec3 m_position{0.0f};

		glm::mat4 m_projection{1.0f };
		glm::mat4 m_view{ 1.0f };

		glm::vec3 m_front{ 0.0f, 0.0f, -1.0f };
		glm::vec3 m_right{ 1.0f, 0.0f, 0.0f };
		glm::vec3 m_up{ 0.0f, 1.0f, 0.0f };

		F32 m_fov;
		F32 m_sensitivity;
		F32 m_near;
		F32 m_far;

		F32 m_yaw = glm::half_pi<F32>();
		F32 m_pitch = 0.0f;
	};
}
