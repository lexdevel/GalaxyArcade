#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../platform/VertexBuffer.h"
#include "../platform/ElementArray.h"

/**
 * @brief The renderable interface.
 */
class Renderable
{
protected:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<ElementArray> m_elementArray;
public:

    /**
     * Constructor.
     * @param vertexBuffer The vertex buffer
     * @param elementArray The element array
     */
    explicit Renderable(const std::shared_ptr<VertexBuffer> &vertexBuffer,
                        const std::shared_ptr<ElementArray> &elementArray);
    virtual ~Renderable() = 0;

    inline VertexBuffer *vertexBuffer() { return this->m_vertexBuffer.get(); }
    inline ElementArray *elementArray() { return this->m_elementArray.get(); }
};

#endif // RENDERABLE_H
