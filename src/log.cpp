#include "log.hpp"

const char* logPath = "./";
const char* logFileName = "log.txt";

// Static variable definitions
std::mutex Log::logMux;
std::ofstream Log::fileHandle;    


void Log::Open(void)
{
    if (fileHandle.is_open())
        throw std::runtime_error("File handle is already open.");

    // Create file
    std::filesystem::path path{logPath};
    path /= logFileName;

    std::cout << "Creating log file " << path << std::endl;
    
    // std::filesystem::create_directories(path.parent_path());
    // if (!std::filesystem::create_directories(path.parent_path()))
        // throw std::runtime_error("create_directories failed.");

    // Get handle
    fileHandle.open(path, std::ofstream::out);

}


void Log::Close(void)
{
    fileHandle.close();
}


void Log::Write(const char* message, size_t size)
{
    std::lock_guard<std::mutex> lock(logMux);
    fileHandle.write(message, size);
    fileHandle.flush();

    // Enabled through compilation script
#ifdef CONSOLE_LOG_OUTPUT
    // Lock guard so this is thread safe
    std::cout << message << std::flush;
#endif
}
