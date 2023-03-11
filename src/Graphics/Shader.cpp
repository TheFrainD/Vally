#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Log.h"
#include "Core/Assert.h"
#include "Graphics/Renderer.h"

namespace Vally
{

	static U32 HashValue(const std::string_view& str)
	{
		const char* c = str.data();
		U32 value = 0x00000000;

		while (*c)
		{
			value = (value << 5) - value + (*c == '/' ? '\\' : *c);
			c++;
		}

		return value ? value : 0xffffffff;
	}

	Shader::~Shader()
	{
		Release();
	}

	Shader::Shader(Shader&& other) noexcept
		: m_id(other.m_id)
		, m_path(std::move(other.m_path))
		, m_uniformLocations(std::move(other.m_uniformLocations))
		, m_uniformBlockLocations(std::move(other.m_uniformBlockLocations))
	{
		other.m_id = 0;
	}

	Shader& Shader::operator=(Shader&& other) noexcept
	{
		if (this != &other)
		{
			Release();

			m_id = other.m_id;
			m_path = std::move(other.m_path);
			m_uniformLocations = std::move(other.m_uniformLocations);
			m_uniformBlockLocations = std::move(other.m_uniformBlockLocations);

			other.m_id = 0;
		}

		return *this;
	}

	void Shader::Use() const  noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not use uninitialized shader!");
		glUseProgram(m_id);
	}

	void Shader::SetUniformFloat(const std::string& name, F32 value) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniformFloatArray(const std::string& name, const std::span<F32>& pArray) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform1fv(GetUniformLocation(name), static_cast<GLsizei>(pArray.size()), pArray.data());
	}

	void Shader::SetUniformVector2(const std::string& name, const glm::vec2& vector) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniformVector3(const std::string& name, const glm::vec3& vector) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniformVector4(const std::string& name, const glm::vec4& vector) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMatrix4(const std::string& name, const glm::mat4& matrix) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(matrix));
	}

	void Shader::SetUniformInteger(const std::string& name, I32 value) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniformIntegerArray(const std::string& name, const std::span<I32>& pArray)
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform to uninitialized shader!");
		Use();
		glUniform1iv(GetUniformLocation(name), static_cast<GLsizei>(pArray.size()), pArray.data());
	}

	void Shader::SetUniformBlock(U32 uniformBinding, const std::string& uniformBlockName) noexcept
	{
		VALLY_ASSERT(m_id != 0, "Can not set uniform block to uninitialized shader!");
		const U32 uniformBlockID = GetUniformBlockLocation(uniformBlockName);
		glUniformBlockBinding(m_id, uniformBlockID, uniformBinding);
	}

	void Shader::Release() noexcept
	{
		glDeleteProgram(m_id);
		m_id = 0;
	}

	Shader::Shader(const std::string& filePath)
		: m_path(filePath)
	{
		const auto [vertexSource, fragmentSource] = Parse(filePath);

		m_id = CreateProgram(vertexSource, fragmentSource);
		if (m_id == 0)
		{
			throw std::runtime_error{ "Could not create shader program (" + m_path + ")" };
		}

		Renderer::s_data.m_cameraBuffer->Bind(0, "CameraMatrices", this);
	}

	U32 Shader::CreateProgram(const std::string& vertexSource, const std::string& fragmentSource) noexcept
	{
		const U32 programID = glCreateProgram();
		const U32 vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexSource);
		const U32 fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

		if (vertexShaderID == 0 || fragmentShaderID == 0)
		{
			return 0;
		}

		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);

		GLint linkStatus;
		glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

		if (linkStatus == GL_FALSE)
		{
			GLint infoLogLength;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, ' ');
			glGetProgramInfoLog(programID, infoLogLength, &infoLogLength, infoLog.data());

			VALLY_ERROR("Shader progarm link error:\n{}", infoLog);

			return 0;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		return programID;
	}

	U32 Shader::CompileShader(U32 type, const std::string& source) noexcept
	{
		const U32 id = glCreateShader(type);

		const char* c_source = source.c_str();
		glShaderSource(id, 1, &c_source, nullptr);

		glCompileShader(id);

		GLint compileStatus;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

			std::string infoLog(infoLogLength, ' ');
			glGetShaderInfoLog(id, infoLogLength, &infoLogLength, infoLog.data());

			VALLY_ERROR("{} shader error:\n{}", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	std::pair<std::string, std::string> Shader::Parse(const std::string& filePath) noexcept
	{
		std::ifstream stream(filePath);
		if (!stream.is_open())
		{
			VALLY_ERROR("Could not load shader source at \"{}\"!", filePath);
			return {};
		}

		enum ShaderType : I16
		{
			None = -1,
			Vertex = 0,
			Fragment = 1
		};

		std::stringstream sourceStream[2];
		std::string currentLine;
		ShaderType type = ShaderType::None;

		while (std::getline(stream, currentLine))
		{
			if (currentLine.find("#shader") != std::string::npos)
			{
				if (currentLine.find("vertex") != std::string::npos)
				{
					type = ShaderType::Vertex;
				}
				else if (currentLine.find("fragment") != std::string::npos)
				{
					type = ShaderType::Fragment;
				}
			}
			else if (type != ShaderType::None)
			{
				sourceStream[type] << currentLine << '\n';
			}
		}

		stream.close();

		return { sourceStream[ShaderType::Vertex].str(), sourceStream[ShaderType::Fragment].str() };
	}

	I32 Shader::GetUniformLocation(const std::string& name) noexcept
	{
		const U32 hashedName = HashValue(name);

		if (!m_uniformLocations.contains(hashedName))
		{
			m_uniformLocations[hashedName] = glGetUniformLocation(m_id, name.c_str());
		}

		return m_uniformLocations.at(hashedName);
	}

	I32 Shader::GetUniformBlockLocation(const std::string& name) noexcept
	{
		const U32 hashedName = HashValue(name);

		if (!m_uniformBlockLocations.contains(hashedName))
		{
			m_uniformBlockLocations[hashedName] = glGetUniformBlockIndex(m_id, name.c_str());
		}

		return m_uniformBlockLocations.at(hashedName);
	}
}
