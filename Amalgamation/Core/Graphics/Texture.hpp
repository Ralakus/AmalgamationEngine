#pragma once

#include <Core/Platform/Platform.hpp>
#include <functional>
#include <string>

namespace Amalgamation {

	class Texture : public GraphicsClass {
	protected:

		std::string m_FilePath;

		int m_Width, m_Height, m_Channels, m_LODLevel;

	public:

		Texture(API API) : GraphicsClass(API) {}
		virtual ~Texture()                    {} 

		int GetWidth()    const { return m_Width;    }
		int GetHeight()   const { return m_Height;   }
		int GetChannels() const { return m_Channels; }
		int GetLODLevel() const { return m_LODLevel;    }

		const std::string& GetFilePath() const { return m_FilePath; }


		virtual bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, std::function<void()> LoadFunction) = 0;
		virtual bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel) = 0;

		virtual void Bind()   const = 0;
		virtual void Unbind() const = 0;
	};

}