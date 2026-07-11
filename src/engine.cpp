#include "engine.h"

#include <fmt/color.h>
#include <fmt/core.h>
#include <glad/glad.h>
#include <memory>

#include "settings.h"
#include "utils.h"
#include "shader.h"
#include "model.h"

Engine::Engine() { init(); }

void Engine::loop()
{

	Model m("bag/scene.gltf");

	// Shader gfx("shaders/basic");

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

void Engine::cleanup() { glfwTerminate(); }