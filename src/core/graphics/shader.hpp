#pragma once

#include "graphics_class.hpp"

#include <string>

namespace amalgamation {

    class Shader : public GraphicsClass {

    protected:

        std::string _shader_src;

        virtual bool _post_load() { return false; };

    public:

        Shader(API api)
            : GraphicsClass(api), supports_lighting(false) {}

        virtual ~Shader() {}

        bool supports_lighting;

        bool load(const std::string& src) {
            this->_shader_src = src;
            return this->_post_load();
        }

    };

}