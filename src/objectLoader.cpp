#include "ObjectLoader.hpp"


ObjectLoader::ObjectLoader()
{
}

ObjectLoader::~ObjectLoader()
{
}

static void ObjectLoader::LoadMesh(const char* path, MeshObject* Mesh)
{
    // Load object from file
    // Parse object
    // Load into VAO

    tinyobj::ObjReaderConfig reader_config;
    tinyobj::ObjReader reader;


    if(!reader.ParseFromFile(path, reader_config))
    {
        if(!reader.Error().empty())
        {
            Log::Write("[ObjectLoader] ", "Failed to load object: ", path, " Error: ", reader.Error());
        }
        return;
    }

    if (!reader.Warning().empty()) {
        Log::Write("[ObjectLoader] ", "Warning: ", reader.Warning());
    }

    attrib_t attrib = reader.GetAttrib();

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    tinyobj::index_t expected_vert_data = shapes[s].mesh.indices[0];
    int vert_data = 0;
    if(expected_vert_data.vertex_index >= 0)
    {
        vert_data += 3;
    }
    if(expected_vert_data.normal_index >= 0)
    {
        vert_data += 3;
    }
    if(expected_vert_data.texcoord_index >= 0)
    {
        vert_data += 2;
    }

    VertexBufferLayout VBL;
    VBL.AddFloat(vert_data);
    vector<real_t> vert_elems;
    VertexBuffer VBO;
    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
    // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
            // access to vertex
            tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
            tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
            tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
            tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];
            vert_elems.push_back(vx);
            vert_elems.push_back(vy);
            vert_elems.push_back(vz);
            Mesh.m_vertices.push_back(vx);
            Mesh.m_vertices.push_back(vy);
            Mesh.m_vertices.push_back(vz);
            Mesh.m_indices.push_back(idx.vertex_index);
            // Check if `normal_index` is zero or positive. negative = no normal data
            if (idx.normal_index >= 0) {
                tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];
                vert_elems.push_back(nx);
                vert_elems.push_back(ny);
                vert_elems.push_back(nz);
                Mesh.m_normals.push_back(nx);
                Mesh.m_normals.push_back(ny);
                Mesh.m_normals.push_back(nz);
                Mesh.m_normalIndices.push_back(idx.normal_index);
            }

            // Check if `texcoord_index` is zero or positive. negative = no texcoord data
            if (idx.texcoord_index >= 0) {
                tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
                vert_elems.push_back(tx);
                vert_elems.push_back(ty);
                Mesh.m_textureCoords.push_back(tx);
                Mesh.m_textureCoords.push_back(ty);
                Mesh.m_textureIndices.push_back(idx.texcoord_index);
            }

            // Optional: vertex colors
            // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
            // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
            // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
            }
            index_offset += fv;

            // per-face material
            // shapes[s].mesh.material_ids[f];
        }

        VBO.SetData<real_t>(vert_elems.data(), vert_elems.size() * sizeof(real_t));
        Mesh.VAO->AddBuffer(&VBO, &VBL);

    }

    /*  Example VAO Usage
    VertexArray VAO;
    VertexBuffer VBO;
    VertexBufferLayout VBL;

    float verts[] =
    {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    VBL.AddFloat(3);
    VBO.SetData<float>(verts, sizeof(verts));
    VAO.AddBuffer(&VBO, &VBL);
 */

}
