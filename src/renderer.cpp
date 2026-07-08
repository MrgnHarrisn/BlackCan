#include "renderer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

Renderer::Renderer(Window *target) : m_target(target) {}

void Renderer::render() {
  pre_frame();

  m_render();

  post_frame();

  finish_frame(); // change to submit frame (more implicit)
}

void Renderer::pre_frame() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::m_render() {
  // actual mesh rendering
}

void Renderer::post_frame() {
  // do some post processing maybe?
}

void Renderer::finish_frame() { glfwSwapBuffers(m_target->getHandle()); }

void Renderer::clear() {}