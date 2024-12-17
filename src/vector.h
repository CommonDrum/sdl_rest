#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x;
    float y;
} vec2_t;

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

vec3_t vec3_rotate_x(vec3_t v, float angle);
vec3_t vec3_rotate_y(vec3_t v, float angle);
vec3_t vec3_rotate_z(vec3_t v, float angle);


float vec2_cross(vec2_t* a, vec2_t* b);
void vec2_normalize(vec2_t* v);

void vec3_add(vec3_t* v, float number);
void vec3_sub(vec3_t* v, float number);
void vec3_mul(vec3_t* v, float number);
void vec3_div(vec3_t* v, float number);

#endif
