#pragma once

#include "GraphicsClass.hpp"
#include <Core/Utilities/File.hpp>
#include <string>

namespace Amalgamation {

	class Shader : public GraphicsClass {

	protected:

		std::string m_ShaderCode;
		File m_File;

		virtual void AfterLoad();

	public:

		bool SupportsLighting = true;

		Shader(API API);
		virtual ~Shader();

		virtual void LoadFile(const std::string& Filepath);
		virtual void LoadFromStr(const std::string& Str);

	};

}
#ifndef AE_NO_IMPL
	#include "Shader.inl"
#endif