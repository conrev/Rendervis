#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <iostream>

#include "glm/glm.hpp"
#include "tiny_obj_loader.h"

namespace Rendervis {

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };
    class Mesh {
    public:
        Mesh(const std::vector<Vertex> &vertices);
        ~Mesh() {
            glDeleteVertexArrays(1, &vao_id_);
            glDeleteBuffers(1, &vbo_id_);
        }

        Mesh(Mesh &&other) : vao_id_{other.vao_id_}, vbo_id_{other.vbo_id_} {
            vertex_data_ = std::move(other.vertex_data_);
            other.vao_id_ = 0;
            other.vbo_id_ = 0;
            other.vertex_data_.clear();
        }
        Mesh &operator=(Mesh &&other) {
            if (this == &other) return *this;

            if (vbo_id_ || vao_id_ || !vertex_data_.empty()) {
                glDeleteVertexArrays(1, &vao_id_);
                glDeleteBuffers(1, &vbo_id_);
                vertex_data_.clear();
            }

            vao_id_ = std::move(other.vao_id_);
            vbo_id_ = std::move(other.vbo_id_);
            vertex_data_ = std::move(other.vertex_data_);

            return *this;
        }

    public:
        void Draw();

    private:
        Mesh(const Mesh &);             // no copy
        Mesh &operator=(const Mesh &);  // no copy assign
        GLuint vao_id_{};
        GLuint vbo_id_{};
        std::vector<Vertex> vertex_data_{};
    };

    // class Model {
    // public:
    //     Model() : shader_to_use_("Default") {};
    //     Model(const std::string &model_path, const std::string &material_search_path);
    //     void Draw();

    // private:
    //     std::vector<Mesh> meshes_{};
    //     std::string shader_to_use_{};
    // };

}  // namespace Rendervis

#endif