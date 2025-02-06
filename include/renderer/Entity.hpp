#ifndef ENTITY_H
#define ENTITY_H

#include <glad/glad.h>

#include <memory>
#include <vector>

#include "renderer/Shader.hpp"

namespace Rendervis {

    // Todo, pass this along the vertex data
    struct VertexLayout {};

    class Entity {
    public:
        Entity(const std::string& file_path);

        // Copy the data for now
        Entity(std::vector<GLfloat> vertex_data, std::vector<GLint> index_data);

        ~Entity();

    public:
        void Draw(std::shared_ptr<Shader> render_shader);

    private:
        std::vector<float> vertex_data_;
        // OpenGL related data
        // future:
        // pointer to textures

    private:
        GLuint vao_id_{};
        GLuint vbo_id_{};
        GLuint ebo_id_{};
    };
}  // namespace Rendervis

#endif
