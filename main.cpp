#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <tiny_obj_loader.h>

#include "gl_program_wrapper.hpp"
#include "scene.hpp"

Scene scene;

void keycallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  scene.keycallback(window, key, scancode, action, mods);
}

int main(int argc, char *argv[]) {
  if (!glfwInit()) exit(1);
  if (atexit(glfwTerminate)) {
    glfwTerminate();
    exit(1);
  }

  int num_of_monitors;
  GLFWmonitor **monitors = glfwGetMonitors(&num_of_monitors);
  glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
  GLFWwindow *window =
      glfwCreateWindow(scene.getwidth(), scene.getheight(), "test", NULL, NULL);
  // Display on full screen
  // GLFWwindow *window =
  //     glfwCreateWindow(scene.getwidth(), scene.getheight(), "test",
  //     monitor[0], NULL);
  if (!window) exit(1);

  glfwMakeContextCurrent(window);

  std::cout << "GL Version   : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GL Vendor    : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "GL Renderer  : " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
  std::cout << std::endl;

  if (glewInit() != GLEW_OK) exit(1);

  glfwSwapInterval(1);
  glfwSetKeyCallback(window, keycallback);

  scene.setupProgram();
  scene.preProcess();

  while (!glfwWindowShouldClose(window)) {
    scene.draw(window);
  }
}
