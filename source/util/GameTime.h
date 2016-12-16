#ifndef GAMETIME_H
#define GAMETIME_H

#include <chrono>

/**
 * @breif The game time class.
 */
class GameTime
{
private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> s_initial;
public:

    /**
     * @brief Get the elapsed game time since game started.
     */
    static float elapsed();
};

#endif // GAMETIME_H
