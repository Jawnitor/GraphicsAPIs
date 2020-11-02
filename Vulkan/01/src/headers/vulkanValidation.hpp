//
// Created by jaw on 24/10/2020.
//

#ifndef VULKANVALIDATION_HPP
#define VULKANVALIDATION_HPP
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

#include <iostream>
#include <stdexcept>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class vulkanValidation {
   public:
    // variables
    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    // functions
    bool                     checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();

    static VKAPI_ATTR VkBool32 VKAPI_CALL
                    debugCallBack(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                                  VkDebugUtilsMessageTypeFlagsEXT             messageType,
                                  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackdata,
                                  void*                                       pUserData);
    static VkResult CreateDebugUtilsMessengerEXT(
        VkInstance                                instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks*              pAlloctator,
        VkDebugUtilsMessengerEXT*                 pDebugMessenger);

    static void createDebugUtilsMessenger(VkInstance                instance,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);

    void DestroyDebugUtilsMessengerEXT(VkInstance                   instance,
                                       VkDebugUtilsMessengerEXT     debugMessenger,
                                       const VkAllocationCallbacks* pAllocator);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
} vValid;

#endif  // VULKANVALIDATION_HPP
