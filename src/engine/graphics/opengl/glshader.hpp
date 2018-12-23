#pragma once

#include <core/graphics/shader.hpp>

#include "glcommon.hpp"

#include <string_view>
#include <memory>

namespace amalgamation {

    class GLShader : public Shader {

        std::uint32_t _shaderid;

        mutable bool _bound;

        std::string_view _vertex_src;
        std::string_view _fragment_src;

        bool _post_load() override;

    public:

        GLShader()
            : Shader(API::opengl), _shaderid(0), _bound(false) {}
        GLShader(const std::string& src)
            : Shader(API::opengl), _shaderid(0), _bound(false) {
            this->load(src);
        }

        ~GLShader() {}

        void bind  () const {
            if(!this->_bound) {
                this->_bound = true;
                GLCALL(glUseProgram(this->_shaderid));
            }
        }

        void unbind() const {
            if(this->_bound) {
                this->_bound = false;
                GLCALL(glUseProgram(0));
            }
        }

        void destroy() {
            if(this->_shaderid == 0) {
                this->unbind();
                GLCALL(glDeleteProgram(this->_shaderid));
                this->_shaderid = 0;
            }
        }

    };

    bool GLShader::_post_load() {

        glnoticeln("Function called");

        GLCALL(this->_shaderid = glCreateProgram());

        GLCALL(std::uint32_t vertex_id   = glCreateShader(GL_VERTEX_SHADER));
        GLCALL(std::uint32_t fragment_id = glCreateShader(GL_FRAGMENT_SHADER));

        std::size_t substr_begin = 0;

        enum class ShaderType {
            Vertex, Fragment, None
        } parse_type = ShaderType::None;

        for(std::size_t i = 0; i < this->_shader_src.length(); i++) {
            if(this->_shader_src[i] == '@') {

                if(parse_type == ShaderType::Vertex) {
                    this->_vertex_src   = std::string_view(this->_shader_src.c_str() + substr_begin, (i) - substr_begin);
                } else if(parse_type == ShaderType::Fragment) {
                    this->_fragment_src = std::string_view(this->_shader_src.c_str() + substr_begin, (i) - substr_begin);
                }

                if(i < (this->_shader_src.length() - 1)) {

                    i++;

                    switch(this->_shader_src[i]) {

                        case 'V': {
                            parse_type = ShaderType::Vertex;
                            substr_begin = i + 1;
                        }
                        break;

                        case 'F': {
                            parse_type = ShaderType::Fragment;
                            substr_begin = i + 1;
                        }
                        break;

                        default: {
                            parse_type = ShaderType::None;
                        }
                        break;

                    }
                }
            }
        }

        int compile_result = 0;

        std::size_t vertex_src_length = this->_vertex_src.length();
        const char* vertex_src_data = this->_vertex_src.data();
        GLCALL(glShaderSource(vertex_id, 1, &vertex_src_data, reinterpret_cast<GLint*>(&vertex_src_length)));
        GLCALL(glCompileShader(vertex_id));

        GLCALL(glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &compile_result));
        if(compile_result == GL_FALSE) {

            GLint length = 512;
            GLCALL(glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> msg { new char[length] };

            GLCALL(glGetShaderInfoLog(vertex_id, length, NULL, msg.get()));

            glerrorln("Failed to compile shader: \n", msg.get());

            GLCALL(glDeleteShader(vertex_id));
            GLCALL(glDeleteShader(fragment_id));
            GLCALL(glDeleteProgram(this->_shaderid));
            return false;
        }

        std::size_t fragment_src_length = this->_fragment_src.length();
        const char* fragment_src_data = this->_fragment_src.data();
        GLCALL(glShaderSource(fragment_id, 1, &fragment_src_data, reinterpret_cast<GLint*>(&fragment_src_length)));
        GLCALL(glCompileShader(fragment_id));

        GLCALL(glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &compile_result));
        if(compile_result == GL_FALSE) {

            GLint length = 512;
            GLCALL(glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> msg { new char[length] };

            GLCALL(glGetShaderInfoLog(fragment_id, length, NULL, msg.get()));

            glerrorln("Failed to compile shader: \n", msg.get());

            GLCALL(glDeleteShader(vertex_id));
            GLCALL(glDeleteShader(fragment_id));
            GLCALL(glDeleteProgram(this->_shaderid));
            return false;
        }

        GLCALL(glAttachShader(this->_shaderid, vertex_id));
        GLCALL(glAttachShader(this->_shaderid, fragment_id));

        GLCALL(glLinkProgram(this->_shaderid));
        GLCALL(glValidateProgram(this->_shaderid));

        GLCALL(glGetProgramiv(this->_shaderid, GL_LINK_STATUS, &compile_result));
        if(compile_result == GL_FALSE) {

            GLint length = 512;
            GLCALL(glGetProgramiv(this->_shaderid, GL_INFO_LOG_LENGTH, &length));
            std::unique_ptr<char[]> msg { new char[length] };

            GLCALL(glGetProgramInfoLog(this->_shaderid, length, NULL, msg.get()));

            glerrorln("Failed to compile shader: \n", msg.get());

            GLCALL(glDeleteShader(vertex_id));
            GLCALL(glDeleteShader(fragment_id));
            GLCALL(glDeleteProgram(this->_shaderid));
            return false;
        }

        GLCALL(glDeleteShader(vertex_id));
        GLCALL(glDeleteShader(fragment_id));

        return true;

    }

}