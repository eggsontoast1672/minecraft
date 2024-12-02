#ifndef MINECRAFT_FILESYSTEM_H
#define MINECRAFT_FILESYSTEM_H

#include <stdio.h>

char *filesystem_load_from_file(FILE *file);
char *filesystem_load_from_path(const char *path);

#endif
