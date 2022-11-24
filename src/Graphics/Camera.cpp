#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics/Renderer.h"

namespace Vally
{
	Camera::Camera(F32 fov, F32 sensitivity, F32 near, F32 far) noexcept
		: m_fov(glm::radians(fov)), m_sensitivity(sensitivity)
		, m_near(near), m_far(far)
	{
		UpdateView();
	}

	void Camera::UpdateProjection(const glm::vec2& viewportSize) noexcept
	{
		const F32 aspectRatio = viewportSize.x / viewportSize.y;
		m_projection = glm::perspective(m_fov, aspectRatio, m_near, m_far);
		if (Renderer::s_data.m_cameraBuffer)
		{
			Renderer::s_data.m_cameraBuffer->SetData(glm::value_ptr(m_projection), sizeof(glm::mat4));
		}
	}

	void Camera::UpdateView() noexcept
	{
		m_pitch = glm::clamp(m_pitch, -glm::half_pi<F32>() + 0.01f, glm::half_pi<F32>() - 0.01f);
		m_yaw = (m_yaw < 0 ? glm::two_pi<F32>() : 0.0f) + glm::mod(m_yaw, glm::two_pi<F32>());

		m_front = {
			glm::cos(m_yaw) * glm::cos(m_pitch),
			glm::sin(m_pitch),
			glm::sin(m_yaw) * glm::cos(m_pitch)
		};

		m_front = glm::normalize(m_front);
		m_right = glm::normalize(glm::cross(m_front, { 0.0f, 1.0f, 0.0f }));
		m_up = glm::normalize(glm::cross(m_right, m_front));

		m_view = glm::lookAt(m_position, m_position + m_front, m_up);
		if (Renderer::s_data.m_cameraBuffer)
		{
			Renderer::s_data.m_cameraBuffer->SetData(glm::value_ptr(m_view), sizeof(glm::mat4), sizeof(glm::mat4));
		}
	}

	void Camera::Rotate(glm::vec2 mouseDeltaPosition)
	{
		mouseDeltaPosition = glm::clamp(mouseDeltaPosition, -100.0f, 100.0f);
		m_yaw += mouseDeltaPosition.x * m_sensitivity;
		m_pitch -= mouseDeltaPosition.y * m_sensitivity;

		UpdateView();
	}
}
