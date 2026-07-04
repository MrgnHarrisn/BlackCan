#pragma once

#include <string>

class Shader
{
public:
    Shader(const std::string& shader_name);
    void use();
    unsigned int ID;
private:
    unsigned int create_shader(const std::string& shader_name);
};