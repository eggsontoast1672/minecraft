#include "minecraft/camera.h"

mat4s camera_get_matrix(camera_t camera) {
  vec3s up = {{0.0f, 1.0f, 0.0f}};

  return glms_look(camera.position, camera.direction, up);
}
