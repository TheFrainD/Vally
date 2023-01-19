#include "Node.h"

#include <sstream>

#include <glm/ext/matrix_transform.hpp>

namespace Vally
{
	Node::Node(const U32 id, std::string name) noexcept
		: m_name(std::move(name))
		, m_id(id)
	{
		VALLY_INFO("Node {} created", m_name);
	}

	Node::~Node()
	{
		VALLY_INFO("Node {} deleted", m_name);
	}

	void Node::Create() noexcept
	{
		OnCreate();
	}

	void Node::Update(const F32 deltaTime) noexcept
	{
		OnUpdate(deltaTime);

		for (auto& child : m_children)
		{
			child.OnUpdate(deltaTime);
		}
	}

	void Node::Render() noexcept
	{
		OnRender();

		if (m_model)
		{
			m_model->Draw(GetModelMatrix());
		}

		for (auto& child : m_children)
		{
			child.Render();
		}
	}

	std::string Node::GetFullName() const noexcept
	{
		if (!m_parent)
		{
			return m_name;
		}

		std::stringstream stream;
		stream << m_parent->m_name << "::" << m_name;
		return stream.str();
	}


	Node* Node::AddChild(const U32 id, const std::string& name) noexcept
	{
		m_children.emplace_back(id, name);
		m_children.back().m_parent = this;
		return &m_children.back();
	}

	void Node::RemoveChild(const std::string& name) noexcept
	{
		std::erase_if(m_children, [&](const Node& node) { return node.m_name == name; });
	}

	void Node::RemoveChild(const U32 id) noexcept
	{
		std::erase_if(m_children, [&](const Node& node) { return node.GetId() == id; });
	}

	Transform Node::GetGlobalTransform() const noexcept
	{
		if (!m_parent)
		{
			return m_transform;
		}

		return m_transform * m_parent->GetGlobalTransform();
	}

	glm::mat4 Node::GetModelMatrix() const noexcept
	{
		const Transform transform = GetGlobalTransform();

		glm::mat4 model{ 1.0f };
		model = glm::translate(model, transform.m_position);
		model = glm::rotate(model, glm::radians(transform.m_rotation.x), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(transform.m_rotation.y), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(transform.m_rotation.z), { 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, transform.m_scale);

		return model;
	}
}
