#pragma once

#include <Core/Graphics/Texture.hpp>
#include "GLCommon.hpp"

#include <stb_image.h>
#include <string>

namespace Amalgamation {

	class GLTexture : public Texture {

		uint32 m_TextureID;

	public:

		GLTexture();
		~GLTexture();

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, int Layer, const std::function<void()>& LoadFunction) override;

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, int Layer) override;

		bool LoadTextureData(const unsigned char* Data, int Width, int Height, int Channels, uint32 LODLevel, int Layer) override;

		bool LoadTextureData(const unsigned char* Data, int Width, int Height, int Channels, uint32 LODLevel, int Layer, const std::function<void()>& LoadFunction) override;

		void Bind()   const;
		void Unbind() const;

	};

}

#include "GLTexture.inl"