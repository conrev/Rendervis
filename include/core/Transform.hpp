#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Rendervis {

    struct Transform {
        glm::vec3 position{glm::vec3(0.0f)};
        glm::quat rotation{glm::identity<glm::quat>()};
        glm::vec3 scale{glm::vec3(1.0f)};

        glm::mat4 GetTransformationMatrix() {
            glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), position);
            glm::mat4 rotation_matrix = glm::toMat4(rotation);
            glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), scale);
            return translation_matrix * rotation_matrix * scale_matrix;
        }
    };

}  // namespace Rendervis