#pragma once

class VertexBuffer
{
private:
    unsigned int VBO = 0;
public:
    VertexBuffer(void);
    ~VertexBuffer();

    /// @brief Set the data
    /// @tparam T type of data
    /// @param data pointer to data buffer
    /// @param count number of elements in the data
    template<typename T>
    void SetData(const void* data, const unsigned int count);

    /// @brief Reserve size in buffer based on type and count
    /// @tparam T type of data
    /// @param count number of elements
    template<typename T>
    void CreateBuffer(const unsigned int count);

    /// @brief Reserver a number of bytes in the buffer
    /// @param bytes Number of bytes to reserve
    void VertexBuffer::CreateBuffer(const unsigned int bytes);

    /// @brief Update the current VBO with the updated data
    /// @param data data to replace
    /// @param offset offset from the beginning in bytes 
    /// @param sizeBytes number of bytes to update (size of data)
    void UpdateBuffer(const void* data, const unsigned int offset, const unsigned int sizeBytes);

    /// @brief Bind the vertex buffer to the current vertex array object
    void Bind(void) const;

    /// @brief Unbind the vertex buffer (set to 0)
    void Unbind(void) const;
};


// Templates
template<typename T>
void VertexBuffer::SetData(const void* data, const unsigned int count)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), data, GL_STATIC_DRAW);
}


// Create buffer of size with no data
template<typename T>
void VertexBuffer::CreateBuffer(const unsigned int count)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(T), nullptr, GL_STATIC_DRAW);
}
