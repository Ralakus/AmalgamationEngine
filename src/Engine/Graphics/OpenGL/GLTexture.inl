
#include <Core/Utilities/File.hpp>
#include "GLTexture.hpp"

namespace Amalgamation {

	FORCEINLINE GLTexture::GLTexture() : Texture(API::OpenGL) {}

	FORCEINLINE GLTexture::~GLTexture() {}

	FORCEINLINE bool GLTexture::LoadTexture(const std::string & FilePath, bool Flip, uint32_t LODLevel, int Layer, const std::function<void()>& LoadFunction) {
		if (Layer >= 0 && Layer <= 31) {
			m_Layer = Layer;
		}
		else {
			throw std::runtime_error("AE: Texture layer out of range!");
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
			printf("Failed to load texture from: %s\n", FilePath.c_str());
			return false;
		}
		stbi_image_free(LoadedData);
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		return true;
	}

	FORCEINLINE bool GLTexture::LoadTexture(const std::string & FilePath, bool Flip, uint32_t LODLevel, int Layer) {
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
			printf("Failed to load texture from: %s\n", FilePath.c_str());
			unsigned char BrokenTexture[3] = { 0xFF, 0xFF, 0xFF };
			GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, BrokenTexture));
			return false;
		}


		/*std::vector<unsigned char> RawData;
		bool Stop = false;
		unsigned long long int i = -1;
		while (!Stop) {
			if (LoadedData[++i] == 0) {
				Stop = true;
			}
			else {
				RawData.emplace_back(LoadedData[i]);
			}
		}

		File RawDataF("RawDataOutput.txt");
		std::string RawDataStr;
		for (auto I : RawData) {
			RawDataStr += (std::to_string(I) + ", ");
		}
		RawDataF.Write(RawDataStr);*/


		stbi_image_free(LoadedData);
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		return true;
	}

	FORCEINLINE bool GLTexture::LoadTextureData(const unsigned char * Data, int Width, int Height, int Channels, uint32_t LODLevel, int Layer) {
		m_Channels = Channels;
		m_Width = Width;
		m_Height = Height;
		m_Layer = Layer;

		GLCall(glGenTextures(1, &m_TextureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		switch (m_Channels) {
		case 3: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data)); break;
		case 4: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data)); break;
		default:
			printf("Number of color channels is invalid!\n");
			return false;
			break;
		}
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		return true;
	}

	FORCEINLINE bool GLTexture::LoadTextureData(const unsigned char * Data, int Width, int Height, int Channels, uint32_t LODLevel, int Layer, const std::function<void()>& LoadFunction) {
		m_Channels = Channels;
		m_Width = Width;
		m_Height = Height;
		m_Layer = Layer;

		GLCall(glGenTextures(1, &m_TextureID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

		LoadFunction();

		switch (m_Channels) {
		case 3: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data)); break;
		case 4: GLCall(glTexImage2D(GL_TEXTURE_2D, LODLevel, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data)); break;
		default:
			printf("Number of color channels is invalid!\n");
			return false;
			break;
		}
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		return true;
	}

	FORCEINLINE void GLTexture::Bind() const {
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

	FORCEINLINE void GLTexture::Unbind() const {
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}


}