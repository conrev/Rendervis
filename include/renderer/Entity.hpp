#ifndef ENTITY_H
#define ENTITY_H

#include <glad/glad.h>

#include <memory>
#include <vector>

#include "core/Transform.hpp"
#include "renderer/Material.hpp"
#include "renderer/Mesh.hpp"
#include "renderer/Shader.hpp"

namespace Rendervis {

    // Todo, pass this along the vertex data
    struct VertexLayout {};

    class Entity {
    public:
        Entity();
        Entity(const std::string &model_path, const std::string &material_search_path, Transform transform);
        ~Entity() = default;

    public:
        void Draw();

    public:
        Transform transform_{};
        Material material_{};

    private:
        std::vector<Mesh> meshes_{};
    };
}  // namespace Rendervis

#endif
