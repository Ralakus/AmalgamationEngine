#pragma once

#include <Core/Platform/Platform.hpp>
#include "GraphicsClass.hpp"
#include <functional>
#include <string>

namespace Amalgamation {

	class Texture : public GraphicsClass {
	protected:

		std::string m_FilePath;

		int m_Width, m_Height, m_Channels, m_LODLevel, m_Layer;

	public:

		Texture(API API) : GraphicsClass(API) {}
		virtual ~Texture()                    {} 

		int GetWidth()    const { return m_Width;    }
		int GetHeight()   const { return m_Height;   }
		int GetChannels() const { return m_Channels; }
		int GetLODLevel() const { return m_LODLevel; }
		int GetLayer()    const { return m_Layer;    }

		const std::string& GetFilePath() const { return m_FilePath; }


		virtual bool LoadTexture(const std::string& FilePath, bool Flip, uint32_t LODLevel, int Layer, const std::function<void()>& LoadFunction) = 0;
		virtual bool LoadTexture(const std::string& FilePath, bool Flip, uint32_t LODLevel, int Layer) = 0;
		virtual bool LoadTextureData(const unsigned char* Data, int Width, int Height, int Channels, uint32_t LODLevel, int Layer) = 0;
		virtual bool LoadTextureData(const unsigned char* Data, int Width, int Height, int Channels, uint32_t LODLevel, int Layer, const std::function<void()>& LoadFunction) = 0;

		virtual void Bind()   const = 0;
		virtual void Unbind() const = 0;
	};

}