#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vec2.h"

bool is_running = false;


const int NO_OF_POINTS = 9 * 9 * 9;
const float FOV = 64.0;
vec3_t  matrix[NO_OF_POINTS];

int current_index = 0;

void init_matrix(){
  for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        vec3_t new_point = {x,y,z};
        matrix[current_index++] = new_point;
      }
    }
  }
}


typedef struct{
  vec3_t position;
  vec3_t rotation;
  float fov;
} camera_t;

vec2_t vertices[4] = {
  { .x = 40, .y = 40 },
  { .x = 80, .y = 40 },
  { .x = 40, .y = 80 }
};

void process_input(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        is_running = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          is_running = false;
        break;
    }
  }
}

vec2_t project_vec3(vec3_t v){
  vec2_t new_vector = {v.x, v.y};
  return new_vector;
}

void draw_matrix(){
  int current_index = 0;
 for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        vec2_t projected_v = project_vec3(matrix[current_index]);
        draw_pixel((projected_v.x * FOV + 200.0), (projected_v.y * FOV + 200.0), 0xFFFF0000);
      }
    }
  }
}

void triangle_fill(vec2_t v0, vec2_t v1, vec2_t v2, uint32_t color) {
  // Finds the bounding box with all candidate pixels
  int x_min = fmin(fmin(v0.x, v1.x), v2.x);
  int y_min = fmin(fmin(v0.y, v1.y), v2.y);
  int x_max = fmax(fmax(v0.x, v1.x), v2.x);
  int y_max = fmax(fmax(v0.y, v1.y), v2.y);

  draw_pixel(v0.x, v0.y, 0xFFFF0000);
  draw_pixel(v1.x, v1.y, 0xFFFF0000);
  draw_pixel(v2.x, v2.y, 0xFFFF0000);

  // Loop all candidate pixels inside the bounding box
  for (int y = y_min; y <= y_max; y++) {
    for (int x = x_min; x <= x_max; x++) {
      vec2_t p  = {x,y};

      vec2_t v0p = {p.x - v0.x, p.y-v0.y};
      vec2_t v1p = {p.x - v1.x, p.y-v1.y};
      vec2_t v2p = {p.x - v2.x, p.y-v2.y};


      vec2_t v0v1= {v1.x - v0.x, v1.y-v0.y};
      vec2_t v1v2= {v2.x - v1.x, v2.y-v1.y};
      vec2_t v2v0= {v0.x - v2.x, v0.y-v2.y};

      float cross1 = vec2_cross(&v0v1, &v0p);
      float cross2 = vec2_cross(&v1v2, &v1p);
      float cross3 = vec2_cross(&v2v0, &v2p);
      
      if (cross1 >= 0 && cross2 >= 0 && cross3 >= 0) {
          draw_pixel(x, y, color);
      }
    }
  }
}

void render(void) {
  clear_framebuffer(0xFF000000);
 
  vec2_t v0 = vertices[0];
  vec2_t v1 = vertices[1];
  vec2_t v2 = vertices[2];

  draw_matrix();

  render_framebuffer();
}

int main(void) {

  init_matrix();
  is_running = create_window();

  while (is_running) {
    fix_framerate();
    process_input();
    render();
  }

  destroy_window();

  return EXIT_SUCCESS;
}
