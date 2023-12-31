#include "Renderer.h"
#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void Renderer::draw(const glm::mat4& view, const glm::mat4& projection){
  Shader shader("../src/Shader/vertex.shader", "../src/Shader/fragment.shader");
  shader.use();

  // Send view matrix to shader
  int viewLoc = glGetUniformLocation(shader.getShaderID(), "u_View");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  // Send projection matrix to shader
  int projLoc = glGetUniformLocation(shader.getShaderID(), "u_Projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

  // Send model matrix to shader - it's the identity matrix for now
  glm::mat4 model = glm::mat4(1.0f);  // Identity matrix means "no transformation"
  int modelLoc = glGetUniformLocation(shader.getShaderID(), "u_Model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

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

  // Create VAO, VBO, and EBO, and bind them
  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Specify vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Unbind the VBO and VAO
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
  glBindVertexArray(0);

  // Draw the object
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);

  // Error checking
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR)
  {
    std::cerr << "OpenGL error: " << err << std::endl;
  }

  shader.stop();
}