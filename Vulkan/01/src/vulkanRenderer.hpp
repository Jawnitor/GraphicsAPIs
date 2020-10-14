#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

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

    // vulkan Components
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

    //--Support Functions Extension
    bool checkInstExtensionSupport(std::vector<const char *> *checkExtensions);
};

#endif // VULKAN_RENDERER_HPP
