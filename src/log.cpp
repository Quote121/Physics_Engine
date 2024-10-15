#include "log.hpp"

const char* logPath = "./";
const char* logFileName = "log.txt";

// Static variable definitions
const hdTimePoint Log::startTimePoint = std::chrono::high_resolution_clock::now();
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
}


std::string Log::GetTimeElapsedString(const hdTimePoint startPoint)
{
    auto elapsed = std::chrono::high_resolution_clock::now() - startPoint;
    
    std::string mins_elapsed = std::to_string(std::chrono::duration_cast<std::chrono::minutes>(elapsed).count()%60);
    mins_elapsed.insert(0, 2-mins_elapsed.size(), '0');

    std::string sec_elapsed = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(elapsed).count()%60);
    sec_elapsed.insert(0, 2-sec_elapsed.size(), '0');

    std::string mss_elapsed = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count()%1000);
    mss_elapsed.insert(0, 3-mss_elapsed.size(), '0');

    return std::string(mins_elapsed + "m:" + sec_elapsed + "s:" + mss_elapsed + "ms");
}
