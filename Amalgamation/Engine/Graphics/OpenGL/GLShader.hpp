#pragma once

#include "GLCommon.hpp"
#include <Core/Graphics/Shader.hpp>
#include <Core/Utilities/File.hpp>
#include <Core/Math/Vector/Vector2.hpp>
#include <Core/Math/Vector/Vector3.hpp>
#include <Core/Math/Vector/Vector4.hpp>
#include <Core/Math/Matrix/Matrix4x4.hpp>
#include <unordered_map>

namespace Amalgamation {
	class GLShader : public Shader {

		uint32 m_ShaderID;
		std::string m_VertexShader, m_FragmentShader, m_GeometryShader;
		std::unordered_map<std::string, int32> m_UniformLocationCahce;

		int GetUniformLocation(const char* name);
		void AfterLoad() override;

	public:

		GLShader();
		GLShader(const std::string& FilepathOrSource, bool IsSource = false);
		~GLShader();

		void SetUniform(const char* name, float value);
		void SetUniform(const char* name, int value);
		void SetUniform(const char* name, const Math::Vec2& vector);
		void SetUniform(const char* name, float x, float y);
		void SetUniform(const char* name, const Math::Vec3& vector);
		void SetUniform(const char* name, float x, float y, float z);
		void SetUniform(const char* name, const Math::Vec4& vector);
		void SetUniform(const char* name, float x, float y, float z, float w);
		void SetUniform(const char* name, const Math::Mat4& matrix);

		void Bind()   const;
		void Unbind() const;

	};

}

#include "GLShader.inl"