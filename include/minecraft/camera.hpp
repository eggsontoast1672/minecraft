#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

class Camera {
public:
  constexpr explicit Camera(glm::vec3 position)
      : m_position(position), m_direction(0.0f, 0.0f, 1.0f) {}

  [[nodiscard]] inline glm::mat4 get_matrix() const {
    constexpr glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f};
    return glm::lookAt(m_position, m_direction, up);
  }

  void move(float amount);
  void strafe(float amount);

private:
  glm::vec3 m_position;
  glm::vec3 m_direction;

  glm::vec3 compute_forward() const;
};
