#pragma once

#include "shader.h"

#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> verts, std::vector<unsigned int> indi, std::vector<Texture> texs);
    void Draw(Shader& shader);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

private:
    unsigned int VAO, VBO, EBO;
    void setup();
};