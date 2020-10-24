#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "../headers/Utilities.hpp"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class vulkanRenderer
{
  public:
    vulkanRenderer();
    void cleanUp();

    int init(GLFWwindow *newWindow);
    ~vulkanRenderer();

  private:
    GLFWwindow *                    window;
    const std::vector<const char *> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    // vulkan Components
    VkInstance instance;
    struct
    {
        VkPhysicalDevice vPhysicalDevice;
        VkDevice         vLogicalDevice;
    } mainDevice;
    VkQueue vGraphicsQueue;

    // vulkan Functions
    //-CreateFunctions
    void createInstance();
    void createLogicalDevice();

    //-Get Functions
    void getPhysicalDevice();

    //-Support Functions Extension
    bool checkValidationLayerSupport();
    //-- Checker Functions
    bool checkInstExtensionSupport(std::vector<const char *> *checkExtensions);
    bool checkDeviceSuitable(VkPhysicalDevice vpdDevice);

    // -- Getter Functions
    QueueFamilyIndices getQueueFamilies(VkPhysicalDevice vpdDevice);
};

#endif // VULKAN_RENDERER_HPP
