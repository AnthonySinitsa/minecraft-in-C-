#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader {
public:
  Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
  ~Shader();

  void use();
  void stop();

private:
  unsigned int shaderID;

  std::string loadShaderFile(const std::string& filepath);
  unsigned int compileShader(unsigned int type, const char* source);
};

#endif //SHADER_H
