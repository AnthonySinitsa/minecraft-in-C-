#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <iostream>
#include <limits.h>
#include "Renderer.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera camera;

// Callback function for handling keyboard input
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS || action == GLFW_REPEAT)
  {
    bool forward = (key == GLFW_KEY_W);
    bool backward = (key == GLFW_KEY_S);
    bool left = (key == GLFW_KEY_A);
    bool right = (key == GLFW_KEY_D);

    // DELETE ME ONCE NEEDED
    // if(forward) std::cout << "W key pressed" << std::endl;
    // if(backward) std::cout << "S key pressed" << std::endl;
    // if(left) std::cout << "A key pressed" << std::endl;
    // if(right) std::cout << "D key pressed" << std::endl;

    // calculate deltaTime
    float currentFrame = glfwGetTime();
    static float lastFrame = currentFrame;
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    camera.processKeyboardInput(forward, backward, left, right, deltaTime);
  }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
  static float lastX = 400, lastY = 300;
  static bool firstMouse = true;

  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.processMouseMovement(xoffset, yoffset);
}

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

  // Disable cursor
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if(glewInit() != GLEW_OK){
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Enable depth test
  glEnable(GL_DEPTH_TEST);

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  Renderer renderer; // Create a renderer object

  float lastFrame = 0.0f; // Last frame
  float deltaTime; // Time between current frame and last frame

  // Create a projection matrix
  float fov = glm::radians(45.0f); // 45-degree field of view
  float aspectRatio = 800.0f / 600.0f; // Adjust according to your window's size
  float nearPlane = 0.1f; // Anything closer than 0.1 units will be clipped
  float farPlane = 100.0f; // Anything further than 100 units will be clipped
  glm::mat4 projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

  glfwSetKeyCallback(window, keyCallback);
  glfwSetCursorPosCallback(window, mouseCallback);

  // create a projection matrix
  projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

  while (!glfwWindowShouldClose(window)){
    // Time logic
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Clear the screen
    // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update view matrix using camera and send it to the shader before rendering
    glm::mat4 view = camera.calculateViewMatrix();

    renderer.draw(view, projection); // Call draw method of renderer object

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up and close window
  glfwTerminate();
  return 0;
}