#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "core/PlatformEntity.h"
#include "../core/Bitmap.h"

enum TextureFilter : GLint {
    Linear          = GL_LINEAR,
    Nearest         = GL_NEAREST
};

enum TextureWrap : GLint {
    Repeat                  = GL_REPEAT,
    MirroredRepeat          = GL_MIRRORED_REPEAT,
    ClampToEdge             = GL_CLAMP_TO_EDGE,
    ClampToBorder           = GL_CLAMP_TO_BORDER
};

/**
 * @brief The 2D texture class.
 */
class Texture2D : public PlatformEntity
{
public:
    explicit Texture2D(const TextureFilter &filter = TextureFilter::Nearest,
                       const TextureWrap &wrap = TextureWrap::ClampToEdge);
    virtual ~Texture2D();

    void texImage2D(const Bitmap &bitmap);

    virtual void attach() override;
    virtual void detach() override;
};

#endif // TEXTURE2D_H
