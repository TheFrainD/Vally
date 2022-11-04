#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <utility>
#include <span>

#include <glm/glm.hpp>

#include "Base.h"

namespace Vally
{

	class Shader;
	using ShaderContainer = std::optional<Shader>;

	class Shader
	{
	public:
		[[nodiscard]] static ShaderContainer Create(
			const std::string& name,
			const std::string& filePath) noexcept;

		~Shader();

		Shader(Shader&& other) noexcept;
		Shader& operator=(Shader&& other) noexcept;

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void Use() const noexcept;

		void SetUniformFloat(const std::string& name, F32 value) noexcept;

		void SetUniformFloatArray(const std::string& name, const std::span<F32>& pArray) noexcept;

		void SetUniformVector2(const std::string& name, const glm::vec2& vector) noexcept;

		void SetUniformVector3(const std::string& name, const glm::vec3& vector) noexcept;

		void SetUniformVector4(const std::string& name, const glm::vec4& vector) noexcept;

		void SetUniformMatrix4(const std::string& name, const glm::mat4& matrix) noexcept;

		void SetUniformInteger(const std::string& name, I32 value) noexcept;

		void SetUniformIntegerArray(const std::string& name, const std::span<I32>& pArray);
	private:
		explicit Shader(std::string name, U32 id) noexcept;

		[[nodiscard]] static U32 CreateProgram(const std::string& vertexSource, const std::string& fragmentSource) noexcept;
		[[nodiscard]] static U32 CompileShader(U32 type, const std::string& source) noexcept;
		[[nodiscard]] static std::pair<std::string, std::string> Parse(const std::string& filePath) noexcept;

		[[nodiscard]] I32 GetUniformLocation(const std::string& name) noexcept;

		U32 m_id = 0;
		std::string m_name;
		std::unordered_map<std::string, I32> m_uniformLocations;
	};

}
