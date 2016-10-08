#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "core/PlatformEntity.h"
#include "../util/Bitmap.h"

enum TextureFilter : GLint {
    LINEAR          = GL_LINEAR,
    NEAREST         = GL_NEAREST
};

enum TextureWrap : GLint {
    REPEAT                  = GL_REPEAT,
    MIRROREDREPEAT          = GL_MIRRORED_REPEAT,
    CLAMPTOEDGE             = GL_CLAMP_TO_EDGE,
    CLAMPTOBORDER           = GL_CLAMP_TO_BORDER
};

/**
 * @brief The 2D texture class.
 */
class Texture2D : public PlatformEntity
{
public:
    explicit Texture2D(const TextureFilter &filter = TextureFilter::NEAREST,
                       const TextureWrap &wrap = TextureWrap::CLAMPTOEDGE);
    explicit Texture2D(const std::shared_ptr<Bitmap> &bitmap,
                       const TextureFilter &filter = TextureFilter::NEAREST,
                       const TextureWrap &wrap = TextureWrap::CLAMPTOEDGE);
    virtual ~Texture2D();

    void texImage2D(const std::shared_ptr<Bitmap> &bitmap);

    virtual void attach() override;
    virtual void detach() override;
};

#endif // TEXTURE2D_H
