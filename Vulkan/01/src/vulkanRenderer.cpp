#include "vulkanRenderer.hpp"

vulkanRenderer::vulkanRenderer()
{
}

// func reates window
int vulkanRenderer::init(GLFWwindow *newWindow)
{
    window = newWindow;

    try
    {
        createInstance();
        getPhysicalDevice();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "ERROR: %s\n" << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}

void vulkanRenderer::cleanUp()
{
    vkDestroyInstance(instance, nullptr);
}

vulkanRenderer::~vulkanRenderer()
{
}

// func creates instance
void vulkanRenderer::createInstance()
{
    // Information about the whole application
    // most data here doesnt affect the program just to help the dev
    VkApplicationInfo appInfo  = {};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO; // sets info type
    appInfo.pApplicationName   = "Vulkan App";                       // name of app
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);           // gives app a version
    appInfo.pEngineName        = "NoEngine";               // for if you want to make an engine
    appInfo.engineVersion      = VK_MAKE_VERSION(0, 0, 0); // for if you want to make an engine
    appInfo.apiVersion         = VK_API_VERSION_1_1;       // vulkan version being used

    // creation information for vk instance
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo     = &appInfo;

    // create list to hold instance extentions
    std::vector<const char *> instanceExtentions = std::vector<const char *>();
    // sets up extension instance
    uint32_t     glfwExtensionCount = 0; // may require multiple extensions
    const char **glfwExtentions;         // Extensions passed as array of cStrings
    // gets GLFW extentions
    glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // add GLFW extensions to list of extensions
    for (size_t i = 0; i < glfwExtensionCount; i++) instanceExtentions.push_back(glfwExtentions[i]);

    // checks instance support
    if (!checkInstExtentionSupport(&instanceExtentions))
        throw std::runtime_error("Vulkan does not support required extentions");

    createInfo.enabledExtensionCount   = static_cast<uint32_t>(instanceExtentions.size());
    createInfo.ppEnabledExtensionNames = instanceExtentions.data();

    // to-do Validation layers
    createInfo.enabledLayerCount   = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    // Create instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result != VK_SUCCESS) throw std::runtime_error("failed to make a vulkan instance");
}
void vulkanRenderer::getPhysicalDevice()
{
    // Enumerate Physical devices the vkInstance can access
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
}

// func checks if we have the required extensions
bool vulkanRenderer::checkInstExtentionSupport(std::vector<const char *> *checkExtentions)
{
    // and to get number of extensions to create array of correct size to hold
    // extensions
    uint32_t extentionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);

    // create a list of vkExtentionProperties using count
    std::vector<VkExtensionProperties> extentions(extentionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, extentions.data());

    // check if given extensions are in list
    for (const auto &checkExtentions : *checkExtentions)
    {
        bool hasExtention = false;
        for (const auto &extentions : extentions)
        {
            if (strcmp(checkExtentions, extentions.extensionName))
            {
                hasExtention = true;
                break;
            }
        }
        if (!hasExtention) return false;
    }
    return true;
}