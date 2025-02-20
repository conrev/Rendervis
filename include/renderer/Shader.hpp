#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace Rendervis {

    class Shader {
    public:
        Shader(const std::string& path_to_vertex, const std::string& path_to_fragment);
        ~Shader();
        Shader(Shader&& other) : renderer_id_{other.renderer_id_} {
            other.renderer_id_ = 0;
        }
        Shader& operator=(Shader&& other) {
            if (this == &other) return *this;

            if (renderer_id_) {
                glDeleteProgram(renderer_id_);
            }

            renderer_id_ = other.renderer_id_;
            other.renderer_id_ = 0;

            return *this;
        }

    public:
        void Bind() const;
        void Unbind() const;
        void SetUniformFloat(const std::string& uniform_name, float value);
        void SetUniformInt(const std::string& uniform_name, int value);
        void SetUniformMat4(const std::string& uniform_name, const glm::mat4& value);
        void SetUniformVec3(const std::string& uniform_name, const glm::vec3& value);
        void SetUniformVec4(const std::string& uniform_name, const glm::vec4& value);

    private:
        Shader(const Shader&);
        Shader& operator=(const Shader&);

        GLuint renderer_id_{};
    };

}  // namespace Rendervis

#endif
