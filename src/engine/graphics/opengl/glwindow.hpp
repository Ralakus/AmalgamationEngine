#pragma once

#include <core/graphics/window.hpp>

#include "glcommon.hpp"
#include "glfwinstance.hpp"

namespace amalgamation {

    class GLWindow : public Window {

    private:

        GLFWwindow*        _window;
        GLFWmonitor*       _monitor;
        const GLFWvidmode* _mode;

    public:

         GLWindow();
         GLWindow(const std::string& title, std::size_t width, std::size_t height, bool fullscreen = false);
        ~GLWindow();

        bool open() override;
        bool open(const std::string& title, std::size_t width, std::size_t height, bool fullscreen) override;
        bool update() override;
        bool close()  override;
        
        void resize(std::size_t width, std::size_t height) override;

    };

}

#include "glwindow.inl"