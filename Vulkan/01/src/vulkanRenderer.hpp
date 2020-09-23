#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

class vulkanRenderer {
 public:
  vulkanRenderer();
  int init(GLFWwindow* newWindow);
  ~vulkanRenderer();

 private:
  GLFWwindow* window;

  // vulkan Conmponents
  VkInstance instance;

  // vulkan Functions
  void createInstance();
};

#endif  // VULKAN_RENDERER_HPP
