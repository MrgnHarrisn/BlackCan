#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
    Window();

    void create_window();
    void update();
    GLFWwindow* getHandle();
    bool is_running = false;
    int m_width, m_height;

private:
    void onFramebufferResize(GLFWwindow* window, int width, int height);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    bool m_is_resizeable = false;
    GLFWwindow *m_window = nullptr;
    
};