#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>

#include <iostream>
#include <memory>
#include <string>

#include "stb_image.h"

namespace Rendervis {

    class Texture {
    public:
        Texture(const std::string& path) {
            unsigned char* data = stbi_load(path.c_str(), &texture_width_, &texture_height_, &channel_size_, 0);

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

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width_, texture_height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        }

    public:
        void Bind() const {
            glBindTexture(GL_TEXTURE_2D, texture_id_);
        }

    private:
        int32_t texture_width_{};
        int32_t texture_height_{};
        int32_t channel_size_{};
        GLuint texture_id_{};
    };

}  // namespace Rendervis

#endif