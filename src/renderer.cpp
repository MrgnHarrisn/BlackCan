#include "renderer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

Renderer::Renderer(Window *target) : m_target(target) {}

void Renderer::render(Camera& active_camera)
{
	pre_frame();

	m_render(active_camera);

	post_frame();

	submit_frame();
}

void Renderer::pre_frame()
{
	Renderer::clear();
}

void Renderer::m_render(Camera& active_camera)
{

	float aspect = (float)m_target->m_width / (float)m_target->m_height;
	glm::mat4 projection = active_camera.getProjectionMatrix(aspect);
	glm::mat4 view = active_camera.GetViewMatrix();

	// while the queue isn't empty
	while (!m_queue.empty()) {
		RenderCommand item = m_queue.front();
		m_queue.pop();

		item.shader->use();

		// set the shader values
		item.shader->setMat4("projection", projection);
		item.shader->setMat4("view", view);
		item.shader->setVec3("viewPos", active_camera.Position);
		item.shader->setMat4("model", item.transform);
		item.shader->setInt("u_activeLightCount", 1);

		// draw the model
		item.model->Draw(*(item.shader));

	}
}

void Renderer::post_frame()
{
	// do some post processing maybe?
}

void Renderer::submit_frame()
{
	glfwSwapBuffers(m_target->getHandle());
}

void Renderer::clear() 
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::submit(Model* model, Shader* shader, glm::mat4 transform)
{
	m_queue.push(RenderCommand{
		shader, model, transform
	});
}