#pragma once

#include <glm/common.hpp>
#include <queue>
#include "window.h"
#include "shader.h"
#include "model.h"
#include "camera.h"

struct RenderCommand
{
    Shader *shader;
    Model *model;
    glm::mat4 transform; // where the model is in the world
};

class Renderer
{
public:
    // still not clear to me what exactly explicit does
    explicit Renderer(Window *target);
    void render(Camera &active_camera);
    void submit(Model *model, Shader *shader, glm::mat4 transform);

private:
    void pre_frame();
    void m_render(Camera &active_camera);
    void post_frame();
    void submit_frame();
    void clear();
    // pointer to window
    Window *m_target = nullptr;

    // could sort these by shader
    std::queue<RenderCommand> m_queue;
};