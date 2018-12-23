#pragma once

#include "glarray_buffer.hpp"

namespace amalgamation {

    class GLVertexArray {

        std::uint32_t _arrayid;
        mutable bool  _bound;

    public:

        GLVertexArray()
            : _arrayid(0), _bound(false) {}

        ~GLVertexArray() {
            this->destroy();
        }

        void create() {
            this->destroy();
            GLCALL(glGenVertexArrays(1, &_arrayid));
        }

        void destroy() {
            glnoticeln("Destroy called for vertex array, id: ", this->_arrayid);
            if(this->_arrayid != 0) {
                glnoticeln("Vertex array destroy idcheck passed");
                this->unbind();
                GLCALL(glDeleteVertexArrays(1, &_arrayid));
            }
        }

        void bind  () const {
            if(!this->_bound) {
                this->_bound = true;
                GLCALL(glBindVertexArray(this->_arrayid));
            }
        }
        void unbind() const {
            if(this->_bound) {
                this->_bound = false;
                GLCALL(glBindVertexArray(0));
            }
        }

        std::uint32_t get_id() const { return this->_arrayid; }

        void set_buffer(const GLArrayBuffer& buffer) {
            this->bind();
            buffer.bind();

            const auto& elements = buffer.get_layout().get_elements();
            std::size_t offset = 0;

            for(std::uint32_t i = 0; i < elements.size(); i++) {

                GLCALL(glEnableVertexAttribArray(i));

                GLCALL(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, buffer.get_layout().get_stride(), reinterpret_cast<const void*>(offset));
                offset += elements[i].count * GLArrayBufferLayout::get_size_of_type(elements[i].type));

            }
        }

    };

}