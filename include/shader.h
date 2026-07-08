#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

enum class ShaderKind
{
    Graphics,
    Compute
};

class Shader
{
public:

    Shader(const std::string &shader_name, ShaderKind kind = ShaderKind::Graphics);
    void use();
    unsigned int ID;

    // uniforms and stuff
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setDouble(const std::string &name, double value);

    // vectors
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setVec2(const std::string &name, float x, float y);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setVec4(const std::string &name, float x, float y, float z, float w);

    // matrices
    void setMat2(const std::string &name, const glm::mat2 &mat, bool transpose = false);
    void setMat3(const std::string &name, const glm::mat3 &mat, bool transpose = false);
    void setMat4(const std::string &name, const glm::mat4 &mat, bool transpose = false);
    
private:
    ShaderKind kind;
    unsigned int create_shader(const std::string &shader_name, ShaderKind kind);

    // cache uniforms
    mutable std::unordered_map<std::string, int> m_uniformLocationCache;
    int getUniformLocation(const std::string &name) const;
};