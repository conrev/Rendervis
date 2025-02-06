#include "core/Camera.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Rendervis {
    Camera::Camera(const glm::vec3& position, float aspect, float near, float far, float fov)
        : camera_position_(position)
        , camera_forward_(glm::vec3(0.0, 0.0, -1.0f))
        , aspect_ratio_(aspect)
        , near_dist_(near)
        , far_dist_(far)
        , fov_(fov) {
        camera_right_ = glm::normalize(glm::cross(camera_forward_, world_up_));
    }
    glm::mat4 Camera::GetViewMatrix() const {
        /*rotation_matrix = glm::rotate(rotation_matrix, glm::radians(-yaw_), glm::vec3(0.0, 1.0f, 0.0));
        rotation_matrix = glm::rotate(rotation_matrix, glm::radians(-pitch_), glm::vec3(1.0, 0.0f, 0.0));
        rotation_matrix = glm::rotate(rotation_matrix, glm::radians(-roll_), glm::vec3(0.0, 0.0f, 1.0));*/

        // glm::mat4 rotation_matrix = glm::eulerAngleZYX(glm::radians(roll_), glm::radians(yaw_), glm::radians(pitch_));
        // glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), camera_position_);
        // glm::mat4 rotation_matrix = glm::eulerAngleYXZ(glm::radians(yaw_), glm::radians(pitch_), glm::radians(roll_));

        // return glm::inverse(translation_matrix * rotation_matrix);

        return glm::lookAt(camera_position_, camera_position_ + camera_forward_, world_up_);
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return glm::perspective(fov_, aspect_ratio_, near_dist_, far_dist_);
    }

    void Camera::Move(const glm::vec2& direction, float dt, float sensitivity) {
        camera_position_ += dt * sensitivity * (direction.x * camera_forward_ + direction.y * camera_right_);
    }

    void Camera::Rotate(const glm::vec3& pitch_yaw_roll, float dt, float sensitivity) {
        glm::vec3 rotation_offset = pitch_yaw_roll * dt * sensitivity;

        // roll_ += roll_ofset;

        // pitch_ = std::max(-89.0f, std::min(pitch_, 89.0f));

        // glm::mat4 view_matrix = GetViewMatrix();
        // camera_forward_ = glm::normalize(glm::vec3(view_matrix[2])) * glm::vec3(1, 1, -1);

        camera_forward_ = glm::normalize(
            glm::rotate(camera_forward_, glm::radians(rotation_offset.y), glm::normalize(glm::cross(camera_forward_, world_up_))));
        camera_forward_ = glm::normalize(glm::rotate(camera_forward_, glm::radians(rotation_offset.x), world_up_));

        camera_right_ = glm::normalize(glm::cross(camera_forward_, world_up_));
    }
};  // namespace Rendervis