#ifndef __JAW_H__
#define __JAW_H__

#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class jaw {
public:
  void Error(std::string value) { // pints error to terminal
    std::cerr << "[ERROR] " << value << "\n";
  }
};

#endif // __JAW_H__