#pragma once

#include <glm/common.hpp>
#include "window.h"

class Renderer
{
public:
    explicit Renderer(Window* target);
    void render();
private:

    void pre_frame();
    void m_render();
    void post_frame();
    void finish_frame();
    void clear();
    // pointer to window
    Window* m_target = nullptr;
    // std::queue<RenderCommand> m_queue;
    
};