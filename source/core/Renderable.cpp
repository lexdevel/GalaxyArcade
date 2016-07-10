#include "Renderable.h"

Renderable::Renderable(const std::shared_ptr<VertexBuffer> &vertexBuffer,
                       const std::shared_ptr<ElementArray> &elementArray)
    : m_vertexBuffer(vertexBuffer),
      m_elementArray(elementArray)
{
}

Renderable::~Renderable()
{
}
