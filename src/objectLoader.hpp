#pragma once
#define TINYOBJLOADER_IMPLEMENTATION


#include <stdint.h>
#include <tiny_obj_loader/tiny_obj_loader.h>


#include "renderer/vertexBuffer.hpp"
#include "renderer/vertexBufferLayout.hpp"
#include "renderer/vertexArray.hpp"
#include "log.hpp"

#include "objects/components.hpp"
#include "objects/gameObjects.hpp"

class MeshObject;

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    static void LoadMesh(const char* path, MeshObject* Mesh);
};
