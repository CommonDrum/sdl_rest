#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include <math.h>

#include "display.h"
#include "mesh.h"
#include "triangle.h"

bool is_running = false;


const int NO_OF_POINTS = 9 * 9 * 9;
vec3_t  matrix[NO_OF_POINTS];

camera_t camera = {
  {0,0,-5},
  {0,0,0},
  300.0
};


void init_matrix(){
  int current_index = 0;
  for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        vec3_t new_point = {x,y,z};
        matrix[current_index++] = new_point;
      }
    }
  }
}

vec2_t project_vec3(vec3_t v){
  vec2_t new_vector = {v.x * camera.fov / (v.z + camera.position.z), v.y * camera.fov / (v.z + camera.position.z)};
  return new_vector;
}

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



void draw_matrix(){
  int current_index = 0;
 for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        matrix[current_index] = vec3_rotate_z(matrix[current_index], 0.02);
        matrix[current_index] = vec3_rotate_x(matrix[current_index], 0.01);
        vec2_t projected_v = project_vec3(matrix[current_index++]);

        draw_pixel((projected_v.x + 128.0), (projected_v.y + 128.0), 0xFFFF0000);
      }
    }
  }
}


void render(void) {
  clear_framebuffer(0xFF000000);

  camera.position = (vec3_t){0,0, camera.position.z - 0.01};

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
