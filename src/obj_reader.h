// reader.h
#ifndef READER_H
#define READER_H

#include "vector.h"  // Add this for vec3_t
#include "triangle.h"  // Add this for face_t
#include <stdio.h>
#include "array.h"

typedef struct {
    vec3_t* vertices;
    face_t* faces;
} model_t;

model_t load_obj(const char* path);
face_t parse_face(char* line);

#endif
