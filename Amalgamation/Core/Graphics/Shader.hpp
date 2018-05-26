#pragma once

#include "GraphicsClass.hpp"
#include <Core/Utilities/File.hpp>
#include <string>

namespace Amalgamation {

	class Shader : public GraphicsClass {

	protected:

		std::string m_ShaderCode;

		File m_File;

		virtual void AfterLoad() {};

		bool m_SupportsLighting = true;

	public:

		Shader(API API) : GraphicsClass(API) {}
		virtual ~Shader()                    {}

		virtual void LoadFile(const std::string& Filepath) {
			m_ShaderCode = m_File.LoadAndGetContents(Filepath);
			AfterLoad();
		}

		virtual void LoadFromStr(const std::string& Str) {
			m_ShaderCode = Str;
			AfterLoad();
		}

		virtual bool SupportsLighting() const {
			return m_SupportsLighting;
		}

		virtual void SetSupportLighting(bool YoN) {
			m_SupportsLighting = YoN;
		}

	};

}