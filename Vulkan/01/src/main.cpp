#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLM/glm.hpp>
#include <GLM/mat4x4.hpp>
#include <iostream>

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(800, 600, "testWindow", nullptr, nullptr);

  uint32_t extenstionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extenstionCount, nullptr);

  printf("Extension count: %i\n", extenstionCount);

  glm::mat4 testMatrix(1.0f);
  glm::vec4 testVector(1.0f);

  auto testResult = testMatrix * testVector;

  // main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
