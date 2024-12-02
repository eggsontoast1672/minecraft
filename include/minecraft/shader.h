#ifndef MINECRAFT_SHADER_H
#define MINECRAFT_SHADER_H

#include <glad/glad.h>

typedef GLuint shader_t;
typedef GLuint program_t;

shader_t shader_load(const char *path, GLenum kind);
program_t shader_program_create(const char *vertex_path,
                                const char *fragment_path);

#endif
