#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "core/Camera.hpp"
#include "core/Light.hpp"
#include "renderer/Entity.hpp"
#include "renderer/Material.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Shader.hpp"

namespace Rendervis {
    class Scene {
        // Represents a scene
        // Simply a data holder for now.

    public:
        Scene() = default;
        // Scene(std::shared_ptr<Camera> main_camera) : main_camera_(main_camera) {}
        std::shared_ptr<Camera> MainCamera() const {
            return main_camera_;
        }

        void SetMainCamera(std::shared_ptr<Camera> camera) {
            main_camera_ = camera;
        }

    public:
        void AddShader(std::shared_ptr<Shader> shader, const std::string& identifier, bool replace = false);
        std::shared_ptr<Shader> GetShader(const std::string& identifier) const;
        void AddEntity(std::shared_ptr<Entity> entity, const std::string& identifier);
        std::shared_ptr<Entity> GetEntity(const std::string& identifier) const;
        void AddTexture(std::shared_ptr<Texture> texture, const std::string& identifier);
        std::shared_ptr<Texture> GetTexture(const std::string& identifier) const;
        void AddLight(std::shared_ptr<PointLight> light);
        std::shared_ptr<PointLight> GetLight(int index) const;
        void Draw();

    private:
        std::unordered_map<std::string, std::shared_ptr<Entity>> entities_;
        std::unordered_map<std::string, std::shared_ptr<Shader>> shader_library_;
        std::unordered_map<std::string, std::shared_ptr<Texture>> texture_library_;
        std::shared_ptr<Camera> main_camera_;
        std::vector<std::shared_ptr<PointLight>> lights_;
    };
}  // namespace Rendervis

#endif  // !SCENE_H
