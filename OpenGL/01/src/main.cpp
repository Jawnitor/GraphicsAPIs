#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shaderprogram.hpp"

void Error(std::string value)
{ // pints error to terminal
  std::cerr << "[ERROR] " << value << "\n";
}

const char *APP_TITLE = "OpenGL-Window"; // name of the window
const int gWindowWidth = 800;            // window width
const int gWindowHeight = 600;           // window height
GLFWwindow *gWindow = nullptr;           // window pointer
bool gWireFrame = false;                 // wire frame mode

/// function declerations ///
void glfwOnKey(GLFWwindow *window, int keyCode, int scancode, int action, int mode);
void showFPS(GLFWwindow *window);
bool initOpenGL();

int main(int argc, char *argv[])
{
  if (!initOpenGL())
  {
    Error("GLFW initalization failed");
    return -1;
  }

  /// Drawing to screen ///

  GLfloat vertices[] = {
      -0.5f, 0.5f,  0.0f, // top
      0.5f,  0.5f,  0.0f, // Right
      0.5f,  -0.5f, 0.0f, // left
      -0.5f, -0.5f, 0.0f  // vertex
  };

  GLuint indices[] = {
      0, 1, 2, // tri 0
      0, 2, 3  // tri 1
  };

  GLuint vbo, ibo, vao;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // position attrib
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);

  // index buffer object
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Shaderprogram shaderprogram;
  shaderprogram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

  /// main loop ///
  while (!glfwWindowShouldClose(gWindow))
  {
    showFPS(gWindow);

    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT);

    shaderprogram.use();

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(gWindow);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &ibo);

  glfwTerminate();
  return 0;
}

// initalizes OpenGL, GLFW and glew
bool initOpenGL()
{
  if (!glfwInit())
  { // prints error to tell user that glfw did big bad
    Error("GLFW initalization Failed");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // sets OpenGL versions
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // sets OpenGL versions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // forces modern OpenGL
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // compatablity for OpenGL 3 and upwards

  gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
  if (gWindow == NULL)
  { // if window fails to load
    Error("GLFW Failed to create window");
    glfwTerminate();
    return false;
  }
  glfwMakeContextCurrent(gWindow);

  glfwSetKeyCallback(gWindow, glfwOnKey);

  // inits glew
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK)
  { // prints error to tell user that glew did big bad
    std::cerr << "[ERROR] GLEW initalization Failed"
              << "\n";
    return false;
  }

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // bg color
  return true;
}

// closes window
void glfwOnKey(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key == GLFW_KEY_W && action == GLFW_PRESS)
  {
    gWireFrame = !gWireFrame;
    if (gWireFrame)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

// shows APP_FPS
void showFPS(GLFWwindow *window)
{
  static double prevSeconds = 0.0;
  static int frameCount = 0;
  double elapsedSeconds;
  double currentSeconds = glfwGetTime();

  elapsedSeconds = currentSeconds - prevSeconds;

  // limits text update to 4 times per second
  if (elapsedSeconds > 0.25)
  {
    prevSeconds = currentSeconds;
    double FPS = (double)frameCount / elapsedSeconds;
    double msPerFrame = 1000.0 / FPS;

    // changes window name to show FPS
    std::ostringstream outs;
    outs.precision(3);
    outs << std::fixed << APP_TITLE << ""
         << "FPS: " << FPS << ""
         << "FrameTime:(ms) " << msPerFrame;
    glfwSetWindowTitle(window, outs.str().c_str());

    frameCount = 0;
  }
  frameCount++;
}
