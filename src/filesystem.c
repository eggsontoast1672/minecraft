#include "minecraft/filesystem.h"

#include <stdio.h>
#include <stdlib.h>

char *filesystem_load_from_file(FILE *file) {
  size_t buffer_size;
  char *buffer;

  fseek(file, 0, SEEK_END);
  buffer_size = ftell(file);
  rewind(file);
  if ((buffer = malloc(buffer_size)) == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return NULL;
  }
  if (fread(buffer, 1, buffer_size, file) < buffer_size) {
    fprintf(stderr, "Failed to read from file\n");
    free(buffer);
    return NULL;
  }
  return buffer;
}

char *filesystem_load_from_path(const char *path) {
  FILE *file;
  char *contents;

  if ((file = fopen(path, "r")) == NULL) {
    fprintf(stderr, "Failed to open file\n");
    return NULL;
  }
  contents = filesystem_load_from_file(file);
  fclose(file);
  return contents;
}
