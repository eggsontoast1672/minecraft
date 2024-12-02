#ifndef MINECRAFT_CAMERA_H
#define MINECRAFT_CAMERA_H

#include <cglm/struct.h>

typedef struct camera {
  vec3s position;
  vec3s direction;
} camera_t;

mat4s camera_get_matrix(camera_t camera);

#endif
