#pragma once

#include "GLCommon.hpp"
#include <Core/Graphics/Shader.hpp>
#include <Core/Utilities/File.hpp>
#include <unordered_map>

namespace Amalgamation {
	class GLShader : public Shader {

		uint32 m_ShaderID;
		std::string m_VertexShader, m_FragmentShader, m_GeometryShader;
		std::unordered_map<std::string, int32> m_UniformLocationCahce;

		void AfterLoad() override;

	public:

		GLShader();
		GLShader(const std::string& FilepathOrSource, bool IsSource = false);
		~GLShader();

		void SetUniform(const char* name, float value);
		void SetUniform(const char* name, int value);
		void SetUniform(const char* name, const glm::vec2& vector);
		void SetUniform(const char* name, float x, float y);
		void SetUniform(const char* name, const glm::vec3& vector);
		void SetUniform(const char* name, float x, float y, float z);
		void SetUniform(const char* name, const glm::vec4& vector);
		void SetUniform(const char* name, float x, float y, float z, float w);
		void SetUniform(const char* name, const glm::mat4& matrix);

		void Bind()   const;
		void Unbind() const;

		int GetUniformLocation(const char* name);

	};

}

#include "GLShader.inl"