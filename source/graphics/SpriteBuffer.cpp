#include "SpriteBuffer.h"
#include "../math/Vec2.h"

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

    std::vector<Vec2>       vertexBufferData = std::vector<Vec2>(4);
    std::vector<Vec2>       texelsBufferData = std::vector<Vec2>(4);
    std::vector<uint32_t>   elementArrayData = std::vector<uint32_t>(6);

    vertexBufferData[0] = Vec2(-1.0f,  1.0f);
    vertexBufferData[1] = Vec2( 1.0f,  1.0f);
    vertexBufferData[2] = Vec2( 1.0f, -1.0f);
    vertexBufferData[3] = Vec2(-1.0f, -1.0f);

    texelsBufferData[0] = Vec2(0.0f, 1.0f);
    texelsBufferData[1] = Vec2(1.0f, 1.0f);
    texelsBufferData[2] = Vec2(1.0f, 0.0f);
    texelsBufferData[3] = Vec2(0.0f, 0.0f);

    elementArrayData[0] = 0;
    elementArrayData[1] = 1;
    elementArrayData[2] = 2;
    elementArrayData[3] = 2;
    elementArrayData[4] = 3;
    elementArrayData[5] = 0;

    vertexBuffer->bufferData<Vec2>(vertexBufferData);
    texelsBuffer->bufferData<Vec2>(texelsBufferData);
    elementArray->bufferData<uint32_t>(elementArrayData);

    static SpriteBuffer spriteBuffer = SpriteBuffer(vertexBuffer, texelsBuffer, elementArray);
    return &spriteBuffer;
}
