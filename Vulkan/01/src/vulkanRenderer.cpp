#include "vulkanRenderer.hpp"

vulkanRenderer::vulkanRenderer() {}

int vulkanRenderer::init(GLFWwindow* newWindow) {
  window = newWindow;

  try {
    createInstance();

  } catch (const std::runtime_error& e) {
    std::cerr << "ERROR: %s\n" << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return 0;
}

vulkanRenderer::~vulkanRenderer() {}

void vulkanRenderer::createInstance() {}
