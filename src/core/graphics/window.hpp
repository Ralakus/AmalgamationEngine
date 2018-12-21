#pragma once

#include <string>

#include "graphics_class.hpp"
#include <core/platform/platform.hpp>

namespace amalgamation {

    class Window : public GraphicsClass {

    protected:

        std::string _title;
        std::size_t _width, _height;
        bool _fullscreen;
        bool _valid;

    public:

        Window(const std::string& title, std::size_t width, std::size_t height, bool fullscreen, API api)
            : GraphicsClass(api), _title(title), _width(width), _height(height), _fullscreen(fullscreen), _valid(false) {}

        Window(API api) 
            : GraphicsClass(api), _title("Amalgamation"), _width(1280), _height(720), _fullscreen(false), _valid(false) {}

        virtual ~Window() {}

        const std::string& get_title() const { return _title;  }
        std::size_t get_height      () const { return _height; }
        std::size_t get_width       () const { return _width;  }

        bool is_fullscreen() const { return _fullscreen; }
        bool is_valid     () const { return _valid;      }

        virtual void set_title(const std::string& title) { _title = title; }
        virtual void set_title(const char* title)        { _title = title; }

        virtual bool open() = 0;
        virtual bool open(const std::string& title, std::size_t width, std::size_t height, bool fullscreen) = 0;
        virtual bool update() = 0;
        virtual bool close()  = 0;

        virtual void resize(std::size_t width, std::size_t height) = 0;

    };


}