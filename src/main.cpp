#include <iostream>
#include <cxxopts.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/utilities/logger.hpp>
#include <core/graphics/window.hpp>

#include <engine/graphics/opengl/glwindow.hpp>

#include <engine/graphics/opengl/buffers/glvertex_array.hpp>
#include <engine/graphics/opengl/buffers/glelement_buffer.hpp>

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
    window.open();

    const char* vtxshadersrc = R"glsl(#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})glsl";

    unsigned int vertex_shader;
    GLCALL(vertex_shader = glCreateShader(GL_VERTEX_SHADER));
    GLCALL(glShaderSource(vertex_shader, 1, &vtxshadersrc, NULL));
    GLCALL(glCompileShader(vertex_shader));

    const char* fgmtshadersrc = R"glsl(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.1f, 0.9f, 0.1f, 1.0f);
})glsl";

    unsigned int fragment_shader;
    GLCALL(fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));
    GLCALL(glShaderSource(fragment_shader, 1, &fgmtshadersrc, NULL));
    GLCALL(glCompileShader(fragment_shader));

    unsigned int shader_program;
    GLCALL(shader_program = glCreateProgram());

    GLCALL(glAttachShader(shader_program, vertex_shader));
    GLCALL(glAttachShader(shader_program, fragment_shader));
    GLCALL(glLinkProgram(shader_program));

    GLCALL(glUseProgram(shader_program));

    GLCALL(glDeleteShader(vertex_shader));
    GLCALL(glDeleteShader(fragment_shader));

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
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

    ae::noticeln("vao: ", vao.get_id(), ", vbo: ", vbo.get_id(),", ebo: ", ebo.get_id());

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

    window.close();

    return EXIT_SUCCESS;

}
