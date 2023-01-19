#pragma once

#include <glm/glm.hpp>

namespace Vally
{

	struct Transform
	{
		glm::vec3 m_position{ 0.0f };
		glm::vec3 m_scale{ 1.0f };
		glm::vec3 m_rotation{ 0.0f };
	};

	constexpr Transform operator* (Transform lhs, const Transform& rhs)
	{
		lhs.m_position += rhs.m_position;
		lhs.m_rotation += rhs.m_rotation;
		lhs.m_scale *= rhs.m_scale;
		return lhs;
	}

}
