#pragma once

class IndexBuffer
{
private:
    unsigned int EBO = 0;
    unsigned int indexBufferCount;
public:
    IndexBuffer(void);
    ~IndexBuffer();

    /// @brief Calls the defualt constructor and will call SetData
    /// @param indices indices data to set
    /// @param count number of indices
    IndexBuffer(const unsigned int* indices, unsigned int count);

    /// @brief Set the data in the current index buffer
    /// @param indices Indices data buffer
    /// @param count Number of indices
    void SetData(const unsigned int* indices, unsigned int count);

    /// @brief 
    /// @param size 
    void CreateBuffer(const unsigned int size);

    /// @brief 
    /// @param data 
    /// @param offset 
    /// @param size_bytes 
    void UpdateBuffer(const void* data, const unsigned int offset, const unsigned int size_bytes);


    /// @brief 
    /// @param  
    /// @return 
    unsigned int GetCount(void) const;


    /// @brief 
    /// @param  
    void Bind(void) const;


    /// @brief 
    /// @param  
    void Unbind(void) const;

};
