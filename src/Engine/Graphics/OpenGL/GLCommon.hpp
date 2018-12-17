#pragma once

#include <glad/glad.h>
#include <Core/Platform/Platform.hpp>

#include <cstdio>
#include <string>

#include <rang.hpp>
#undef max
#undef min
#undef APIENTRY

namespace Amalgamation {
	class GLErrorManagement {
	public:
		static GLenum GLCheckError() { return glGetError(); }
		static bool GLLogCall(const char* function, const char* file, int line) {
			GLenum error = GLCheckError();
			if (error != GL_NO_ERROR) {
				//printf("[OpenGL Error]: (%u): %s , %s : %i", error, function, file, line);
				std::string errorStr = "(" + std::to_string(error) + "): " + function + ", " + file + " : " + std::to_string(line);
				//AE_LOG_ERROR(errorStr.c_str());
				std::cerr << rang::fgB::red << "[ gl::error ]: " << rang::fg::reset << errorStr << rang::fgB::yellow << "\nEND" << rang::fg::reset << std::endl;
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