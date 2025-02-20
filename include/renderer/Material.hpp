#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>
#include <memory>
#include <string>

namespace Rendervis {
    struct TextureMapping {
        // maps texture identifier to a specific uniform
        std::string texture_name;
        std::string uniform_name;
    };
    class Texture {
    public:
        Texture(const std::string& path) {
            unsigned char* data = stbi_load(path.c_str(), &texture_width_, &texture_height_, &channel_size_, 0);

            GLenum texture_format;

            switch (channel_size_) {
                // single channel texture
                case 1:
                    texture_format = GL_RED;
                    break;
                // rgb texture
                case 3:
                    texture_format = GL_RGB;
                    break;
                // rgba texture (pngs)
                case 4:
                    texture_format = GL_RGBA;
                    break;
                default:
                    texture_format = GL_RGB;
            };

            if (!data) {
                std::cerr << " ERROR: Texture Data is Empty";
            }

            glGenTextures(1, &texture_id_);
            glBindTexture(GL_TEXTURE_2D, texture_id_);
            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, texture_format, texture_width_, texture_height_, 0, texture_format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        }
        ~Texture() {
            glDeleteTextures(1, &texture_id_);
        }

        Texture(Texture&& other)
            : texture_width_{other.texture_width_}
            , texture_height_{other.texture_height_}
            , channel_size_{other.channel_size_}
            , texture_id_{other.texture_id_} {
            other.texture_width_ = 0;
            other.texture_height_ = 0;
            other.channel_size_ = 0;
            other.texture_id_ = 0;
        }
        Texture& operator=(Texture&& other) {
            if (this == &other) return *this;
            texture_width_ = std::move(other.texture_width_);
            texture_height_ = std::move(other.texture_height_);
            texture_id_ = std::move(other.texture_id_);

            return *this;
        }

    public:
        void Bind() const {
            glBindTexture(GL_TEXTURE_2D, texture_id_);
        }

    private:
        Texture(const Texture&);
        Texture& operator=(const Texture&);

        int32_t texture_width_{};
        int32_t texture_height_{};
        int32_t channel_size_{};
        GLuint texture_id_{};
    };

    struct Material {
        std::string shader_name;               // identifiers of shader in the scene
        std::vector<TextureMapping> textures;  // identifier of textures in the scene
        float shininess = 32.0f;
        // what about other uniforms?
    };
}  // namespace Rendervis

#endif