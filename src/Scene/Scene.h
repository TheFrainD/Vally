#pragma once

#include <vector>
#include <queue>
#include <string>

#include "Base.h"
#include "Scene/Node.h"

namespace Vally
{

	class Scene
	{
	public:
		explicit Scene(std::string name = "") noexcept;
		~Scene() = default;

		Scene(Scene&& other) noexcept;
		Scene& operator=(Scene&& other) noexcept;

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		void Update(const F32 deltaTime) noexcept;

		void Render() noexcept;

		Node* AddNode(const std::string& parent, const std::string& child) noexcept;

		void QueueFreeNode(Node* node) noexcept;

		[[nodiscard]] bool HasNode(const std::string& name) const noexcept;

		[[nodiscard]] bool HasNode(const U32 id) const noexcept;

		[[nodiscard]] Node* GetNode(const std::string& name) const noexcept;

		[[nodiscard]] Node* GetNode(const U32 id) const noexcept;

		[[nodiscard]] Node* GetRoot() noexcept
		{
			return &m_rootNode;
		}

		[[nodiscard]] std::string GetName() const noexcept
		{
			return m_name;
		}
	private:
		void RemoveNode(Node* node) noexcept;

		std::string m_name;
		Node m_rootNode{ 0, "root" };
		std::vector<Node*> m_nodes;
		std::queue<Node*> m_nodesToDelete;
		static U32 s_lastId;
	};
}
