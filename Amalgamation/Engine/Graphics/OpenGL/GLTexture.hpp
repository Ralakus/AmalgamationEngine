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

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, int Layer, std::function<void()> LoadFunction) override;

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, int Layer) override;

		void Bind()   const;
		void Unbind() const;

	};

}

#include "GLTexture.inl"