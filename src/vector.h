#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x, y;
} vec2_t;

typedef struct {
  float x, y, z;
} vec3_t;

typedef struct {
  float x, y, z, w;
} vec4_t;

////////////////////////////////////////////////////////////////////////////////
// Vector 2D functions
////////////////////////////////////////////////////////////////////////////////
float vec2_length(vec2_t v);
int vec2_cross(vec2_t v0, vec2_t v1);
vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_mul(vec2_t v, float factor);
vec2_t vec2_div(vec2_t v, float factor);

////////////////////////////////////////////////////////////////////////////////
// Vector 3D functions
////////////////////////////////////////////////////////////////////////////////
float vec3_length(vec3_t v);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec3_t vec3_mul(vec3_t v, float factor);
vec3_t vec3_div(vec3_t v, float factor);
vec3_t vec3_cross(vec3_t a, vec3_t b);
float vec3_dot(vec3_t a, vec3_t b);

vec3_t normalize(vec3_t v);

vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);

////////////////////////////////////////////////////////////////////////////////
// Vector 4D functions
////////////////////////////////////////////////////////////////////////////////

float vec4_length(vec4_t v);
vec4_t vec4_add(vec4_t a, vec4_t b);
vec4_t vec4_sub(vec4_t a, vec4_t b);
vec4_t vec4_mul(vec4_t v, float factor);
vec4_t vec4_div(vec4_t v, float factor);
vec4_t vec4_cross(vec4_t a, vec4_t b);
float vec4_dot(vec4_t a, vec4_t b);

#endif
