#include "Model.h"

#include <glm/ext/matrix_transform.hpp>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Core/Log.h"
#include "Core/ResourceManager.h"

namespace Vally
{
	Model::Model(std::string path, const bool flipWindingOrder) noexcept
		: m_path(std::move(path))
	{
		LoadModel(m_path, flipWindingOrder);
	}

	Model::Model(Model&& other) noexcept
		: m_path(std::move(other.m_path))
		, m_directory(std::move(other.m_directory))
		, m_meshes(std::move(other.m_meshes))
	{
	}

	Model& Model::operator=(Model&& other) noexcept
	{
		if (this != &other)
		{
			m_path = std::move(other.m_path);
			m_directory = std::move(other.m_directory);
			m_meshes = std::move(other.m_meshes);
		}
		
		return *this;
	}

	void Model::Draw(const glm::mat4& model) const noexcept
	{
		for (auto&& mesh : m_meshes)
		{
			mesh.m_material->m_shader->SetUniformMatrix4("uModel", model);
			mesh.Draw();
		}
	}

	void Model::AttachMesh(Mesh&& mesh) noexcept
	{
		m_meshes.push_back(std::move(mesh));
	}

	void Model::LoadModel(const std::string& path, const bool flipWindingOrder)
	{
		Assimp::Importer importer;
		const aiScene* pScene = nullptr;

		U32 sceneLoadFlags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
			aiProcess_GenUVCoords | aiProcess_SortByPType | aiProcess_RemoveRedundantMaterials |
			aiProcess_FindInvalidData | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
			aiProcess_OptimizeMeshes | aiProcess_SplitLargeMeshes;

		if (flipWindingOrder)
		{
			sceneLoadFlags |= aiProcess_FlipWindingOrder;
		}
		else
		{
			sceneLoadFlags |= aiProcess_GenSmoothNormals | aiProcess_ImproveCacheLocality;
		}

		pScene = importer.ReadFile(path, sceneLoadFlags);

		if (pScene == nullptr || pScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || pScene->mRootNode == nullptr)
		{
			VALLY_ERROR("Could not load model at \"{}\". Assimp Error: {}", path, importer.GetErrorString());
			importer.FreeScene();
			return;
		}

		m_directory = path.substr(0, path.find_last_of('/')) + "/";

		ProcessNode(pScene->mRootNode, pScene);

		importer.FreeScene();
	}

	void Model::ProcessNode(aiNode* pNode, const aiScene* pScene)
	{
		for (int i = 0; i < pNode->mNumMeshes; ++i)
		{
			aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
			ProcessMesh(pMesh, pScene);
		}

		for (int i = 0; i < pNode->mNumChildren; ++i)
		{
			ProcessNode(pNode->mChildren[i], pScene);
		}
	}

	void Model::ProcessMesh(aiMesh* pMesh, const aiScene* pScene)
	{
		std::vector<Vertex> vertices;

		for (U32 i = 0; i < pMesh->mNumVertices; ++i)
		{
			Vertex vertex;

			if (pMesh->HasPositions())
			{
				vertex.m_position = {
					pMesh->mVertices[i].x,
					pMesh->mVertices[i].y,
					pMesh->mVertices[i].z
				};
			}

			if (pMesh->HasNormals())
			{
				vertex.m_normal = {
					pMesh->mNormals[i].x,
					pMesh->mNormals[i].y,
					pMesh->mNormals[i].z
				};
			}

			if (pMesh->HasTangentsAndBitangents())
			{
				vertex.m_tangent = {
					pMesh->mTangents[i].x,
					pMesh->mTangents[i].y,
					pMesh->mTangents[i].z
				};
			}

			if (pMesh->HasTextureCoords(0))
			{
				vertex.m_uv = {
					pMesh->mTextureCoords[0][i].x,
					pMesh->mTextureCoords[0][i].y
				};
			}

			vertices.push_back(vertex);
		}

		std::vector<U32> indices;

		for (U32 i = 0; i < pMesh->mNumFaces; ++i)
		{
			const aiFace face = pMesh->mFaces[i];
			for (U32 j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		Mesh mesh;
		mesh.m_vertices = vertices;
		mesh.m_indices = indices;

		const aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];

		aiString materialName;
		pMaterial->Get(AI_MATKEY_NAME, materialName);

		if (ResourceManager::Exists(materialName.C_Str()))
		{
			mesh.m_material = ResourceManager::Get<Material>(materialName.C_Str());
		}
		else
		{
			auto material = std::make_shared<Material>();

			aiString albedoPath;
			pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &albedoPath);

			ResourceManager::Load<Shader>("Standard shader", "assets/shaders/standard.glsl");
			material->m_shader = ResourceManager::Get<Shader>("Standard shader");

			ResourceManager::Load<Texture>(albedoPath.C_Str(), albedoPath.C_Str());
			material->m_textures.m_albedo = ResourceManager::Get<Texture>(albedoPath.C_Str());

			mesh.m_material = material;
			ResourceManager::Load<Material>(materialName.C_Str(), material);
		}

		mesh.UpdateMesh();

		m_meshes.push_back(std::move(mesh));
	}
}
