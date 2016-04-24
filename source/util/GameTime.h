#ifndef GAMETIME_H
#define GAMETIME_H

#include <chrono>

typedef std::chrono::high_resolution_clock          HighResolutionClock;
typedef std::chrono::duration<float, std::milli>    DurationMillisecond;

class GameTime
{
private:
    static std::chrono::time_point<HighResolutionClock> s_timePoint;
public:

    static void reset();
    static float elapsed();
};

#endif // GAMETIME_H
