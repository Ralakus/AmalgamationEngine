#pragma once

namespace amalgamation {

    enum class API {
        opengl, vulkan, other
    };

    class GraphicsClass {

    protected:

        const API _api;

    public:

        GraphicsClass(API api) : _api(api) {}
        virtual ~GraphicsClass() {}

        API get_api() const { return _api; }

    };

}