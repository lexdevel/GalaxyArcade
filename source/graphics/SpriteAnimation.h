#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include "SpriteRegion.h"
#include <vector>

enum PlaybackMode
{
    ONCE,
    LOOP
};

enum AnimationState
{
    PLAYING,
    STOPPED
};

class SpriteAnimation
{
private:
    std::vector<SpriteRegion *>     m_frameQueue;
    float                           m_updateFreq;
    float                           m_updateCounter;
    unsigned int                    m_currentFrame;
    PlaybackMode                    m_playbackMode;
    AnimationState                  m_animationState;
public:
    explicit SpriteAnimation(float updateFreq, const PlaybackMode &playbackMode = PlaybackMode::LOOP);
    ~SpriteAnimation();

    void push(SpriteRegion *spriteRegion);

    void setAnimationState(const AnimationState &animationState);
    void update(float delta);

    SpriteRegion *getCurrentSpriteRegion();
    inline const AnimationState &animationState() { return this->m_animationState; }

    inline Transformation &transformation() { return this->m_frameQueue[0]->transformation(); }
    void setTransformation(const Transformation &transformation) {
        // ToDo: Fix, only one transformation for all animation frames
        for (auto &it : this->m_frameQueue) {
            it->transformation() = transformation;
        }
    }
};

#endif // SPRITEANIMATION_H
