#pragma once

#include "GLCommon.hpp"
#include <Core/Utilities/File.hpp>
#include <Core/Types/Macros.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>

namespace Amalgamation {
	class Shader {

	private:

		uint32 m_ShaderID;
		std::string m_SourcePath;
		std::unordered_map<std::string, int32> m_UniformLocationCahce;

		uint32 Load();

		int GetUniformLocation(const char* name);

		std::string m_DefaultShader = R"glsl(
@V
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normals;
layout(location = 2) in vec3 a_TextureCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
	gl_Position = vec4(a_Position, 1.f);
}
@F
#version 330 core

out vec4 FragColor;

void main() {
	FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}
)glsl";


	public:
		Shader(std::string sourcePath);
		~Shader();

		void SetUniform(const char* name, float value);
		void SetUniform(const char* name, int value);
		void SetUniform(const char* name, const glm::vec2& vector);
		void SetUniform(const char* name, float x, float y);
		void SetUniform(const char* name, const glm::vec3& vector);
		void SetUniform(const char* name, float x, float y, float z);
		void SetUniform(const char* name, const glm::vec4& vector);
		void SetUniform(const char* name, float x, float y, float z, float w);
		void SetUniform(const char* name, const glm::mat4& matrix);

		void Bind() const;
		void Unbind() const;

		void LoadShader(const std::string& ShaderLocation);

	};
}