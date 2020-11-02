#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "../headers/Utilities.hpp"
#include "../headers/vulkanValidation.hpp"

class vulkanRenderer {
   public:
    vulkanRenderer();
    void cleanUp();

    int init(GLFWwindow* newWindow);
    ~vulkanRenderer();

    // vulkanValidation vValid;

   private:
    GLFWwindow* window{};
    // const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    // vulkan Components
    VkInstance               instance{};
    VkDebugUtilsMessengerEXT debugMessenger{};

    struct {
        VkPhysicalDevice vPhysicalDevice;
        VkDevice         vLogicalDevice;
    } mainDevice{};
    VkQueue vGraphicsQueue{};

    // vulkan Functions
    //-CreateFunctions
    void createInstance();
    void createLogicalDevice();

    //-Get Functions
    void getPhysicalDevice();

    //-Support Functions Extension
    static void setupDebugMessenger();  // validation support
    //-- Checker Functions
    static bool checkInstExtensionSupport(std::vector<const char*>* checkExtensions);
    bool        checkDeviceSuitable(VkPhysicalDevice vpdDevice);

    // -- Getter Functions
    QueueFamilyIndices getQueueFamilies(VkPhysicalDevice vpdDevice);
};

#endif  // VULKAN_RENDERER_HPP
