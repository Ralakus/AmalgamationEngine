#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <core/platform/platform.hpp>
#include <core/utilities/logger.hpp>

namespace amalgamation {

    template<class... T>
    inline decltype(notice()) glnotice(T&&... args) {
        return ((notice(ansi::yellow, "[ gl::", ansi::cyan, "notice", ansi::yellow, " ]: ", ansi::reset)) << ... << std::forward<T&&>(args));
    }

    template<class... T>
    inline decltype(glnotice()) glnoticeln(T&&... args) {
        return ((glnotice()) << ... << std::forward<T&&>(args)) << std::endl;
    }

    template<class... T>
    inline decltype(error()) glerror(T&&... args) {
        return ((error(ansi::yellow, "[ gl::", ansi::red, "error", ansi::yellow, " ]: ", ansi::reset)) << ... << std::forward<T&&>(args));
    }

    template<class... T>
    inline decltype(glerror()) glerrorln(T&&... args) {
        return ((glerror()) << ... << std::forward<T&&>(args)) << std::endl;
    }

    class GLErrorHandler {
    public:
        static GLenum glcheck_error() { return glGetError(); }
        static bool gllog_call(const char* function, const char* file, int line) {
			GLenum error = glcheck_error();
			if (error != GL_NO_ERROR) {
                glerrorln("(", error, "): ", function, ", ", file, " : ", line);
				return false;
			}
			return true;
        }
    };

}

#if defined(AE_GL_NO_EXEC)
    #define GLCALL(x)
#elif AE_BUILD_DEBUG
    #define GLCALL(x) amalgamation::GLErrorHandler::glcheck_error(); x; amalgamation::GLErrorHandler::gllog_call(#x, __FILE__, __LINE__)
#else
    #define GLCALL(x) x
#endif