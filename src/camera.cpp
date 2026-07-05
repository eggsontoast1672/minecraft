#include <glm/geometric.hpp>
#include <minecraft/camera.hpp>

void Camera::move(float amount) {
  // Project the look direction into the xz-plane. This will ensure that
  // movement is not tied to the look direction.
  m_position += amount * compute_forward();
}

void Camera::strafe(float amount) {
  glm::vec3 forward = compute_forward();
  glm::vec3 up = {0.0f, 1.0f, 0.0f};
  glm::vec3 right = glm::cross(forward, up);

  m_position += amount * right;
}

glm::vec3 Camera::compute_forward() const {
  glm::vec3 forward = glm::vec3(m_direction.x, m_direction.y, 0.0f);
  return glm::normalize(forward);
}
