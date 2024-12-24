#include "obj_reader.h"
#include "triangle.h"
#include "vector.h"

model_t load_obj(const char *path) {
  FILE *file = fopen(path, "r");
  model_t model = {NULL, NULL};

  if (!file) {
    perror("Error opening file");
    return model;
  }

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      vec4_t vertex = {0, 0, 0, 1};
      if (sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z) == 3) {
        array_push(model.vertices, vertex);
      }
    } else if (line[0] == 'f' && line[1] == ' ') {
      face_t face = parse_face(line);
      array_push(model.faces, face);
    }
  }

  fclose(file);
  return model;
}

face_t parse_face(char *line) {
  face_t face = {0, 0, 0};
  sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &face.a, &face.b, &face.c);
  return face;
}
