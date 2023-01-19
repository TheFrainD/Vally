#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Base.h"

namespace Vally::VImGui
{

	std::string LabelPrefix(const char* label);

	void InputVec3(const std::string& label, glm::vec3& vector, F32 resetValue = 0.0f, F32 columnWidth = 100.0f);

}
