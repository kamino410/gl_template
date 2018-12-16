#pragma once

#include <tiny_obj_loader.h>
#include <map>
#include <vector>

#include "gl_program_wrapper.hpp"

struct Object {
  tinyobj::attrib_t attr;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  GLuint vao;       // Vertex Array Object
  GLuint vaaos[2];  // Vertex Attribute Array Object
  GLuint eao;       // Element Array Object
};

class Scene {
  GLSLProgramWrapper* pro;
  Object obj;

 public:
  Scene();
  ~Scene();
  void setupProgram();
  void preProcess();
  void draw(GLFWwindow*);
  void keycallback(GLFWwindow* window, int key, int scancode, int action,
                   int mods);
  int getwidth();
  int getheight();
};
