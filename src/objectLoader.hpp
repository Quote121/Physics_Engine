#pragma once

class MeshObject;

class ObjectLoader
{
public:
    ObjectLoader();
    ~ObjectLoader();

    static void LoadMesh(const char* path, MeshObject* Mesh);
};
