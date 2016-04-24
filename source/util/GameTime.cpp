#include "GameTime.h"

std::chrono::time_point<HighResolutionClock> GameTime::s_timePoint = HighResolutionClock::now();

void GameTime::reset()
{
    GameTime::s_timePoint = HighResolutionClock::now();
}

float GameTime::elapsed()
{
    return std::chrono::duration_cast<DurationMillisecond>(HighResolutionClock::now() - GameTime::s_timePoint).count() / 1000.0f;
}
