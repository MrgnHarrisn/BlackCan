#pragma once

#include <memory>
#include "window.h"
#include "renderer.h"

class Engine
{
public:
    Engine();
    void loop();

private:
    void init();
    void cleanup();

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
};