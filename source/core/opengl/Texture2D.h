#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../GraphicsObject.h"

/**
 *
 */
class Texture2D : public GraphicsObject
{
private:
    explicit Texture2D(const GLuint &identifier);
public:
    virtual ~Texture2D();

    /**
     *
     */
    virtual void attach() override;

    /**
     *
     */
    virtual void detach() override;

    friend class GraphicsFactory;
};

#endif // TEXTURE2D_H
