#pragma once

#include <string>

class Texture
{
public:
    Texture();
    Texture(std::string &filepath);
    void loadTexture(std::string& filepath);
    unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
    unsigned int id;
    std::string type;
    std::string path;

private:
};