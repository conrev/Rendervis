
#include "core/Scene.hpp"

namespace Rendervis {

    void Scene::AddShader(std::shared_ptr<Shader> shader, const std::string& identifier, bool replace) {
        // if it already exist and we dont wanna replace, spit warning
        if (!replace && shader_library_.count(identifier)) {
            std::cerr << "WARNING::SHADER LIBRARY::IDENTIFIER EXIST::IGNORED" << std::endl;
            return;
        }

        shader_library_[identifier] = shader;
    }

    std::shared_ptr<Shader> Scene::GetShader(const std::string& identifier) const {
        if (!shader_library_.count(identifier)) {
            std::cerr << "ERROR::SHADER LIBRARY::IDENTIFIER DOES NOT EXIST" << std::endl;
            return nullptr;
        }

        return shader_library_.at(identifier);
    }

    std::shared_ptr<Entity> Scene::GetEntity(const std::string& identifier) const {
        if (!entities_.count(identifier)) {
            std::cerr << "ERROR::ENTITY LIBRARY::IDENTIFIER DOES NOT EXIST" << std::endl;
            return nullptr;
        }

        return entities_.at(identifier);
    }

    void Scene::AddEntity(std::shared_ptr<Entity> entity, const std::string& identifier) {
        if (entities_.count(identifier)) {
            std::cerr << "WARNING::ENTITY LIBRARY::IDENTIFIER EXIST::IGNORED" << std::endl;
            return;
        }

        entities_[identifier] = entity;
    }

    std::shared_ptr<Texture> Scene::GetTexture(const std::string& identifier) const {
        if (!texture_library_.count(identifier)) {
            std::cerr << "ERROR::TEXTURE LIBRARY::IDENTIFIER DOES NOT EXIST" << std::endl;
            return nullptr;
        }

        return texture_library_.at(identifier);
    }

    void Scene::AddTexture(std::shared_ptr<Texture> texture, const std::string& identifier) {
        if (texture_library_.count(identifier)) {
            std::cerr << "WARNING::TEXTURE LIBRARY::IDENTIFIER EXIST::IGNORED" << std::endl;
            return;
        }

        texture_library_[identifier] = texture;
    }

    void Scene::AddLight(std::shared_ptr<PointLight> light) {
        lights_.push_back(light);
    }

    std::shared_ptr<PointLight> Scene::GetLight(int index) const {
        if (index >= lights_.size()) {
            std::cerr << "ERROR::SCENE::GETLIGHT INDEX OUT OF BOUNDS" << std::endl;
            return nullptr;
        }
        return lights_[index];
    }

    void Scene::Draw() {
        // for (const auto& [_, shader] : shader_library_) {
        //     // give all shaders scene-wide uniform values, assume their name for now
        //     shader->Bind();
        //     shader->SetUniformMat4("viewMatrix", main_camera_->GetViewMatrix());
        //     shader->SetUniformMat4("projectionMatrix", main_camera_->GetProjectionMatrix());
        //     shader->SetUniformVec3("lightColor", lights_[0]->color);
        //     shader->SetUniformVec3("lightPosition", lights_[0]->transform.position);
        //     shader->SetUniformVec3("viewPosition", main_camera_->Position());
        // }

        // for (auto& mesh : test_model_->meshes_) {
        //     // std::cout << test_model_->shaders_to_use_ << std::endl;
        //     std::shared_ptr<Shader> entity_shader = shader_library_[test_model_->shaders_to_use_];
        //     entity_shader->Bind();
        //     entity_shader->SetUniformMat4("viewMatrix", main_camera_->GetViewMatrix());
        //     entity_shader->SetUniformMat4("projectionMatrix", main_camera_->GetProjectionMatrix());
        //     entity_shader->SetUniformVec3("lightColor", lights_[0]->color);
        //     entity_shader->SetUniformVec3("lightPosition", lights_[0]->transform.position);
        //     entity_shader->SetUniformVec3("viewPosition", main_camera_->Position());
        //     entity_shader->SetUniformMat4("transformMatrix", glm::mat4x4(1.0f));

        //     mesh.Draw();
        // }

        for (const auto& [_, entity] : entities_) {
            // set the shader uniform to entity-specific values
            std::shared_ptr<Shader> entity_shader = shader_library_["Default"];
            entity_shader->Bind();
            entity_shader->SetUniformMat4("viewMatrix", main_camera_->GetViewMatrix());
            entity_shader->SetUniformMat4("projectionMatrix", main_camera_->GetProjectionMatrix());
            entity_shader->SetUniformVec3("lightColor", lights_[0]->color);
            entity_shader->SetUniformVec3("lightPosition", lights_[0]->transform.position);

            entity_shader->SetUniformVec3("viewPosition", main_camera_->Position());
            entity_shader->SetUniformMat4("transformMatrix", entity->transform_.GetTransformationMatrix());

            for (size_t i = 0; i < entity->material_.textures.size(); i++) {
                std::shared_ptr<Texture> texture = texture_library_[entity->material_.textures[i].texture_name];
                entity_shader->SetUniformInt(entity->material_.textures[i].uniform_name, i);
                entity_shader->SetUniformFloat("material.shininess", entity->material_.shininess);
                // std::cout << entity->material_.textures[i].uniform_name << i << std::endl;
                glActiveTexture(GL_TEXTURE0 + i);
                texture->Bind();
            }
            entity->Draw();
        }
    }
}  // namespace Rendervis