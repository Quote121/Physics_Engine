#pragma once
#define TINYOBJLOADER_IMPLEMENTATION


#include <stdint.h>
#include <tiny_obj_loader/tiny_obj_loader.h>


#include "renderer/vertexBuffer.hpp"
#include "renderer/vertexBufferLayout.hpp"
#include "renderer/vertexArray.hpp"
#include "log.hpp"


class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    void LoadObject(const char* path, VertexArray* VAO);
};
