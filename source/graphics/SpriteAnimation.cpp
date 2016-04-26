#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(float updateFreq)
    : m_updateFreq(updateFreq)
{
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::push(SpriteRegion *spriteRegion)
{
    this->m_frameQueue.push_back(spriteRegion);
    this->m_currentFrame = 0;
}

void SpriteAnimation::update(float delta)
{
    static float counter = 0.0f;
    counter += delta;

    if (counter >= this->m_updateFreq)
    {
        ++this->m_currentFrame;
        if (this->m_currentFrame == this->m_frameQueue.size()) {
            this->m_currentFrame = 0;
        }
        counter = 0.0f;
    }
}

SpriteRegion *SpriteAnimation::getCurrentSpriteRegion()
{
    return this->m_frameQueue[this->m_currentFrame];
}
