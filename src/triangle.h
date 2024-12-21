#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

typedef struct {
  int a;
  int b;
  int c;
} face_t;

typedef struct {
  vec2_t a;
  vec2_t c;
  vec2_t b;
  float depth;
} triangle_t;

#endif
