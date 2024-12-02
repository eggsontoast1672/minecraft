#include "minecraft/shader.h"

#include <stdlib.h>

#include "minecraft/filesystem.h"

shader_t shader_load(const char *path, GLenum kind) {
  char *source;
  shader_t shader;

  if ((source = filesystem_load_from_path(path)) == NULL) {
    fprintf(stderr, "Failed to load shader source\n");
    return 0;
  }
  shader = glCreateShader(kind);
  glShaderSource(shader, 1, (const GLchar *const *)&source, NULL);
  glCompileShader(shader);
  /* TODO: Check for errors */
  free(source);
  return shader;
}

program_t shader_program_create(const char *vertex_path,
                                const char *fragment_path) {
  shader_t vertex_shader, fragment_shader;
  program_t program;

  if ((vertex_shader = shader_load(vertex_path, GL_VERTEX_SHADER)) == 0) {
    fprintf(stderr, "Failed to load vertex shader\n");
    return 0;
  }
  if ((fragment_shader = shader_load(fragment_path, GL_FRAGMENT_SHADER)) == 0) {
    fprintf(stderr, "Failed to load fragment shader\n");
    glDeleteShader(vertex_shader);
    return 0;
  }
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  /* TODO: Check for link errors */
  glDetachShader(program, fragment_shader);
  glDetachShader(program, vertex_shader);
  glDeleteShader(fragment_shader);
  glDeleteShader(vertex_shader);
  return program;
}
