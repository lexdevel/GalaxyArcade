#include "SpriteBuffer.h"

SpriteBuffer::SpriteBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer,
                           const std::shared_ptr<VertexBuffer> &texelsBuffer,
                           const std::shared_ptr<ElementArray> &elementArray)
    : m_vertexBuffer(vertexBuffer),
      m_texelsBuffer(texelsBuffer),
      m_elementArray(elementArray)
{
}

SpriteBuffer::~SpriteBuffer()
{
}

SpriteBuffer *SpriteBuffer::instance()
{
    static std::shared_ptr<VertexBuffer> vertexBuffer = std::shared_ptr<VertexBuffer>(new VertexBuffer());
    static std::shared_ptr<VertexBuffer> texelsBuffer = std::shared_ptr<VertexBuffer>(new VertexBuffer());
    static std::shared_ptr<ElementArray> elementArray = std::shared_ptr<ElementArray>(new ElementArray());

    std::vector<Vector2f> vertexBufferData = std::vector<Vector2f>(4);
    std::vector<Vector2f> texelsBufferData = std::vector<Vector2f>(4);
    std::vector<uint32_t> elementArrayData = std::vector<uint32_t>(6);

    vertexBufferData[0] = Vector2f(-1.0f,  1.0f);
    vertexBufferData[0] = Vector2f( 1.0f,  1.0f);
    vertexBufferData[0] = Vector2f( 1.0f, -1.0f);
    vertexBufferData[0] = Vector2f(-1.0f, -1.0f);

    texelsBufferData[0] = Vector2f(0.0f, 0.0f);
    texelsBufferData[0] = Vector2f(1.0f, 0.0f);
    texelsBufferData[0] = Vector2f(1.0f, 1.0f);
    texelsBufferData[0] = Vector2f(0.0f, 1.0f);

    elementArrayData[0] = 0;
    elementArrayData[0] = 1;
    elementArrayData[0] = 2;
    elementArrayData[0] = 2;
    elementArrayData[0] = 3;
    elementArrayData[0] = 0;

    vertexBuffer->bufferData<Vector2f>(vertexBufferData);
    texelsBuffer->bufferData<Vector2f>(texelsBufferData);
    elementArray->bufferData<uint32_t>(elementArrayData);

    static SpriteBuffer spriteBuffer = SpriteBuffer(vertexBuffer, texelsBuffer, elementArray);
    return static_cast<SpriteBuffer *>(&spriteBuffer);
}
