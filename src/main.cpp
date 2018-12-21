#include <iostream>
#include <cxxopts.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/utilities/logger.hpp>
#include <core/graphics/window.hpp>

#include <engine/graphics/opengl/glwindow.hpp>

namespace amalgamation {
    constexpr auto version = "0.1.0";
}

namespace ae = amalgamation;

int main(int argc, char* argv[]) {

    cxxopts::Options options("Amalgamation", "This is a project made using the Amalgamation Engine");

    options.add_options()
        ("v,version", "Displays version")
        ("h,help", "Prints help")
    ;

    options.help({""});

    try {
        auto cxxresult = options.parse(argc, argv);

        if(cxxresult.count("help")) {
            std::cout << options.help() << std::endl;
            return EXIT_SUCCESS;
        }

        if(cxxresult.count("version")) {
            std::cout << "Amalgamation version: " << ae::version << std::endl;
            return EXIT_SUCCESS;
        }

    } catch (cxxopts::OptionException& e) {

        ae::error() << e.what() << std::endl;
        return EXIT_FAILURE;

    }

    ae::GLWindow window("Window", 1280, 720, false);
    window.open();

    while (window.is_valid()) {

        if(window.update() == false) {
            ae::glnoticeln("Window close requested");
        }

    }

    window.close();

    return EXIT_SUCCESS;

}
