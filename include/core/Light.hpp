#ifndef LIGHT_H
#define LIGHT_H

#include <core/Transform.hpp>
#include <glm/glm.hpp>

namespace Rendervis {

    struct PointLight {
        Transform transform;
        glm::vec3 color;
        float intensity;

        PointLight(Transform light_transform, glm::vec3 light_color = glm::vec3(1.0f), float light_intensity = 1.0f)
            : transform(light_transform), color(light_color), intensity(light_intensity) {}
    };
}  // namespace Rendervis

#endif