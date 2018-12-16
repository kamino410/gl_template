#include "scene.hpp"

#include <tiny_obj_loader.h>
#include <iostream>
#include <string>
#include <vector>

#define WIDTH 640
#define HEIGHT 480

Scene::Scene() {}

Scene::~Scene() { delete pro; }

int Scene::getheight() { return HEIGHT; }

int Scene::getwidth() { return WIDTH; }

void Scene::keycallback(GLFWwindow* window, int key, int scancode, int action,
                        int mods) {
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    if (key == GLFW_KEY_ESCAPE) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }
}

void Scene::setupProgram() {
  pro = new GLSLProgramWrapper();
  pro->compileShader("test.vert", GLSLShaderType::VERTEX);
  pro->compileShader("test.frag", GLSLShaderType::FRAGMENT);
  pro->link();
}

void Scene::preProcess() {
  // std::string err, warn;
  // bool res = tinyobj::LoadObj(&obj.attr, &obj.shapes, &obj.materials, &warn,
  //                            &err, "test.obj");
  // if (!res) {
  //  std::cerr << err << std::endl;
  //  exit(1);
  // }
  // v  (std::vector<float>) : obj.attr.vertices
  // vn (std::vector<float>) : obj.attr.normals
  // f  (std::vector<struct(vert_index, norms_index, texcoord_index)>) :
  //     obj.shapes[0].mesh.indices

  float verts[3 * 4];
  verts[0] = -0.7f, verts[1] = -0.7f, verts[2] = 0.0f;
  verts[3] = 0.7f, verts[4] = -0.7f, verts[5] = 0.0f;
  verts[6] = 0.7f, verts[7] = 0.7f, verts[8] = 0.0f;
  verts[9] = -0.7f, verts[10] = 0.7f, verts[11] = 0.0f;

  float norms[3 * 4];
  norms[0] = 1.0f, norms[1] = 1.0f, norms[2] = 0.0f;
  norms[3] = 0.0f, norms[4] = 1.0f, norms[5] = 0.0f;
  norms[6] = 0.0f, norms[7] = 0.0f, norms[8] = 0.0f;
  norms[9] = 1.0f, norms[10] = 0.0f, norms[11] = 0.0f;

  unsigned int indexes[3 * 2];
  indexes[0] = 0, indexes[1] = 1, indexes[2] = 2;
  indexes[3] = 0, indexes[4] = 3, indexes[5] = 2;

  {
    glGenBuffers(2, obj.vaaos);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vaaos[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), verts,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vaaos[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), norms,
                 GL_STATIC_DRAW);

    glGenBuffers(1, &obj.eao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.eao);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * sizeof(GLuint), indexes,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  {
    glGenVertexArrays(1, &obj.vao);
    glBindVertexArray(obj.vao);

    GLint posLoc = pro->getAttribLocation("VertexPosition");
    glEnableVertexAttribArray(posLoc);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vaaos[0]);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    GLint colLoc = pro->getAttribLocation("VertexColor");
    glEnableVertexAttribArray(colLoc);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vaaos[1]);
    glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}

void Scene::draw(GLFWwindow* window) {
  pro->enable();

  glViewport(0, 0, WIDTH, HEIGHT);
  glClearColor(0.5, 0.5, 0.5, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(obj.vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.eao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window);
  glfwPollEvents();
}
