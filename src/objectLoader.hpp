#pragma once
#include <memory>
class MeshObject;

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    static void LoadMesh(const char* path, std::shared_ptr<MeshObject> mesh_out);
};
