#include "vector.h"
#include <math.h>

///////////////////////////////////////////////////////////////////////////////
// Implementations of Vector 2D functions
///////////////////////////////////////////////////////////////////////////////
float vec2_length(vec2_t v) { return sqrt(v.x * v.x + v.y * v.y); }

int vec2_cross(vec2_t v0, vec2_t v1) { return v0.x * v1.y - v0.y * v1.x; }

vec2_t vec2_add(vec2_t a, vec2_t b) {
  vec2_t result = {.x = a.x + b.x, .y = a.y + b.y};
  return result;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  vec2_t result = {.x = a.x - b.x, .y = a.y - b.y};
  return result;
}

vec2_t vec2_mul(vec2_t v, float factor) {
  vec2_t result = {.x = v.x * factor, .y = v.y * factor};
  return result;
}

vec2_t vec2_div(vec2_t v, float factor) {
  vec2_t result = {.x = v.x / factor, .y = v.y / factor};
  return result;
}

float vec2_dot(vec2_t a, vec2_t b) { return (a.x * b.x) + (a.y * b.y); }

///////////////////////////////////////////////////////////////////////////////
// Implementations of Vector 3D functions
///////////////////////////////////////////////////////////////////////////////
float vec3_length(vec3_t v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

vec3_t vec3_add(vec3_t a, vec3_t b) {
  vec3_t result = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
  return result;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
  vec3_t result = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
  return result;
}

vec3_t vec3_mul(vec3_t v, float factor) {
  vec3_t result = {.x = v.x * factor, .y = v.y * factor, .z = v.z * factor};
  return result;
}

vec3_t vec3_div(vec3_t v, float factor) {
  vec3_t result = {.x = v.x / factor, .y = v.y / factor, .z = v.z / factor};
  return result;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  vec3_t result = {.x = a.y * b.z - a.z * b.y,
                   .y = a.z * b.x - a.x * b.z,
                   .z = a.x * b.y - a.y * b.x};
  return result;
}

float vec3_dot(vec3_t a, vec3_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3_t vec3_rotate_x(vec3_t v, float angle) {
  vec3_t rotated_vector = {.x = v.x,
                           .y = v.y * cos(angle) - v.z * sin(angle),
                           .z = v.y * sin(angle) + v.z * cos(angle)};
  return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
  vec3_t rotated_vector = {.x = v.x * cos(angle) - v.z * sin(angle),
                           .y = v.y,
                           .z = v.x * sin(angle) + v.z * cos(angle)};
  return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
  vec3_t rotated_vector = {.x = v.x * cos(angle) - v.y * sin(angle),
                           .y = v.x * sin(angle) + v.y * cos(angle),
                           .z = v.z};
  return rotated_vector;
}

vec3_t normalize(vec3_t v) {
  float len = vec3_length(v);
  return vec3_div(v, len);
}

/////////////////
float vec4_length(vec4_t v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

vec4_t vec4_add(vec4_t a, vec4_t b) {
  vec4_t result = {.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
  return result;
}

vec4_t vec4_sub(vec4_t a, vec4_t b) {
  vec4_t result = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
  return result;
}

vec4_t vec4_mul(vec4_t v, float factor) {
  vec4_t result = {.x = v.x * factor, .y = v.y * factor, .z = v.z * factor};
  return result;
}

vec4_t vec4_div(vec4_t v, float factor) {
  vec4_t result = {.x = v.x / factor, .y = v.y / factor, .z = v.z / factor};
  return result;
}

vec4_t vec4_cross(vec4_t a, vec4_t b) {
  vec4_t result = {.x = a.y * b.z - a.z * b.y,
                   .y = a.z * b.x - a.x * b.z,
                   .z = a.x * b.y - a.y * b.x};
  return result;
}

float vec4_dot(vec4_t a, vec4_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
