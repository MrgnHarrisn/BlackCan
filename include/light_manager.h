#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glad/glad.h>

// C++ Side
struct GPULight
{
    // std430 alignment rules applied
    alignas(16) glm::vec4 position;  // w component can store radius
    alignas(16) glm::vec4 color;     // w component can store intensity
    alignas(16) glm::vec4 direction; // w component can store light type (0=point, 1=dir)

    // Add spot light angles or other data here if needed, keeping 16-byte alignment
};

class LightManager
{
public:
    LightManager();
    ~LightManager();
    // only gonna use these for now
    void addPointLight(glm::vec3 position, float radius, glm::vec3 color, float intensity);
    void updateGPU();
private:
    std::vector<GPULight> m_lights;
    bool is_dirty;
    unsigned int m_lightSSBO;   // shader storage buffer object
};