#include <math.h>
#include "vec2.h"

vec2_t vec2_new(float x, float y){
  vec2_t result = {x, y};
  return result;
}


vec2_t vec2_add(vec2_t* a, vec2_t* b){
  vec2_t result = {
    .x = a->x + b->x,
    .y = a->y + b->y
  };
  return result;
}

vec2_t vec2_sub(vec2_t*a, vec2_t* b){
  vec2_t result = {
    .x = a->x - b->x,
    .y = a->y - b->y
  };
  return result;
}


float vec2_cross(vec2_t* a, vec2_t* b){
 return a->x * b->y - a->y * b->x;
}


