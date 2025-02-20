#include "renderer/Mesh.hpp"

#include "glm/gtx/string_cast.hpp"

namespace Rendervis {

    Mesh::Mesh(const std::vector<Vertex> &vertices) {
        glGenVertexArrays(1, &vao_id_);
        glGenBuffers(1, &vbo_id_);

        // bind the vertex array
        glBindVertexArray(vao_id_);
        // The array buffer is now bounded to our VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        // the VBO now has data, our vertices array
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        // tell opengl how to interpret our bounded array buffer, aka the VBO
        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

        // UV
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        // Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        // assign vertices to storage
        vertex_data_ = vertices;
    }

    void Mesh::Draw() {
        glBindVertexArray(vao_id_);

        glDrawArrays(GL_TRIANGLES, 0, vertex_data_.size());
        glBindVertexArray(0);
    }

    // Model::Model(const std::string &model_path, const std::string &material_search_path) : Model() {
    //     tinyobj::ObjReaderConfig reader_config;
    //     reader_config.mtl_search_path = material_search_path;

    //     tinyobj::ObjReader reader;

    //     if (!reader.ParseFromFile(model_path, reader_config)) {
    //         if (!reader.Error().empty()) {
    //             std::cerr << "ERROR::TinyObjReader:: " << reader.Error();
    //         }
    //     }

    //     if (!reader.Warning().empty()) {
    //         std::cerr << "WARNING::TinyObjReader:: " << reader.Warning();
    //     }

    //     auto &attrib = reader.GetAttrib();
    //     auto &shapes = reader.GetShapes();
    //     auto &materials = reader.GetMaterials();

    //     for (const auto &shape : shapes) {
    //         std::vector<Vertex> vertex_data;
    //         vertex_data.resize(shape.mesh.indices.size());
    //         for (size_t i = 0; i < shape.mesh.indices.size(); ++i) {
    //             const tinyobj::index_t &idx = shape.mesh.indices[i];

    //             vertex_data[i].position = {attrib.vertices[3 * idx.vertex_index + 0], attrib.vertices[3 * idx.vertex_index + 1],
    //                                        attrib.vertices[3 * idx.vertex_index + 2]};

    //             vertex_data[i].normal = {attrib.normals[3 * idx.normal_index + 0], attrib.normals[3 * idx.normal_index + 1],
    //                                      attrib.normals[3 * idx.normal_index + 2]};

    //             vertex_data[i].uv = {attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]};
    //         }
    //         meshes_.emplace_back(vertex_data);
    //     }
    // }

    // void Model::Draw() {
    //     for (auto &mesh : meshes_) {
    //         mesh.Draw();
    //     }
    // }
}  // namespace Rendervis