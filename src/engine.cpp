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

	// trying to get a model to render correctly
	Model bag("mic/scene.gltf");
	Shader gfx("shaders/basic");
	Camera main_camera(glm::vec3(0.f, 0.f, 50.f));

	float rot_speed = 1;
	float current_angle = 0;

	float dt = 0;
	float last_frame = 0;
	float current_time = 0;

	while (m_window->is_running)
	{

		last_frame = current_time;
		current_time = glfwGetTime();

		dt = current_time - last_frame;

		current_angle += rot_speed * dt;

		m_window->update();

		glm::mat4 transform = glm::mat4(1.f);
		transform = glm::rotate(transform, current_angle, glm::vec3(0, 1, 0));

		transform = glm::scale(transform, glm::vec3(5.f));


		m_renderer->submit(&bag, &gfx, transform);

		m_renderer->render(main_camera);
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