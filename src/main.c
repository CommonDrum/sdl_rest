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
  {0,0,-8},
  {0.2,0,0},
  650.0
};


void draw_line(vec2_t* a, vec2_t* b) {
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
        draw_pixel(x0 + 128, y0 + 128, 0xFFFF0000); // Draw pixel at current position

        if (x0 == x1 && y0 == y1) break; // Line is complete

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

vec2_t project(vec3_t point) {
   float z = point.z;
    if (fabs(z) < 0.001) z = 0.001;
    
    vec2_t projected_point = {
        .x = (camera.fov * point.x) / z,
        .y = (camera.fov * point.y) / z
    };
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



void draw_matrix(){
  int current_index = 0;
 for (float x = -1; x <= 1; x += 0.25) {
    for (float y = -1; y <= 1; y += 0.25) {
      for (float z = -1; z <= 1; z += 0.25) {
        matrix[current_index] = vec3_rotate_z(matrix[current_index], 0.02);
        matrix[current_index] = vec3_rotate_x(matrix[current_index], 0.01);
        vec2_t projected_v = project(matrix[current_index++]);

        draw_pixel((projected_v.x + 128.0), (projected_v.y + 128.0), 0xFFFF0000);
      }
    }
  }
}

void process_all_faces(triangle_t * triangles_to_render){

  for (int i = 0; i < N_MESH_FACES; i++){
    vec3_t a =  mesh_vertices[mesh_faces[i].a -1];
    vec3_t b =  mesh_vertices[mesh_faces[i].b -1];
    vec3_t c =  mesh_vertices[mesh_faces[i].c -1];

    a = vec3_rotate_x(a, camera.rotation.x);
    b = vec3_rotate_x(b, camera.rotation.x);
    c = vec3_rotate_x(c, camera.rotation.x);


    a = vec3_rotate_z(a, camera.rotation.x);
    b = vec3_rotate_z(b, camera.rotation.x);
    c = vec3_rotate_z(c, camera.rotation.x);

    a.z += camera.position.z;
    b.z += camera.position.z;
    c.z += camera.position.z;


    triangles_to_render[i] = (triangle_t){
      project(a),
      project(b),
      project(c)
    };
  }
}


void draw_all_faces(){
  triangle_t triangles_to_render[N_MESH_FACES];
  process_all_faces(triangles_to_render);
  for (int i = 0; i < N_MESH_FACES; i++){
    triangle_t triangle = triangles_to_render[i];
    draw_line(&triangle.a, &triangle.b);
    draw_line(&triangle.b, &triangle.c);
  }
}


void render(void) {
  clear_framebuffer(0xFF000000);
  camera.rotation.x += 0.01;
  draw_all_faces();
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
