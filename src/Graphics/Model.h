#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Base.h"
#include "Core/Resource.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"

struct aiScene;
struct aiNode;
struct aiMesh;

namespace Vally
{
	class Model final : public Resource
	{
	public:
		VALLY_RESOURCE(Model)

		~Model() override = default;

		explicit Model(std::string path, const bool flipWindingOrder = false) noexcept;

		Model(Model&& other) noexcept;
		Model& operator=(Model&& other) noexcept;

		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		void Draw(const glm::mat4& model) const noexcept;

		void AttachMesh(Mesh&& mesh) noexcept;

		[[nodiscard]] std::string GetPath() const noexcept
		{
			return m_path;
		}
	private:
		void LoadModel(const std::string& path, const bool flipWindingOrder = false);
		void ProcessNode(aiNode* pNode, const aiScene* pScene);
		void ProcessMesh(aiMesh* pMesh, const aiScene* pScene);

		std::string m_path;
		std::vector<Mesh> m_meshes;
	};
}
