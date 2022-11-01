#include "Input.h"

namespace Vally
{
	Keyboard Input::s_keyboard;
	Mouse Input::s_mouse;

	bool Input::IsKeyPressed(Key key) noexcept
	{
		return s_keyboard.m_keys[static_cast<U16>(key)];
	}

	bool Input::IsMouseButtonPressed(MouseButton mouseButton) noexcept
	{
		return s_mouse.m_buttons[static_cast<U16>(mouseButton)];
	}

	glm::vec2 Input::GetMousePosition() noexcept
	{
		return s_mouse.m_position;
	}

	glm::vec2 Input::GetMousePreviousPosition() noexcept
	{
		return s_mouse.m_previousPosition;
	}

}
