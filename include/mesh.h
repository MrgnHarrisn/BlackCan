#pragma once

#include "shader.h"
#include "texture.h"
#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> verts, std::vector<unsigned int> indi, std::vector<Texture> texs);
    void Draw(Shader& shader);

    // delete copy constructor and copy assignment
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // Add move constructor and move assignment
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    ~Mesh();

private:
    unsigned int VAO, VBO, EBO;
    void setup();
};