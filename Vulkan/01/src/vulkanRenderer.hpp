#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <string.h>
#include <vector>

class vulkanRenderer
{
public:
  vulkanRenderer();
  int init(GLFWwindow *newWindow);
  ~vulkanRenderer();

private:
  GLFWwindow *window;

  // vulkan Conmponents
  VkInstance instance;

  // vulkan Functions
  //--CreateFunctions
  void createInstance();

  //--Support Funnctions
  bool checkInstExtentionSupport(std::vector<const char *> *checkExtentions);
};

#endif // VULKAN_RENDERER_HPP
