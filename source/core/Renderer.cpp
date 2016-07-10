#include "Renderer.h"

Renderer::Renderer(const std::shared_ptr<ShaderProgram> &shaderProgram)
    : m_shaderProgram(shaderProgram)
{
}

Renderer::~Renderer()
{
}
