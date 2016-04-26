#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "SpriteRegion.h"
#include <vector>

class SpriteAnimation
{
private:
    std::vector<SpriteRegion *>     m_frameQueue;
    unsigned int                    m_currentFrame;
    float                           m_updateFreq;
public:
    explicit SpriteAnimation(float updateFreq);
    ~SpriteAnimation();

    void push(SpriteRegion *spriteRegion);

    void update(float delta);

    SpriteRegion *getCurrentSpriteRegion();
};

#endif // SPRITEANIMATION_H
