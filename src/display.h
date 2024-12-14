#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "vector.h"
#include <SDL.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

#define FPS 30
#define MILLISECS_PER_FRAME (1000 / FPS)

typedef struct{
  vec3_t position;
  vec3_t rotation;
  float fov;
} camera_t;

bool create_window(void);
void destroy_window(void);

void fix_framerate(void);

void clear_framebuffer(uint32_t color);
void render_framebuffer(void);

void draw_pixel(uint16_t x, uint16_t y, uint32_t color);

#endif
