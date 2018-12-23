#pragma once

#include <vector>

#include "../glcommon.hpp"

namespace amalgamation {

    struct GLArrayElement {

        std::uint32_t type, count;
        std::int8_t   normalized ;

        GLArrayElement(std::uint32_t type, std::uint32_t count, std::int8_t normalized)
            : type(type), count(count), normalized(normalized) {}

    };

    class GLArrayBufferLayout {

        std::vector<GLArrayElement> _elements;
        std::uint32_t _stride;

    public:

        GLArrayBufferLayout()
            : _stride(0) {}

        static std::size_t get_size_of_type(std::uint32_t type) {
            switch (type) {
                case GL_FLOAT:         return sizeof(GLfloat);
                case GL_INT:           return sizeof(GLint);
                case GL_UNSIGNED_INT:  return sizeof(GLuint);
                case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
                default: return 0;
            }
        }

        template<class T>
        void push(int count) {
            // static_assert(false, "Element push type is not supported!");
            glerrorln("Invalid opengl element push type!");
        }

        const decltype(_elements)& get_elements() const { return this->_elements; }
        std::uint32_t get_stride() const { return this->_stride; }

    };

    template<>
    inline void GLArrayBufferLayout::push<float>(int count) {
        this->_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
        this->_stride = count * GLArrayBufferLayout::get_size_of_type(GL_FLOAT);
    }

    template<>
    inline void GLArrayBufferLayout::push<int>(int count) {
        this->_elements.emplace_back(GL_INT, count, GL_FALSE);
        this->_stride = count * GLArrayBufferLayout::get_size_of_type(GL_INT);
    }

    template<>
    inline void GLArrayBufferLayout::push<std::uint32_t>(int count) {
        this->_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
        this->_stride = count * GLArrayBufferLayout::get_size_of_type(GL_UNSIGNED_INT);
    }

    template<>
    inline void GLArrayBufferLayout::push<std::uint8_t>(int count) {
        this->_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_FALSE);
        this->_stride = count * GLArrayBufferLayout::get_size_of_type(GL_UNSIGNED_BYTE);
    }


    class GLArrayBuffer {

        std::uint32_t _bufferid;
        GLArrayBufferLayout _layout;
        mutable bool _bound;

    public:

        GLArrayBuffer() 
            : _bufferid(0), _bound(false) {}

        GLArrayBuffer(const void* data, size_t size) 
            : _bufferid(0), _bound(false) {
            this->create();
            this->push_data(data, size);
        }
        
        ~GLArrayBuffer() {
            this->destroy();
        }

        void create() {
            this->destroy();
            GLCALL(glGenBuffers(1, &this->_bufferid));
        }

        void destroy() {
            glnoticeln("Destroy called for array buffer, id: ", this->_bufferid);
            if(this->_bufferid != 0) {
                glnoticeln("Array buffer destroy idcheck passed");
                this->unbind();
                glnoticeln("Array buffer ptr: ", &this->_bufferid);
                GLCALL(glDeleteBuffers(GL_ARRAY_BUFFER, &this->_bufferid));
            }
        }

        void bind()   const {
            if(!this->_bound) {
                this->_bound = true;
                GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->_bufferid));
            }
        }

        void unbind() const {
            if(this->_bound) {
                this->_bound = false;
                GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
                glnoticeln("Unbind called");
            }
        }

        void push_data(const void* data, std::size_t size) {
            this->bind();
            GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
        }

              GLArrayBufferLayout& get_layout()       { return this->_layout; }
        const GLArrayBufferLayout& get_layout() const { return this->_layout; }

        std::uint32_t get_id() const { return this->_bufferid; }

    };

}