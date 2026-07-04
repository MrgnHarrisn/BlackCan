#pragma once

#include <memory>
#include "window.h"

class Engine {
    public:
        Engine();
        void loop();
    private:
    std::unique_ptr<Window> m_window;
    // std::unique_ptr<Renderer> m_renderer;

    void init();
    void cleanup();
};