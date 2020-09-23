#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "vulkanRenderer.hpp"

GLFWwindow* window;
vulkanRenderer vulkanrenderer;

void initWindow(std::string wName = "testWin", const int width = 800, const int height = 600) {
  // init glfw
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main() {
  // create win
  initWindow("testWin", 800, 600);

  // create vulkan renderer instance
  if (vulkanrenderer.init(window) == EXIT_FAILURE)
    return EXIT_FAILURE;

  // main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  // clean up
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
