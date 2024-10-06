#include "shader.hpp"
#include <fstream>
#include "../log.hpp"
#include <string>
#include <cstring>

constexpr char prefix[] = "#type ";
constexpr char fragmentStr[] = "fragment";
constexpr char vertexStr[] = "vertex";


Shader::Shader(std::filesystem::path shaderPath)
{
    // Read shader in, split at pragmatic comment and pass it to main shader constructor
    // everything after #type vertex is vertex, everything after #type fragment is fragment shader

    std::stringstream vss;
    std::stringstream fss;

    std::ifstream shaderFile(shaderPath);

    if (!shaderFile.is_open())
        throw std::runtime_error("Shader file failed to open. Could be incorrect path.");

    std::string line;
    std::string currentShader = "";

    while (std::getline(shaderFile, line, '\n'))
    {
        if (std::strncmp(line.c_str(), prefix, sizeof(prefix)-1) == 0)
        {
            if ((line.size() > (sizeof(prefix) + sizeof(fragmentStr))) && (line.size() > (sizeof(prefix) + sizeof(vertexStr))))
                throw std::runtime_error("Malformed shader pragmatic statment");

            if (std::strncmp(line.c_str()+sizeof(prefix)-1, vertexStr, sizeof(vertexStr)-1) == 0)
                currentShader = vertexStr;

            if (std::strncmp(line.c_str()+sizeof(prefix)-1, fragmentStr, sizeof(fragmentStr)-1) == 0)
                currentShader = fragmentStr;
        }
        else if (currentShader != "")
        {
            if (currentShader == vertexStr)
                vss << line << '\n'; // Append the new line char back
            else if (currentShader == fragmentStr)
                fss << line << '\n';
            else
                throw std::runtime_error("Unknown shader type.");
        }
    }
    // Check both shaders have something loaded
    if (vss.str().size() == 0 && fss.str().size() == 0)
        throw std::runtime_error("Nothing written to shader. Could be incorrect path.");

    // Pass the underlying c string shaders to compile
    ShaderCompile(vss.str().c_str(), fss.str().c_str());
}


Shader::Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath)
{
    std::stringstream vss;
    std::stringstream fss;

    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    // Ensure ifstream objs can throw
    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexFile.open(vertexPath);
        vss << vertexFile.rdbuf();
        vertexFile.close();
    }
    catch(const std::ifstream::failure& e)
    {
        Log::Write("Shader", "Failed to read vertexshader: ", vertexPath, " Error: ", e.what(), " Code: ", e.code());
    }

    try
    {
        fragmentFile.open(fragmentPath);
        fss << fragmentFile.rdbuf();
        fragmentFile.close();
    }
    catch(const std::ifstream::failure& e)
    {
        Log::Write("Shader", "Failed to read fragmentshader: ", fragmentPath, " Error: ", e.what(), " Code: ", e.code());
    }
    
    // Pass underlying c strings to compile
    ShaderCompile(vss.str().c_str(), fss.str().c_str());
}

void Shader::ShaderCompile(const char* vertexCode, const char* fragmentCode)
{
    // Compile shaders
    unsigned int vertex,fragment;
    int success;
    char infoLog[512];

    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);

    // Handle errors
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, sizeof(infoLog), nullptr, infoLog);
        Log::Write("Shader", "Vertex compilation failed. InfoLog ouput: ", infoLog);
        throw std::runtime_error("Vertex shader compilation failed. Check logs.");
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);

    // Handle errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, sizeof(infoLog), nullptr, infoLog);
        Log::Write("Shader", "Fragment compilation failed. InfoLog output: ", infoLog);
        throw std::runtime_error("Fragment shader compilation failed. Check logs.");
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Handle linking errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, sizeof(infoLog), nullptr, infoLog);
        Log::Write("Shader", "Shader linking failed. InfoLog output: ", infoLog);
        throw std::runtime_error("Shader linking failed. Check logs.");
    }
    
    // Delete shaders since they are now linked
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
