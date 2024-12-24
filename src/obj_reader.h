// reader.h
#ifndef READER_H
#define READER_H

#include "array.h"
#include "triangle.h" // Add this for face_t
#include "vector.h"   // Add this for vec3_t
#include <stdio.h>

typedef struct {
  vec4_t *vertices;
  face_t *faces;
} model_t;

model_t load_obj(const char *path);
face_t parse_face(char *line);

#endif
