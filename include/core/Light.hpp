#ifndef LIGHT_H
#define LIGHT_H

#include <core/Transform.hpp>
#include <glm/glm.hpp>

namespace Rendervis {

    struct PointLight {
        Transform transform;
        glm::vec3 color;
        float intensity;
    };
}  // namespace Rendervis

#endif