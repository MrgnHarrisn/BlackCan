#include "window.h"

#include <fmt/core.h>
#include <fmt/color.h>
#include <glad/glad.h>

#include "settings.h"
#include "utils.h"

Window::Window()
{
    create_window();
}

void Window::create_window()
{
    // load settings and then set this shit
    auto &settings = Settings::getInstance();

    m_width = settings.getWindowWidth();
    m_height = settings.getWindowHeight();
    string title = settings.getWindowTitle();
    m_is_resizeable = settings.isWindowResizable();

    glfwWindowHint(GLFW_RESIZABLE, m_is_resizeable);

    m_window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);

    if (m_window == nullptr)
    {
        Utils::errorMessage("ENGINE::CORE::WINDOW", "Window failed to be created");
        exit(-1);
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Utils::errorMessage("ENGINE::CORE::GLAD", "Failed to initialize GLAD");
        exit(-1);
    }

    is_running = true;
}

void Window::update()
{
    glfwPollEvents();
    is_running = !glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::getHandle() {
    return m_window;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}