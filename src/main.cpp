#include <iostream>
#include <cxxopts.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/utilities/logger.hpp>
#include <core/graphics/window.hpp>

#include <engine/graphics/opengl/glwindow.hpp>

#include <engine/graphics/opengl/buffers/glvertex_array.hpp>
#include <engine/graphics/opengl/buffers/glelement_buffer.hpp>

#include <engine/graphics/opengl/glshader.hpp>

namespace amalgamation {
    constexpr auto version = "0.1.0";
}

namespace ae = amalgamation;

int main(int argc, char** argv) {

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
    if(!window.open()) {
        return EXIT_FAILURE;
    }

    const char* shader_src = R"glsl(@V#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}@F#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.1f, 0.9f, 0.1f, 1.0f);
}@)glsl";

    ae::GLShader shader(shader_src);
    shader.bind();

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    ae::GLVertexArray vao;
    vao.create();
    vao.bind();

    ae::GLArrayBuffer vbo(vertices, sizeof(vertices));
    vbo.bind();

    vbo.get_layout().push<float>(3);

    ae::GLElementBuffer ebo(indices, sizeof(indices));
    ebo.bind();

    vao.set_buffer(vbo);

    ae::noticeln("shader: ", shader.get_id(), ", vao: ", vao.get_id(), ", vbo: ", vbo.get_id(),", ebo: ", ebo.get_id());

    GLCALL(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));

    GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));

    while (window.is_valid()) {
        
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        if(window.update() == false) {
            ae::glnoticeln("Window close requested");
        }

    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();

    shader.destroy();

    window.close();

    return EXIT_SUCCESS;

}
