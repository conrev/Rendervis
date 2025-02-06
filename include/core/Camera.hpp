#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace Rendervis {

    class Camera {
    public:
        Camera(const glm::vec3& position, float aspect, float near, float far, float fov);
        inline const glm::vec3& Position() const {
            return camera_position_;
        }

    public:
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        void Move(const glm::vec2& direction, float dt, float sensitivity = 1.0f);
        void Rotate(const glm::vec3& pitch_yaw_roll, float dt, float sensitivity = 1.0f);

    private:
        const glm::vec3 world_up_ = glm::vec3(0.0, 1.0f, 0.0);
        glm::vec3 camera_position_{};
        glm::vec3 camera_forward_{};
        glm::vec3 camera_right_{};
        float near_dist_ = 0;
        float far_dist_ = 0;
        float aspect_ratio_ = 0;
        float fov_ = 0;
    };
}  // namespace Rendervis

#endif
