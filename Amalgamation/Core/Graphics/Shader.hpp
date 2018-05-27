#pragma once

#include "GraphicsClass.hpp"
#include <Core/Utilities/File.hpp>
#include <string>

namespace Amalgamation {

	class Shader : public GraphicsClass {

	protected:

		std::string m_ShaderCode;
		File m_File;
		bool m_SupportsLighting = true;

		virtual void AfterLoad();

	public:

		Shader(API API);
		virtual ~Shader();

		virtual void LoadFile(const std::string& Filepath);
		virtual void LoadFromStr(const std::string& Str);

		virtual bool SupportsLighting() const;
		virtual void SetSupportLighting(bool YoN);

	};

}

#include "Shader.inl"