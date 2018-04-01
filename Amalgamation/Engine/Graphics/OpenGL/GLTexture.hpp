#pragma once

#include <Core/Graphics/Texture.hpp>
#include "GLCommon.hpp"

#include <stb_image.h>
#include <string>

namespace Amalgamation {

	class GLTexture : public Texture {

		uint32 m_TextureID;

	public:

		GLTexture() : Texture(API::OpenGL) {}
		~GLTexture()                       {}

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, int Layer, std::function<void()> LoadFunction) override {
			if (Layer >= 0 && Layer <= 31) {
				m_Layer = Layer;
			}
			else {
				throw Error("AE: Texture layer out of range!");
			}
			GLCall(glGenTextures(1, &m_TextureID));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

			LoadFunction();

			stbi_set_flip_vertically_on_load(Flip);

			unsigned char* LoadedData = stbi_load(FilePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

			if (LoadedData) {
				switch (m_Channels)
				{
				case 3: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, LoadedData)); break;
				case 4: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LoadedData)); break;
				default:
					printf("Number of color channels couldn't be identified!\n");
					return false;
					break;
				}
				GLCall(glGenerateMipmap(GL_TEXTURE_2D));
			}
			else {
				printf("Failed to load texture from: %s\n", FilePath);
				return false;
			}
			stbi_image_free(LoadedData);
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			return true;
		}

		bool LoadTexture(const std::string& FilePath, bool Flip, uint32 LODLevel, int Layer) override {
			m_Layer = Layer;
			GLCall(glGenTextures(1, &m_TextureID));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_set_flip_vertically_on_load(Flip);

			unsigned char* LoadedData = stbi_load(FilePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

			if (LoadedData) {
				switch (m_Channels)
				{
				case 3: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, LoadedData)); break;
				case 4: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LoadedData)); break;
				default:
					printf("Number of color channels couldn't be identified!\n");
					return false;
					break;
				}
				GLCall(glGenerateMipmap(GL_TEXTURE_2D));
			}
			else {
				printf("Failed to load texture from: %s\n", FilePath);
				return false;
			}
			stbi_image_free(LoadedData);
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
			return true;
		}

		void Bind()   const {
			switch (m_Layer) {
			case 0:  GLCall(glActiveTexture(GL_TEXTURE0)); 	break;
			case 1:  GLCall(glActiveTexture(GL_TEXTURE1));	break;
			case 2:  GLCall(glActiveTexture(GL_TEXTURE2));	break;
			case 3:  GLCall(glActiveTexture(GL_TEXTURE3));	break;
			case 4:  GLCall(glActiveTexture(GL_TEXTURE4));	break;
			case 5:  GLCall(glActiveTexture(GL_TEXTURE5));	break;
			case 6:  GLCall(glActiveTexture(GL_TEXTURE6));	break;
			case 7:  GLCall(glActiveTexture(GL_TEXTURE7));	break;
			case 8:  GLCall(glActiveTexture(GL_TEXTURE8));	break;
			case 9:  GLCall(glActiveTexture(GL_TEXTURE9));	break;
			case 10: GLCall(glActiveTexture(GL_TEXTURE10));	break;
			case 11: GLCall(glActiveTexture(GL_TEXTURE11));	break;
			case 12: GLCall(glActiveTexture(GL_TEXTURE12));	break;
			case 13: GLCall(glActiveTexture(GL_TEXTURE13));	break;
			case 14: GLCall(glActiveTexture(GL_TEXTURE14));	break;
			case 15: GLCall(glActiveTexture(GL_TEXTURE15));	break;
			case 16: GLCall(glActiveTexture(GL_TEXTURE16));	break;
			case 17: GLCall(glActiveTexture(GL_TEXTURE17));	break;
			case 18: GLCall(glActiveTexture(GL_TEXTURE18)); break;
			case 19: GLCall(glActiveTexture(GL_TEXTURE19)); break;
			case 20: GLCall(glActiveTexture(GL_TEXTURE20)); break;
			case 21: GLCall(glActiveTexture(GL_TEXTURE21)); break;
			case 22: GLCall(glActiveTexture(GL_TEXTURE22)); break;
			case 23: GLCall(glActiveTexture(GL_TEXTURE23)); break;
			case 24: GLCall(glActiveTexture(GL_TEXTURE24)); break;
			case 25: GLCall(glActiveTexture(GL_TEXTURE25)); break;
			case 26: GLCall(glActiveTexture(GL_TEXTURE26)); break;
			case 27: GLCall(glActiveTexture(GL_TEXTURE27)); break;
			case 28: GLCall(glActiveTexture(GL_TEXTURE28)); break;
			case 29: GLCall(glActiveTexture(GL_TEXTURE29)); break;
			case 30: GLCall(glActiveTexture(GL_TEXTURE30)); break;
			case 31: GLCall(glActiveTexture(GL_TEXTURE31)); break;
			default: break;
			}
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
		}
		void Unbind() const {
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}

	};

}