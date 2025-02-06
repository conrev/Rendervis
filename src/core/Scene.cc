
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
        if (shader_library_.count(identifier)) {
            std::cerr << "WARNING::ENTITY LIBRARY::IDENTIFIER EXIST::IGNORED" << std::endl;
            return;
        }

        entities_[identifier] = entity;
    }

}  // namespace Rendervis