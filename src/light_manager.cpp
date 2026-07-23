#include "light_manager.h"

LightManager::LightManager()
{
    is_dirty = true;
    glGenBuffers(1, &m_lightSSBO);
}

LightManager::~LightManager()
{
    glDeleteBuffers(1, &m_lightSSBO);
}

void LightManager::addPointLight(glm::vec3 position, float radius, glm::vec3 color, float intensity)
{
    GPULight light;
    light.position = glm::vec4(position, radius);
    light.color = glm::vec4(color, intensity);
    light.direction = glm::vec4(0, 0, 0, 0);

    m_lights.push_back(light);
    is_dirty = true;
}

void LightManager::updateGPU()
{
    if (!is_dirty || m_lights.empty()) return;

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_lightSSBO);

    glBufferData(GL_SHADER_STORAGE_BUFFER, m_lights.size() * sizeof(GPULight), m_lights.data(), GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_lightSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    is_dirty = false;

}