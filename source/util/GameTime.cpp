#include "GameTime.h"
#include <stdlib.h>
#include <time.h>

std::chrono::time_point<std::chrono::high_resolution_clock>
        GameTime::s_initial = std::chrono::high_resolution_clock::now();

void GameTime::randomizeTimer()
{
    ::srand(static_cast<unsigned int>(::time(nullptr)));
}

float GameTime::elapsed()
{
    return std::chrono::duration_cast<std::chrono::duration<float, std::milli>>
            (std::chrono::high_resolution_clock::now() - GameTime::s_initial).count();
}
