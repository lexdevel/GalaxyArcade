#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "GraphicsFactory.h"
#include "../math/Transformation.h"

class Renderable
{
private:
    std::unique_ptr<Buffer> m_vertexBuffer;
    std::unique_ptr<Buffer> m_elementArray;
    Transformation          m_transformation;
protected:
    Renderable(const Transformation &transformation);
    virtual ~Renderable() = 0;

public:
    inline Buffer *vertexBuffer() { return this->m_vertexBuffer.get(); }
    inline Buffer *elementArray() { return this->m_elementArray.get(); }

    inline const Transformation &transformation() const { return this->m_transformation; }
    inline Transformation &transformation() { return this->m_transformation; }
};

#endif // RENDERABLE_H
