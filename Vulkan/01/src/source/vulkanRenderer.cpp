#include "../headers/vulkanRenderer.hpp"

vulkanRenderer::vulkanRenderer()
{
}

void vulkanRenderer::cleanUp()
{
    vkDestroyInstance(instance, nullptr);
}

// func creates window
int vulkanRenderer::init(GLFWwindow *newWindow)
{
    window = newWindow;

    try
    {
        createInstance();
        getPhysicalDevice();
        createLogicalDevice();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "ERROR: %s\n" << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
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
    appInfo.apiVersion         = VK_API_VERSION_1_0;       // vulkan version being used

    // creation information for vk instance
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo     = &appInfo;

    // create list to hold instance extensions
    std::vector<const char *> instanceExtensions = std::vector<const char *>();
    // sets up extension instance
    uint32_t     glfwExtensionCount = 0; // may require multiple extensions
    const char **glfwExtensions;         // Extensions passed as array of cStrings
    // gets GLFW extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // add GLFW extensions to list of extensions
    for (size_t i = 0; i < glfwExtensionCount; i++) instanceExtensions.push_back(glfwExtensions[i]);

    // checks instance support
    if (!checkInstExtensionSupport(&instanceExtensions))
        throw std::runtime_error("Vulkan does not support required extensions");

    createInfo.enabledExtensionCount   = static_cast<uint32_t>(instanceExtensions.size());
    createInfo.ppEnabledExtensionNames = instanceExtensions.data();

    // to-do Validation layers
    createInfo.enabledLayerCount   = 0;
    createInfo.ppEnabledLayerNames = nullptr;

    // Create instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (result != VK_SUCCESS) throw std::runtime_error("failed to make a vulkan instance");
}

void vulkanRenderer::createLogicalDevice()
{
    // Get queue family indices for the chosen Physical Device
    QueueFamilyIndices indices = getQueueFamilies(mainDevice.vPhysicalDevice);

    // Queues the logical device needs to create info to do so(Only 1 for now, will add more later!)
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    // The index of the family to create a queue from
    queueCreateInfo.queueFamilyIndex = indices.iGraphicsFamily;
    queueCreateInfo.queueCount       = 1; // Number of queues to create
    float fPriority                  = 1.0f;
    queueCreateInfo.pQueuePriorities = &fPriority;
    // ^ Vulkan needs to know how to handle multiple queues. so decided highest priority (1 highest)

    // Information to create logical device (sometimes called "device")
    VkDeviceCreateInfo vDeviceCreateInfo   = {};
    vDeviceCreateInfo.sType                = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    vDeviceCreateInfo.queueCreateInfoCount = 1; // Number of queue create Infos
}

void vulkanRenderer::getPhysicalDevice()
{
    // Enumerate Physical devices the vkInstance can access
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    // if no devices available then no support vulkan
    if (deviceCount == 0)
        throw std::runtime_error("Can't find any GPU's that support Vulkan Instance");

    // get list od Physical Devices
    std::vector<VkPhysicalDevice> vDeviceList(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, vDeviceList.data());

    for (const auto &device : vDeviceList)
    {
        if (checkDeviceSuitable(device))
        {
            mainDevice.vPhysicalDevice = device;
            break;
        }
    }
}

// func checks if we have the required extensions
bool vulkanRenderer::checkInstExtensionSupport(std::vector<const char *> *checkExtensions)
{
    // and to get number of extensions to create array of correct size to hold
    // extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // create a list of vkExtensionProperties using count
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    // check if given extensions are in list
    for (const auto &checkExtensions : *checkExtensions)
    {
        bool hasExtension = false;
        for (const auto &extensions : extensions)
        {
            if (strcmp(checkExtensions, extensions.extensionName))
            {
                hasExtension = true;
                break;
            }
        }
        if (!hasExtension) return false;
    }
    return true;
}

bool vulkanRenderer::checkDeviceSuitable(VkPhysicalDevice vpdDevice)
{
    /*
    // Information about the device(ID, name, type, vendor, etc)
    VkPhysicalDeviceProperties vDeviceProperties;
    vkGetPhysicalDeviceProperties(vpdDevice, &vDeviceProperties);

    //Information about what the device can do (geo shader, tess shader, wide lines, etc)
    VkPhysicalDeviceFeatures vDeviceFeatures;
    vkGetPhysicalDeviceFeatures(vpdDevice, &vDeviceFeatures);
    */
    QueueFamilyIndices indices = getQueueFamilies(vpdDevice);

    return indices.isValid();
}

QueueFamilyIndices vulkanRenderer::getQueueFamilies(VkPhysicalDevice vpdDevice)
{
    QueueFamilyIndices indices;

    // Get all Queue Family Properties info for the given device
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(vpdDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(vpdDevice, &queueFamilyCount, queueFamilyList.data());

    // go through each queue family and check if it has atleast 1 of the required types of queue
    int i = 0;
    for (const auto &queueFamily : queueFamilyList)
    {
        // First check if queue family has at least 1 queue in that family (possible to have none)
        // Queue can be multiple types defined thought bitfield. Need to bitwise AND with
        // VK_QUEUE_*_BIT to check if has required type
        if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.iGraphicsFamily = i; // if queue family is valid then get index
        }
        // Check if queue family indices are in a valid state, stop searching if so
        if (indices.isValid()) break;
        i++;
    }
    return indices;
}
