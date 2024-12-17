#include <math.h>
#include "vector.h"

vec3_t vec3_rotate_x(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_y(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)
    };
    return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t v, float angle) {
    vec3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z
    };
    return rotated_vector;
}

float vec3_cross(vec2_t* a, vec2_t* b){
 return a->x * b->y - a->y * b->x;
}

void vec3_add(vec3_t* v, float number){
  v->x += number;
  v->y += number;
  v->z += number;
}
void vec3_sub(vec3_t* v, float number){
  v->x += number;
  v->y += number;
  v->z += number;
}
void vec3_mul(vec3_t* v, float number){
  v->x += number;
  v->y += number;
  v->z += number;
}
void vec3_div(vec3_t* v, float number){
  v->x += number;
  v->y += number;
  v->z += number;
}

