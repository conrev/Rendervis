#include "renderer/Entity.hpp"

namespace Rendervis {

    Entity::Entity(std::vector<GLfloat> vertex_data, std::vector<GLint> index_data, Transform transform)
        : transform_{transform}, vertex_data_(vertex_data) {
        glGenVertexArrays(1, &vao_id_);
        glGenBuffers(1, &vbo_id_);
        glGenBuffers(1, &ebo_id_);

        // bind the vertex array
        glBindVertexArray(vao_id_);
        // The array buffer is now bounded to our VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);

        // the VBO now has data, our vertices array
        glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

        // bind array element buffer to our EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);

        // put the data in
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(GLuint), index_data.data(), GL_STATIC_DRAW);

        // tell opengl how to interpret our bounded array buffer, aka the VBO
        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // VAO attribute for UV
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Normals
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(8 * sizeof(float)));
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

    Entity::~Entity() {
        glDeleteVertexArrays(1, &vao_id_);
        glDeleteBuffers(1, &vbo_id_);
        glDeleteBuffers(1, &ebo_id_);
    }

    Transform Entity::GetTransform() {
        // not great, is this being copied?
        return transform_;
    }

    void Entity::Draw(std::shared_ptr<Shader> render_shader) {
        render_shader->Bind();
        glBindVertexArray(vao_id_);

        render_shader->SetUniformMat4("transformMatrix", transform_.GetTransformationMatrix());
        glDrawElements(GL_TRIANGLES, sizeof(vertex_data_), GL_UNSIGNED_INT, 0);
    }

}  // namespace Rendervis