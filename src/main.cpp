#include <iostream>
#include <cxxopts.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/utilities/logger.hpp"

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

    GLFWwindow* window;

    if (!glfwInit()) {
        ae::error() << "Failed to initialize glfw" << std::endl;;
        return EXIT_FAILURE;
    }

    window = glfwCreateWindow(1280, 720, "A window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        ae::error() << "Failed to initialize glad!" << std::endl;
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
            glColor3f(0.f, 0.f, 1.f);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.5f, -0.5f);
            glVertex2f(0.5f, 0.5f);
        glEnd();

        glBegin(GL_TRIANGLES);
            glColor3f(0.f, 1.f, 0.f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(-0.5f, 0.5f);
            glVertex2f(-0.5f, -0.5f);
        glEnd();


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return EXIT_SUCCESS;

}
