#pragma once

#include "glcommon.hpp"
#include <GLFW/glfw3.h>

namespace amalgamation {

    class GLFWInstance {

    public:

        static bool init()      { glnoticeln("glfw init"); return is_initialized() == false ? is_initialized(true, true),  glfwInit() == GLFW_TRUE : false; }

        static bool terminate() { glnoticeln("glfw term"); return is_initialized() == true  ? is_initialized(true, false), glfwTerminate(), true   : false; }

        static bool is_initialized(bool set = false, bool val = false) {
            static bool _initialized = false;
            if(set) {
                _initialized = val;
            }
            return _initialized;
        }

        static std::size_t open_windows(bool set = false, std::size_t count = 0) {
            static std::size_t _open_windows = 0;
            if(set) {
                _open_windows = count;
            }
            return _open_windows;
        }

    };

}