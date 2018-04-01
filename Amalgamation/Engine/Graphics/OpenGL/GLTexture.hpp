#pragma once

#include <Core/Graphics/Texture.hpp>
#include "GLCommon.hpp"

#include <stb_image.h>
#include <string>

namespace Amalgamation {

	class GLTexture : public Texture {
	public:

		GLTexture() : Texture(API::OpenGL) {}
		~GLTexture()                       {}

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, std::function<void()> LoadFunction) override {

		}

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel) override {

		}

		void Bind()   const {}
		void Unbind() const {}

	};

}