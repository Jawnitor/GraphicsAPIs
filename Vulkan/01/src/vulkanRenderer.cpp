#include "vulkanRenderer.hpp"

vulkanRenderer::vulkanRenderer()
{
}

int vulkanRenderer::init(GLFWwindow *newWindow)
{
  window = newWindow;

  try
  {
    createInstance();
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

void vulkanRenderer::createInstance()
{
  // Infomation about the whole application
  // most data here doesnt affect the program just to help the dev
  VkApplicationInfo appInfo  = {};
  appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO; // sets info type
  appInfo.pApplicationName   = "Vulkan App";                       // name of app
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);           // gives app a version
  appInfo.pEngineName        = "NoEngine";                         // for if you want to make an engine
  appInfo.engineVersion      = VK_MAKE_VERSION(0, 0, 0);           // for if you want to make an engine
  appInfo.apiVersion         = VK_API_VERSION_1_1;                 // vulkan version being used

  // creation indfomation for vk instance
  VkInstanceCreateInfo createInfo = {};
  createInfo.sType                = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo     = &appInfo;

  // create list to hold instance extentions
  std::vector<const char *> instanceExtentions = std::vector<const char *>();
  // sets up extention instance
  uint32_t     glfwExtensionCount = 0; // may require multiple extentions
  const char **glfwExtentions;         // Extentions passed as array of cStrings
  // gets GLFW extentions
  glfwExtentions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  // add GLFW extentions to list of extentions
  for (size_t i = 0; i < glfwExtensionCount; i++) instanceExtentions.push_back(glfwExtentions[i]);

  createInfo.enabledExtensionCount   = static_cast<uint32_t>(instanceExtentions.size());
  createInfo.ppEnabledExtensionNames = instanceExtentions.data();

  // Validation layers
  createInfo.enabledLayerCount = 0;
}
