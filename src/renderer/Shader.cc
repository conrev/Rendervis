#include "renderer/Shader.hpp"

#include <glad/glad.h>

#include <vector>

#include "util/FileOperations.hpp"

namespace Rendervis {

    Shader::Shader(const std::string& path_to_vertex, const std::string& path_to_fragment) {
        // shader compilation information variables
        int compilation_status, link_status;
        char info_log[512];

        // temporary source file holder
        const char* temp_src;

        // send source code to OpenGL
        std::string vertex_shader_source = Rendervis::Util::LoadFileToString(path_to_vertex);
        temp_src = vertex_shader_source.c_str();

        GLuint vertex_shader_id;
        vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertex_shader_id, 1, &temp_src, NULL);
        glCompileShader(vertex_shader_id);
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compilation_status);

        if (compilation_status == GL_FALSE) {
            glGetShaderInfoLog(vertex_shader_id, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << "\n";

            glDeleteShader(vertex_shader_id);
            return;
        }

        std::string fragment_shader_source = Rendervis::Util::LoadFileToString(path_to_fragment);
        temp_src = fragment_shader_source.c_str();

        GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader_id, 1, &temp_src, NULL);
        glCompileShader(fragment_shader_id);

        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &compilation_status);

        if (compilation_status == GL_FALSE) {
            glGetShaderInfoLog(fragment_shader_id, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << "\n";

            glDeleteShader(fragment_shader_id);
            return;
        }

        renderer_id_ = glCreateProgram();

        // attach individual shader to a full shader pipeline
        glAttachShader(renderer_id_, vertex_shader_id);
        glAttachShader(renderer_id_, fragment_shader_id);

        // link to OpenGL
        glLinkProgram(renderer_id_);

        glGetProgramiv(renderer_id_, GL_LINK_STATUS, &link_status);

        if (link_status == GL_FALSE) {
            glGetProgramInfoLog(renderer_id_, 512, NULL, info_log);
            std::cerr << "ERROR::SHADER::PROGRAM_LINKING_ERROR\n" << info_log << "\n";
        }
        // delete individual shader
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
    }

    Shader::~Shader() {
        glDeleteProgram(renderer_id_);
    }

    void Shader::Bind() const {
        glUseProgram(renderer_id_);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    void Shader::SetUniformFloat(const std::string& uniform_name, float value) {
        GLint uniform_loc = glGetUniformLocation(renderer_id_, uniform_name.c_str());
        glUniform1f(uniform_loc, value);
    }

    void Shader::SetUniformInt(const std::string& uniform_name, int value) {
        GLint uniform_loc = glGetUniformLocation(renderer_id_, uniform_name.c_str());
        glUniform1i(uniform_loc, value);
    }

    void Shader::SetUniformMat4(const std::string& uniform_name, const glm::mat4& value) {
        GLint uniform_loc = glGetUniformLocation(renderer_id_, uniform_name.c_str());
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetUniformVec3(const std::string& uniform_name, const glm::vec3& value) {
        GLint uniform_loc = glGetUniformLocation(renderer_id_, uniform_name.c_str());
        glUniform3fv(uniform_loc, 1, glm::value_ptr(value));
    }

    void Shader::SetUniformVec4(const std::string& uniform_name, const glm::vec4& value) {
        GLint uniform_loc = glGetUniformLocation(renderer_id_, uniform_name.c_str());
        glUniform4fv(uniform_loc, 1, glm::value_ptr(value));
    }

}  // namespace Rendervis