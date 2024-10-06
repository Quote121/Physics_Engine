#pragma once

#include <thread>
#include <mutex>
#include <filesystem>
#include <fstream>
#include "screen.hpp"

#include <iostream>

using hdTimePoint = std::chrono::high_resolution_clock::time_point;

extern const char* logPath;
extern const char* logFileName;

class Log
{
private:
    static std::mutex logMux;

    static std::ofstream fileHandle;    

public:
    static const hdTimePoint startTimePoint;

    static void Open(void);
    static void Close(void);

    static void Write(const char* message, size_t size);
    template<typename... Args>
    static void Write(const std::string& system, Args&&... message);

    static std::string GetTimeElapsedString(hdTimePoint startPoint);

    static inline hdTimePoint GetTimePointNow(void);
};



template<typename T>
void logFormat(std::ostringstream& oss, T&& t)
{
    oss << std::forward<T>(t);
}


template<typename T, typename... Args>
void logFormat(std::ostringstream& oss, T&& t, Args&&... args)
{
    oss << std::forward<T>(t);
    logFormat(oss, std::forward<Args>(args)...);
}


template<typename... Args>
void Log::Write(const std::string& system, Args&&... message)
{
    std::lock_guard<std::mutex> lock(logMux);
    
    // If enabled add timestamp
    std::ostringstream logSS;
    
    logSS << system << ": Thread ID (" << std::this_thread::get_id() << ") " << " - ";

    logFormat(logSS, std::forward<Args>(message)...);
    logSS << std::endl;

    fileHandle.write(logSS.str().c_str(), logSS.str().size());
    fileHandle.flush();
}


inline hdTimePoint Log::GetTimePointNow(void)
{
    return std::chrono::high_resolution_clock::now();
}
