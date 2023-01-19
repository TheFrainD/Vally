#include "Scene.h"

#include <ranges>
#include <algorithm>

namespace Vally
{
	U32 Scene::s_lastId = 0;

	Scene::Scene(std::string name) noexcept 
		: m_name(std::move(name))
	{
		m_nodes.push_back(&m_rootNode);
	}

	Scene::Scene(Scene&& other) noexcept
		: m_name(std::move(other.m_name))
		, m_rootNode(other.m_rootNode)
		, m_nodes(std::move(other.m_nodes))
	{
	}

	Scene& Scene::operator=(Scene&& other) noexcept
	{
		if (this != &other)
		{
			m_name = std::move(other.m_name);
			m_rootNode = other.m_rootNode;
			m_nodes = std::move(other.m_nodes);
		}

		return *this;
	}

	void Scene::Update(const F32 deltaTime) noexcept
	{
		m_rootNode.Update(deltaTime);

		while (!m_nodesToDelete.empty())
		{
			RemoveNode(m_nodesToDelete.front());
			m_nodesToDelete.pop();
		}
	}

	void Scene::Render() noexcept
	{
		m_rootNode.Render();
	}

	Node* Scene::AddNode(const std::string& parent, const std::string& child) noexcept
	{
		if (HasNode(parent))
		{
			if (!HasNode(child))
			{
				const auto node = GetNode(parent)->AddChild(++s_lastId, child);
				m_nodes.push_back(node);
				return node;
			}

			return GetNode(child);
		}

		return nullptr;
	}

	void Scene::QueueFreeNode(Node* node) noexcept
	{
		m_nodesToDelete.push(node);
	}

	void Scene::RemoveNode(Node* node) noexcept
	{
		node->m_parent->RemoveChild(node->m_name);
		std::erase(m_nodes, node);
	}

	[[nodiscard]] bool Scene::HasNode(const std::string& name) const noexcept
	{
		return std::ranges::find_if(m_nodes, 
			[&](Node* node) { return node->m_name == name; }) != m_nodes.end();
	}

	bool Scene::HasNode(const U32 id) const noexcept
	{
		return std::ranges::find_if(m_nodes,
			[&](Node* node) { return node->GetId() == id; }) != m_nodes.end();
	}

	Node* Scene::GetNode(const std::string& name) const noexcept
	{
		auto it = std::ranges::find_if(m_nodes,
			[&](Node* node) { return node->m_name == name; });

		if (it != m_nodes.end())
		{
			return *it;
		}

		return nullptr;
	}

	Node* Scene::GetNode(const U32 id) const noexcept
	{
		auto it = std::ranges::find_if(m_nodes,
			[&](const Node* node) { return node->GetId() == id; });

		if (it != m_nodes.end())
		{
			return *it;
		}

		return nullptr;
	}
}
