#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <chrono>

using hdTimePoint = std::chrono::high_resolution_clock::time_point;

class Time
{
private:
    static Uint64 NOW;
    static Uint64 LAST;
    static double deltaTime;
    static const hdTimePoint startTimePoint;

public:
    /// @brief Indicate the next frame has stated, update the clock
    static void UpdateFrameTime(void);

    /// @brief Get the frame time in ms
    static inline const double GetDeltaTime(void);

    /// @brief Get the number of frames per second
    static inline double GetFramesPerSecond(void);

    /// @brief Get string 
    /// @param startPoint Start time to determine elapsed time
    /// @return formatted string mm:ss:mss
    static std::string GetTimeElapsedString(const hdTimePoint startPoint);

    /// @brief Get a high definition of the current time point
    /// @return Return high definition time point
    static inline hdTimePoint GetTimePointNow(void);

};

inline hdTimePoint Time::GetTimePointNow(void)
{
    return std::chrono::high_resolution_clock::now();
}

inline const double Time::GetDeltaTime(void)
{
    return deltaTime;
}

inline double Time::GetFramesPerSecond(void)
{
    return (1/Time::GetDeltaTime())*1000;
}
