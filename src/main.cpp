#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include "Renderer/Renderer.h"

int main(){
  // Print the current working directory
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    std::cout << "Current working dir: " << cwd << std::endl;
  } else {
    perror("getcwd() error");
    return 1;  // Return an error code
  }

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

  Renderer renderer; // Create a renderer object

  while (!glfwWindowShouldClose(window)){
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.draw(); // Call draw method of renderer object

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up and close window
  glfwTerminate();
  return 0;
}