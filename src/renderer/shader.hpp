#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <string>
#include <filesystem>

// Simple struct for passing shader location info
struct ShaderPath
{
	std::string vertex;
	std::string fragment;
};

class Shader {
private:

	// Program ID (set when we create a shader instance)
	unsigned int ID = 0;

    void ShaderCompile(const char* vertex, const char* fragment);

public:

    /// @brief Constructor for shader which has both fragment and vertex in one file
    /// @param shaderPath Path of the shader
    Shader(std::filesystem::path shaderPath);

    /// @brief Constructor for shader
    /// @param vertexPath Path for the vertex shader
    /// @param fragmentPath Path for the fragment shader
    Shader(std::filesystem::path vertexPath, std::filesystem::path fragmentPath);

	// use/activate the shader
	inline void Use() const;

	// Utility functions and overrides

	inline void setBool(const std::string& name, bool value) const;
	inline void setBool(const char* name, bool value) const;

	inline void setInt(const std::string& name, int value) const;
	inline void setInt(const char* name, int value) const;

	inline void setFloat(const std::string& name, float value) const;
	inline void setFloat(const char* name, float value) const;

	inline void setVec2(const std::string& name, const glm::vec2& value) const;
	inline void setVec2(const std::string& name, float x, float y) const;
    inline void setVec2(const char* name, const glm::vec2& value) const;
	inline void setVec2(const char* name, float x, float y) const;

	inline void setVec3(const std::string& name, const glm::vec3& value) const;
	inline void setVec3(const std::string& name, float x, float y, float z) const;
	inline void setVec3(const char* name, const glm::vec3& value) const;
	inline void setVec3(const char* name, float x, float y, float z) const;

	inline void setVec4(const std::string& name, const glm::vec4& value) const;
	inline void setVec4(const std::string& name, float x, float y, float z, float w) const;
    inline void setVec4(const char* name, const glm::vec4& value) const;
	inline void setVec4(const char* name, float x, float y, float z, float w) const;

	inline void setMat2(const std::string& name, const glm::mat2& mat) const;
	inline void setMat2(const char* name, const glm::mat2& mat) const;

	inline void setMat3(const std::string& name, const glm::mat3& mat) const;
	inline void setMat3(const char* name, const glm::mat3& mat) const;

	inline void setMat4(const std::string& name, const glm::mat4& mat) const;
	inline void setMat4(const char* name, const glm::mat4& mat) const;
};

inline void Shader::Use() const
{
    glUseProgram(ID);
}

// Utility inline functions
inline void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
inline void Shader::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}
// ------------------------------------------------------------------------
inline void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
inline void Shader::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}
// ------------------------------------------------------------------------
inline void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
inline void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}
// ------------------------------------------------------------------------
inline void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
inline void Shader::setVec2(const char* name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
// ------------------------------------------------------------------------
inline void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
inline void Shader::setVec2(const char* name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y);
}
// ------------------------------------------------------------------------
inline void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
inline void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
inline void Shader::setVec3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
inline void Shader::setVec3(const char* name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}
// ------------------------------------------------------------------------
inline void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
inline void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
inline void Shader::setVec4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
inline void Shader::setVec4(const char* name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}
// ------------------------------------------------------------------------
inline void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void Shader::setMat2(const char* name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
inline void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void Shader::setMat3(const char* name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
inline void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
inline void Shader::setMat4(const char* name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &mat[0][0]);
}
