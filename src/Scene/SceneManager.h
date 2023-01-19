#pragma once

#include <unordered_map>
#include <string>

#include "Base.h"
#include "Scene/Scene.h"

namespace Vally
{

	class SceneManager
	{
	public:
		SceneManager() = delete;

		static Scene* CreateScene(const std::string& name) noexcept;

		[[nodiscard]] static bool HasScene(const std::string& name) noexcept;

		[[nodiscard]] static Scene* GetScene(const std::string& name) noexcept;

		[[nodiscard]] static Scene* GetCurrentScene() noexcept
		{
			return s_currentScene;
		}

		static void SetCurrentScene(const std::string& name) noexcept;

		static void Update(F32 deltaTime) noexcept;
		
		static void Render() noexcept;
	private:
		static std::unordered_map<std::string, Scene> s_scenes;
		static Scene* s_currentScene;
	};

}
