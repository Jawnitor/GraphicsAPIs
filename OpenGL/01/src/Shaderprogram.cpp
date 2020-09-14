#include "Shaderprogram.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Shaderprogram::Shaderprogram() : mHandle(0)
{
}

Shaderprogram::~Shaderprogram()
{
  glDeleteProgram(mHandle);
}

bool Shaderprogram::loadShaders(const char *vsFilename, const char *fsFilename)
{
  std::string vsString = fileToString(vsFilename);
  std::string fsString = fileToString(fsFilename);
  const GLchar *vsSourcePtr = vsString.c_str();
  const GLchar *fsSourcePtr = fsString.c_str();

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vs, 1, &vsSourcePtr, NULL);
  glShaderSource(fs, 1, &fsSourcePtr, NULL);

  glCompileShader(vs);
  checkCompileErrors(vs, VERTEX);
  glCompileShader(fs);
  checkCompileErrors(fs, FRAGMENT);

  mHandle = glCreateProgram();
  glAttachShader(mHandle, vs);
  glAttachShader(mHandle, fs);
  glLinkProgram(mHandle);

  checkCompileErrors(mHandle, PROGRAM);

  // Shader clean up
  glDeleteShader(vs);
  glDeleteShader(fs);

  return true;
}

void Shaderprogram::use()
{ // makes shader active
  if (mHandle > 0)
    glUseProgram(mHandle);
}

std::string Shaderprogram::fileToString(const std::string &filename)
{ // reads the shader files
  std::stringstream ss;
  std::ifstream file;

  try
  {
    file.open(filename, std::ios::in);
    if (!file.fail())
      ss << file.rdbuf();
    file.close();
  }
  catch (const std::exception &e)
  {
    std::cerr << "[ERROR] failed to read shader file name" << '\n';
  }
  return ss.str();
}

void Shaderprogram::checkCompileErrors(GLuint shader, ShaderType type)
{
  int status = 0;

  ShaderType st;
  switch (st)
  {
  case PROGRAM:
    glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
      GLint length = 0;
      glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &length);

      std::string errorLog(length, ' ');
      glGetProgramInfoLog(mHandle, length, &length, &errorLog[0]);

      std::cerr << "[ERROR] Program failed to link."
                << "\n";
    }
    break;

  case VERTEX || FRAGMENT:
    glGetProgramiv(mHandle, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
      GLint length = 0;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

      std::string errorLog(length, ' ');
      glGetShaderInfoLog(shader, length, &length, &errorLog[0]);

      std::cerr << "[ERROR] shader failed to Compile."
                << "\n";
    }
    break;

  default:
    break;
  };
}
