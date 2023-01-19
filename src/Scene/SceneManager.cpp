#include "SceneManager.h"

namespace Vally
{

	std::unordered_map<std::string, Scene> SceneManager::s_scenes;
	Scene* SceneManager::s_currentScene = nullptr;

	Scene* SceneManager::CreateScene(const std::string& name) noexcept
	{
		if (!HasScene(name))
		{
			s_scenes.emplace(name, name);
			if (!s_currentScene)
			{
				s_currentScene = &s_scenes[name];
				 
			}
			return &s_scenes[name];
		}

		return nullptr;
	}

	bool SceneManager::HasScene(const std::string& name) noexcept
	{
		return s_scenes.contains(name);
	}

	Scene* SceneManager::GetScene(const std::string& name) noexcept
	{
		if (HasScene(name))
		{
			return &s_scenes.at(name);
		}

		return nullptr;
	}

	void SceneManager::SetCurrentScene(const std::string& name) noexcept
	{
		Scene* scene = GetScene(name);
		if (scene)
		{
			s_currentScene = scene;
		}
	}

	void SceneManager::Update(F32 deltaTime) noexcept
	{
		if (s_currentScene)
		{
			s_currentScene->Update(deltaTime);
		}
	}

	void SceneManager::Render() noexcept
	{
		if (s_currentScene)
		{
			s_currentScene->Render();
		}
	}
}
