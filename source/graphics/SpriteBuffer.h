#ifndef SPRITEBUFFER_H
#define SPRITEBUFFER_H

#include "../platform/VertexBuffer.h"
#include "../platform/ElementArray.h"

/**
 * @brief The sprite buffer class.
 */
class SpriteBuffer
{
private:
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<VertexBuffer> m_texelsBuffer;
    std::shared_ptr<ElementArray> m_elementArray;
private:
    explicit SpriteBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer,
                          const std::shared_ptr<VertexBuffer> &texelsBuffer,
                          const std::shared_ptr<ElementArray> &elementArray);
    ~SpriteBuffer();
public:

    /**
     * @brief Gets the single instance of the sprite buffer.
     */
    static SpriteBuffer *instance();

    inline const std::shared_ptr<VertexBuffer> &vertexBuffer() const { return this->m_vertexBuffer; }
    inline const std::shared_ptr<VertexBuffer> &texelsBuffer() const { return this->m_texelsBuffer; }
    inline const std::shared_ptr<ElementArray> &elementArray() const { return this->m_elementArray; }
};

#endif // SPRITEBUFFER_H
