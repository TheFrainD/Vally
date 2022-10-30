#pragma once

#include "Base.h"

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

		void Render();
	private:
		void Begin();
		void End();

		F32 m_frameWidth{};
		F32 m_frameHeight{};
	};

}