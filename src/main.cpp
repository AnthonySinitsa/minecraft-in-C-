#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include "Renderer.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(){
  // Print the current working directory
  char cwd[PATH_MAX];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    std::cout << "Current working dir: " << cwd << std::endl;
  } else {
    perror("getcwd() error");
    return 1;  // Return an error code
  }

  glfwSetErrorCallback([](int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
  });


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
  Camera camera; // Create a camera object

  float lastFrame = 0.0f; // Last frame
  float deltaTime; // Time between current frame and last frame

  while (!glfwWindowShouldClose(window)){
    // Time logic
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process input
    bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
    camera.processKeyboardInput(forward, backward, left, right, deltaTime);

    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // update view matrix using camera and send it to the shader before rendering
    glm::mat4 view = camera.calculateViewMatrix();

    renderer.draw(view); // Call draw method of renderer object

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up and close window
  glfwTerminate();
  return 0;
}