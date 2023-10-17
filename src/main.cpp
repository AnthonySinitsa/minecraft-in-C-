#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Cube Vertices and indices
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

int main(){
  // Initialize GLFW and GLEW, create window
  if(!glfwInit()){
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Create buffers and load the cube's vertices and indeces into OpenGL
  GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
  if(!window){
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Load and compile shaders, create shader program
  glfwMakeContextCurrent(window);

  if(glewInit() != GLEW_OK){
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  while (!glfwWindowShouldClose(window)){
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Bing the shaer program and VAO
    // Draw the cube
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up and close window
  glfwTerminate();
  return 0;
}