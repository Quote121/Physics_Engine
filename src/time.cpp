#include "time.hpp"

Uint64 Time::NOW = SDL_GetPerformanceCounter();
Uint64 Time::LAST = 0;
double Time::deltaTime = 0;
const hdTimePoint Time::startTimePoint = std::chrono::high_resolution_clock::now();

std::string Time::GetTimeElapsedString(const hdTimePoint startPoint)
{
    const auto elapsed = std::chrono::high_resolution_clock::now() - startPoint;
    
    std::string mins_elapsed = std::to_string(std::chrono::duration_cast<std::chrono::minutes>(elapsed).count()%60);
    mins_elapsed.insert(0, 2-mins_elapsed.size(), '0');

    std::string sec_elapsed = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count()%60);
    sec_elapsed.insert(0, 2-sec_elapsed.size(), '0');
    std::string mss_elapsed = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count()%1000);
    mss_elapsed.insert(0, 3-mss_elapsed.size(), '0');

    return std::string(mins_elapsed + "m:" + sec_elapsed + "s:" + mss_elapsed + "ms");
}

void Time::UpdateFrameTime(void)
{
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    deltaTime = static_cast<double>((NOW-LAST)*1000 / static_cast<double>(SDL_GetPerformanceFrequency()));
}

