#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string.h>

#include <iostream>
#include <stdexcept>
#include <vector>

class vulkanRenderer
{
  public:
    vulkanRenderer();
    void cleanUp();

    int init(GLFWwindow *newWindow);
    ~vulkanRenderer();

  private:
    GLFWwindow *window;

    // vulkan Conmponents
    VkInstance instance;
    struct
    {
        VkPhysicalDevice physicalDevice;
        VkDevice         logicalDevice;
    } mainDevice;

    // vulkan Functions
    //--CreateFunctions
    void createInstance();

    //--Get Functions
    void getPhysicalDevice();

    //--Support Funnctions
    bool checkInstExtentionSupport(std::vector<const char *> *checkExtentions);
};

#endif // VULKAN_RENDERER_HPP
