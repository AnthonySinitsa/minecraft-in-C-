#include "Renderer.h"
#include "Shader/Shader.h"

void Renderer::draw(){
  Shader shader("../src/Shader/vertex.shader", "../src/Shader/fragment.shader");
  shader.use();

  // Cube vertices
  float vertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
  };

  // Indices for each triangle that makes up each face of the cube
  unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    0, 1, 5, 5, 4, 0,
    2, 3, 7, 7, 6, 2,
    1, 2, 6, 6, 5, 1,
    4, 0, 3, 3, 7, 4
  };

  shader.stop();
}