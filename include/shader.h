#ifndef SHADER_H
#define SHADER_H

#include <stddef.h>

typedef struct {
    unsigned int index;
    const char *name;
} vertex_attr_t;

typedef struct {
    unsigned int vertex_handle, fragment_handle, shader_handle;
} shader_t;

shader_t shader_create(const char *vertex_path, const char *fragment_path, size_t n, vertex_attr_t attrs[]);
void shader_destroy(shader_t self);
void shader_bind(shader_t self);

#endif
