#pragma once

#include <thread>
#include <mutex>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "screen.hpp"


extern const char* logPath;
extern const char* logFileName;

class Log
{
private:
    static std::mutex logMux;
    static std::ofstream fileHandle;    

public:
    
    /// @brief Open file
    static void Open(void);

    /// @brief Close file
    static void Close(void);

    /// @brief Write to file (thread safe)
    /// @param message Raw message
    /// @param size Size of char buffer
    static void WriteRaw(const char* message, size_t size);
    
    /// @brief Write to file (thread safe)
    /// @param system The system to report the error from e.g. ("Input System")
    /// @param ...message Comma seperated list of messages 
    template<typename... Args>
    static void Write(const std::string& system, Args&&... message);
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

    // Enabled through compilation script
#ifdef CONSOLE_LOG_OUTPUT
    // Lock guard so this is thread safe
    std::cout << logSS.str() << std::flush;
#endif
}
