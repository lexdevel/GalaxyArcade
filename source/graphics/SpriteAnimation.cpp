#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(float updateFreq, const PlaybackMode &playbackMode)
    : m_updateFreq(updateFreq), m_playbackMode(playbackMode)
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

void SpriteAnimation::setAnimationState(const AnimationState &animationState)
{
    this->m_animationState = animationState;
    if (this->m_animationState == AnimationState::STOPPED) {
        this->m_currentFrame = 0;
    }
}

void SpriteAnimation::update(float delta)
{
    static float counter = 0.0f;

    if (this->m_animationState == AnimationState::PLAYING)
    {
        counter += delta;

        if (counter >= this->m_updateFreq)
        {
            ++this->m_currentFrame;
            if (this->m_currentFrame == this->m_frameQueue.size()) {
                this->m_currentFrame = 0;
                if (this->m_playbackMode == PlaybackMode::ONCE) {
                    this->m_animationState = AnimationState::STOPPED;
                }
            }
            counter = 0.0f;
        }
    }
}

SpriteRegion *SpriteAnimation::getCurrentSpriteRegion()
{
    return this->m_frameQueue[this->m_currentFrame];
}
