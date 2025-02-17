#ifndef ENTITY_H
#define ENTITY_H

#include <glad/glad.h>

#include <memory>
#include <vector>

#include "core/Transform.hpp"
#include "renderer/Material.hpp"
#include "renderer/Shader.hpp"

namespace Rendervis {

    // Todo, pass this along the vertex data
    struct VertexLayout {};

    class Entity {
    public:
        Entity(const std::string& file_path);

        // Copy the data for now
        Entity(std::vector<GLfloat> vertex_data, std::vector<GLint> index_data, Transform transform, Material material,
               const std::string& shader_to_use = "Default");

        ~Entity();

    public:
        void Draw();

    public:
        Transform transform_{};
        std::string shader_to_use_{};
        Material material_{};

    private:
        GLuint vao_id_{};
        GLuint vbo_id_{};
        GLuint ebo_id_{};
        std::vector<float> vertex_data_{};
    };
}  // namespace Rendervis

#endif
