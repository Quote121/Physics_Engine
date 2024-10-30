#pragma once
#include <memory>
class MeshObject;

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    static void LoadMesh(const char* path, MeshObject* mesh_out);
};
