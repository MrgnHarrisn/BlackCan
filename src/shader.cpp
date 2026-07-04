#include "shader.h"

#include <glad/glad.h>

#include "utils.h"

using namespace std;

Shader::Shader(const string& shader_name) {
    this->ID = create_shader(shader_name);
}

unsigned int Shader::create_shader(const string& shader_name) {

    // get the actual source files
    const char* vertSrc = Utils::readFileToString(shader_name + ".vs").c_str();
    const char* fragSrc = Utils::readFileToString(shader_name + ".fs").c_str();

    // create vertex shader
    unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    // create fragment shader
    unsigned int fragShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    // create shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    // clean up shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    // return program ID
    return shaderProgram;
}