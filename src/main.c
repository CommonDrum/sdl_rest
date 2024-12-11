#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "display.h"
#include "vec2.h"

bool is_running = false;

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

int cross_product(vec2_t v0, vec2_t v1){
 return v0.x * v1.y - v0.y * v1.x;
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

      int cross1 = cross_product(v0v1, v0p);
      int cross2 = cross_product(v1v2, v1p);
      int cross3 = cross_product(v2v0, v2p);
      
      // Check if point is on the same side of all edges
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

  triangle_fill(v0, v1, v2, 0xFF00FF00);

  render_framebuffer();
}

int main(void) {
  is_running = create_window();

  while (is_running) {
    fix_framerate();
    process_input();
    render();
  }

  destroy_window();

  return EXIT_SUCCESS;
}
