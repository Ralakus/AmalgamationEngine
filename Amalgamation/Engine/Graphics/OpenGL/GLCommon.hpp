#pragma once

#include <glad/glad.h>
#include <Core/Math/Vector/Vector3.hpp>
#include <Core/Math/Vector/Vector4.hpp>
#include <Core/Math/Quaternion/Quaternion.hpp>
#include <Core/Math/Matrix/Matrix4x4.hpp>
#include <Core/Utilities/Log.hpp>
#include <Core/Platform/Platform.hpp>

#include <cstdio>
#include <string>

namespace Amalgamation {
	class GLErrorManagement {
	public:
		static GLenum GLCheckError() { return glGetError(); }
		static bool GLLogCall(const char* function, const char* file, int line) {
			GLenum error = GLCheckError();
			if (error != GL_NO_ERROR) {
				//printf("[OpenGL Error]: (%u): %s , %s : %i", error, function, file, line);
				std::string errorStr = "[OpenGL Error]: (" + std::to_string(error) + "): " + function + ", " + file + " : " + std::to_string(line);
				AE_LOG_ERROR(errorStr.c_str());
				return false;
			}
			return true;
		}
	};
}
#if defined(GL_NO_EXEC)
#define GLCall(x)
#elif _DEBUG
#define GLCall(x) Amalgamation::GLErrorManagement::GLCheckError(); x; if(!Amalgamation::GLErrorManagement::GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
#define GLCall(x) x;
#endif