#include "Renderable.h"

Renderable::Renderable(const Transformation &transformation)
    : m_vertexBuffer(GraphicsFactory::createBuffer(GL_ARRAY_BUFFER, 0, nullptr)),
      m_elementArray(GraphicsFactory::createBuffer(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr)),
      m_transformation(transformation)
{
}

Renderable::~Renderable()
{
}
