#include "renderer/Entity.hpp"

namespace Rendervis {
    Entity::Entity(const std::string &model_path, const std::string &material_search_path, Transform transform)
        : transform_(transform) {
        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = material_search_path;

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(model_path, reader_config)) {
            if (!reader.Error().empty()) {
                std::cerr << "ERROR::TinyObjReader:: " << reader.Error() << "\n";
            }
        }

        if (!reader.Warning().empty()) {
            std::cerr << "WARNING::TinyObjReader:: " << reader.Warning() << "\n";
        }

        auto &attrib = reader.GetAttrib();
        auto &shapes = reader.GetShapes();
        auto &materials = reader.GetMaterials();

        for (const auto &shape : shapes) {
            std::vector<Vertex> vertex_data;
            vertex_data.resize(shape.mesh.indices.size());
            for (size_t i = 0; i < shape.mesh.indices.size(); ++i) {
                const tinyobj::index_t &idx = shape.mesh.indices[i];

                vertex_data[i].position = {attrib.vertices[3 * idx.vertex_index + 0], attrib.vertices[3 * idx.vertex_index + 1],
                                           attrib.vertices[3 * idx.vertex_index + 2]};

                vertex_data[i].normal = {attrib.normals[3 * idx.normal_index + 0], attrib.normals[3 * idx.normal_index + 1],
                                         attrib.normals[3 * idx.normal_index + 2]};

                vertex_data[i].uv = {attrib.texcoords[2 * idx.texcoord_index + 0], attrib.texcoords[2 * idx.texcoord_index + 1]};
            }
            meshes_.emplace_back(vertex_data);
        }
    }

    // Entity::Entity(std::vector<GLfloat> vertex_data, std::vector<GLint> index_data, Transform transform, Material material,
    //                const std::string &shader_to_use)
    //     : transform_{transform}, vertex_data_(vertex_data), shader_to_use_(shader_to_use), material_(material) {
    //     glGenVertexArrays(1, &vao_id_);
    //     glGenBuffers(1, &vbo_id_);
    //     glGenBuffers(1, &ebo_id_);

    //     // bind the vertex array
    //     glBindVertexArray(vao_id_);
    //     // The array buffer is now bounded to our VBO
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

    //     // the VBO now has data, our vertices array
    //     glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

    //     // bind array element buffer to our EBO
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);

    //     // put the data in
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(GLuint), index_data.data(), GL_STATIC_DRAW);

    //     // tell opengl how to interpret our bounded array buffer, aka the VBO
    //     // Position
    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
    //     glEnableVertexAttribArray(0);

    //     // Color
    //     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(3 * sizeof(float)));
    //     glEnableVertexAttribArray(1);

    //     // UV
    //     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(6 * sizeof(float)));
    //     glEnableVertexAttribArray(2);

    //     // Normals
    //     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(8 * sizeof(float)));
    //     glEnableVertexAttribArray(3);

    //     glBindBuffer(GL_ARRAY_BUFFER, 0);
    //     glBindVertexArray(0);
    //     glDisableVertexAttribArray(0);
    //     glDisableVertexAttribArray(1);
    //     glDisableVertexAttribArray(2);
    // }

    // Entity::~Entity() {
    //     glDeleteVertexArrays(1, &vao_id_);
    //     glDeleteBuffers(1, &vbo_id_);
    //     glDeleteBuffers(1, &ebo_id_);
    // }

    void Entity::Draw() {
        for (auto &mesh : meshes_) {
            mesh.Draw();
        }
    }

}  // namespace Rendervis