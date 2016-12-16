#include "GameTime.h"

std::chrono::time_point<std::chrono::high_resolution_clock>
        GameTime::s_initial = std::chrono::high_resolution_clock::now();

float GameTime::elapsed()
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>
            (std::chrono::high_resolution_clock::now() - GameTime::s_initial).count();
}
