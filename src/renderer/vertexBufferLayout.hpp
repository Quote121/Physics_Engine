#pragma once

#include <vector>


class VertexBufferElement
{
public:
    unsigned int type;
    unsigned int count;
    unsigned char normalized; // Bool
    int layout;

    static unsigned int GetSizeOfType(const unsigned int type);
};


class VertexBufferLayout
{
private:
    unsigned int stride;

    // Elements such that vertices, normals and texcoords
    std::vector<VertexBufferElement> elementVector;

    /// @brief Push a layout element into a buffer
    /// @param type The OpenGL type
    /// @param count Number of types
    /// @param normalized If the type is normalized
    /// @param location Its desired layout location (-1 for default)
    void Push(unsigned int type, unsigned int count, unsigned char normalized, int location);

public:
    VertexBufferLayout();

    /// @brief Add float to the layout
    /// @param count number of floats i.e. position (x,y,z) = 3 floats
    /// @param location desired shader location
    void AddFloat(unsigned int count, int location = -1); 
    
    /// @brief Add unsigned int to the layout
    /// @param count number of unsigned int
    /// @param location desired shader location
    void AddUnsignedInt(unsigned int count, int location = -1); 
    
    /// @brief Add bytes to the layout
    /// @param count number of bytes
    /// @param location desired shader location
    void AddUnsignedByte(unsigned int count, int location = -1);

    /// @brief Get a the elements to read
    /// @return A const reference to the vector
    const std::vector<VertexBufferElement>& GetElements() const;

    /// @brief Get the stride number (bytes of all layout elements per vertex)
    /// @return stride
    unsigned int GetStride() const;
};

