#pragma once

#include "GraphicsClass.hpp"
#include <Core/Utilities/File.hpp>
#include <string>

namespace Amalgamation {

	class Shader : public GraphicsClass {

		std::string m_ShaderCode, m_Filepath;

	public:

		Shader(API API) : GraphicsClass(API) {}
		virtual ~Shader()                    {}

		virtual void LoadFile(const std::string& Filepath) {
			m_ShaderCode = File::ReadFile(Filepath);
			m_Filepath = Filepath;
		}

		virtual void LoadFileFromStr(const std::string& Str) {
			m_ShaderCode = Str;
		}

	};

}