#include "engine.h"

#include <memory>
#include <fmt/core.h>
#include <fmt/color.h>
#include <glad/glad.h>

#include "utils.h"
#include "settings.h"

Engine::Engine()
{

    init();

    
}

void Engine::loop()
{
    while (m_window->is_running)
    {
        m_window->update();
        m_renderer->render();
    }

    // engine cleanup
}

void Engine::init()
{

    if (!glfwInit())
    {
        // failed to initialize glfw
        Utils::errorMessage("ENGINE::CORE::GLFW", "GLFW failed to initialize");
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = std::make_unique<Window>();
    m_renderer = std::make_unique<Renderer>(m_window.get());

}

void Engine::cleanup()
{
    glfwTerminate();
}