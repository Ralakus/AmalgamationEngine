#pragma once

#include <vector>

#include "../glcommon.hpp"

namespace amalgamation {

    class GLElementBuffer {

        std::uint32_t _bufferid;
        std::size_t   _count;
        mutable bool  _bound;

    public:

        GLElementBuffer()
            : _bufferid(0), _count(0), _bound(false) {}

        GLElementBuffer(const uint32_t* data, std::size_t count)
            : _bufferid(0), _count(0), _bound(false) {
            this->create();
            this->push_data(data, count);
        }
        
        ~GLElementBuffer() {
            this->destroy();
        }

        void push_data(const uint32_t* data, std::size_t count) {
            this->bind();
            this->_count = count;
            GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW));
        }

        void create() {
            this->destroy();
            GLCALL(glGenBuffers(1, &this->_bufferid));
        }

        void destroy() {
            glnoticeln("Destroy called for element buffer, id: ", this->_bufferid);
            if(this->_bufferid != 0) {
                glnoticeln("Element buffer destroy idcheck passed");
                this->unbind();
                GLCALL(glDeleteBuffers(1, &this->_bufferid));
            }
        }

        void bind  () const {
            if(!this->_bound) {
                this->_bound = true;
                GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_bufferid));
            }
        }
        void unbind() const {
            if(this->_bound) {
                this->_bound = false;
                GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            }
        }

        std::size_t get_count() const { return this->_count;    }
        std::uint32_t get_id () const { return this->_bufferid; }

    };

}