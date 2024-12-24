#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "array.h"
#include "display.h"
#include "obj_reader.h"
#include "triangle.h"
#include "vector.h"

#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a > _b ? _a : _b;                                                         \
  })

#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    _a < _b ? _a : _b;                                                         \
  })

bool is_running = false;

camera_t camera = {{0, 0, 0, 1}, {0.2, 0, 0, 1}, 600.0};

void draw_line(vec2_t *a, vec2_t *b) {
  int x0 = (int)a->x;
  int y0 = (int)a->y;
  int x1 = (int)b->x;
  int y1 = (int)b->y;

  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1; // Step direction for x
  int sy = (y0 < y1) ? 1 : -1; // Step direction for y

  int err = dx - dy; // Initial decision variable

  while (1) {
    draw_pixel(x0 + 128, y0 + 128,
               0xFFFF0000); // Draw pixel at current position

    if (x0 == x1 && y0 == y1)
      break; // Line is complete

    int e2 = 2 * err;

    if (e2 > -dy) { // Move in x-direction
      err -= dy;
      x0 += sx;
    }

    if (e2 < dx) { // Move in y-direction
      err += dx;
      y0 += sy;
    }
  }
}

vec2_t project(vec4_t point) {
  float z = point.z;
  if (fabs(z) < 0.001)
    z = 0.001;

  vec2_t projected_point = {.x = (camera.fov * point.x) / z,
                            .y = (camera.fov * point.y) / z};
  return projected_point;
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

bool backface_culling(vec4_t a, vec4_t b, vec4_t c) {
  vec4_t ab = vec4_sub(c, a);
  vec4_t ac = vec4_sub(b, a);
  vec4_t normal = vec4_cross(ab, ac);
  vec4_t camera_ray = vec4_sub(camera.position, a);
  float dot_product = vec4_dot(camera_ray, normal);

  if (dot_product > 0) {
    return true;
  } else {
    return false;
  }
}

void process_all_faces(triangle_t **triangles_to_render, model_t *model) {

  vec4_t *mesh_vertices = model->vertices;
  face_t *mesh_faces = model->faces;
  int N_MESH_FACES = array_length(model->faces);

  for (int i = 0; i < N_MESH_FACES; i++) {
    vec4_t a = mesh_vertices[mesh_faces[i].a - 1];
    vec4_t b = mesh_vertices[mesh_faces[i].b - 1];
    vec4_t c = mesh_vertices[mesh_faces[i].c - 1];

    a.z -= camera.position.z + 10;
    b.z -= camera.position.z + 10;
    c.z -= camera.position.z + 10;

    if (backface_culling(a, b, c)) {
      continue;
    }

    triangle_t processed_triangle = {project(a), project(b), project(c),
                                     (a.z + b.z + c.z) / 3};

    array_push(*triangles_to_render, processed_triangle);
  }
}

void sort_triangles(triangle_t *array, int array_len) {
  if (array == NULL || array_len <= 0)
    return;

  bool sorted = false;

  while (!sorted) {
    sorted = true; // Assume sorted unless a swap occurs
    for (int i = 0; i < array_len - 1; i++) {
      if (array[i].depth > array[i + 1].depth) {
        triangle_t temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
        sorted = false; // A swap occurred, so it’s not sorted
      }
    }
  }
}

void triangle_fill(triangle_t triangle, uint32_t color) {
  int x_min = fmin(fmin(triangle.a.x, triangle.b.x), triangle.c.x);
  int y_min = fmin(fmin(triangle.a.y, triangle.b.y), triangle.c.y);
  int x_max = fmax(fmax(triangle.a.x, triangle.b.x), triangle.c.x);
  int y_max = fmax(fmax(triangle.a.y, triangle.b.y), triangle.c.y);

  for (int y = y_min; y <= y_max; y++) {
    for (int x = x_min; x <= x_max; x++) {
      vec2_t p = {x, y};

      vec2_t v0p = {p.x - triangle.a.x, p.y - triangle.a.y};
      vec2_t v1p = {p.x - triangle.b.x, p.y - triangle.b.y};
      vec2_t v2p = {p.x - triangle.c.x, p.y - triangle.c.y};

      vec2_t v0v1 = {triangle.b.x - triangle.a.x, triangle.b.y - triangle.a.y};
      vec2_t v1v2 = {triangle.c.x - triangle.b.x, triangle.c.y - triangle.b.y};
      vec2_t v2v0 = {triangle.a.x - triangle.c.x, triangle.a.y - triangle.c.y};

      int cross1 = vec2_cross(v0v1, v0p);
      int cross2 = vec2_cross(v1v2, v1p);
      int cross3 = vec2_cross(v2v0, v2p);

      // Check if all cross products have the same sign
      bool all_positive = (cross1 >= 0 && cross2 >= 0 && cross3 >= 0);
      bool all_negative = (cross1 <= 0 && cross2 <= 0 && cross3 <= 0);

      if (all_positive || all_negative) {
        draw_pixel(x + 128, y + 128, color);
      }
    }
  }
}

void draw_all_faces() {
  model_t model = load_obj("cube.obj");
  int N_MESH_FACES = array_length(model.faces);

  triangle_t *triangles_to_render = NULL;
  process_all_faces(&triangles_to_render, &model);
  sort_triangles(triangles_to_render, array_length(triangles_to_render));

  for (int i = 0; i < array_length(triangles_to_render); i++) {
    triangle_t triangle = triangles_to_render[i];
    triangle_fill(triangle, 0xFFFFFF00);
    draw_line(&triangle.a, &triangle.b);
    draw_line(&triangle.b, &triangle.c);
    draw_line(&triangle.c, &triangle.a);
  }
}

void render(void) {
  clear_framebuffer(0xFF000000);
  camera.rotation.x += 0.01;
  draw_all_faces();
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
