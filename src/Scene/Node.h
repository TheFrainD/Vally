#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>

#include "Base.h"
#include "Core/Log.h"
#include "Scene/Transform.h"
#include "Graphics/Model.h"

namespace Vally
{

	class Node
	{
	public:
		explicit Node(const U32 id, std::string name) noexcept;

		virtual ~Node();

		void Create() noexcept;

		void Update(const F32 deltaTime) noexcept;

		void Render() noexcept;

		virtual void OnCreate() noexcept
		{
		}

		virtual void OnUpdate(const F32 deltaTime) noexcept
		{
		}

		virtual void OnRender()
		{
		}

		[[nodiscard]] U32 GetId() const noexcept
		{
			return m_id;
		}

		[[nodiscard]] std::string GetFullName() const noexcept;

		Node* AddChild(const U32 id, const std::string& name) noexcept;

		void RemoveChild(const std::string& name) noexcept;

		void RemoveChild(const U32 id) noexcept;

		Transform GetGlobalTransform() const noexcept;

		std::string m_name;
		
		Transform m_transform;
		std::shared_ptr<Model> m_model;

		std::vector<Node> m_children;
		Node* m_parent = nullptr;
	private:
		U32 m_id = 0;

		[[nodiscard]] glm::mat4 GetModelMatrix() const noexcept;
	};

}
