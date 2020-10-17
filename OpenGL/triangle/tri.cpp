#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char *APP_TITLE = "triangle";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
GLFWwindow *gWindow = nullptr;

bool initOpenGL();

int main(){
  if (!glfwInit()){
    std::cerr << "[ERROR] failed to init GLFW\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // sets OpenGL versions
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // sets OpenGL versions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // forces modern OpenGL
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // compatablity for OpenGL 3 and upwards


  

}